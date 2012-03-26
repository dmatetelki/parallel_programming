#include <iostream> // cout
#include <vector>

#include <cstdlib> // srand, rand, atoi
#include <ctime> // time, timespec, clock_gettime
#include <cmath> // pow, sqrt, log

#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"


const int RANDOM_MAX = 1000;
const int RANDOM_MIN = 1;


timespec diff(timespec start, timespec end)
{
  timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}


// passing by value and not a reference saves memory read time
float modify(float value)
{
  return 13.37 * pow(sqrt(value), log(value));
}


class itbbMap {

public:

  itbbMap(std::vector<float>& data)
    : m_data(data)
  {}

  void operator()(const tbb::blocked_range<size_t>& r) const
  {
    for( size_t i = r.begin(); i != r.end(); i++ )
      m_data[i] = modify(m_data[i]);
  }

private:
  std::vector<float>& m_data;
};


int main(int argc, char* argv[])
{
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <NUMBER_OF_THREADS> <DATA_SIZE>" << std::endl;
    exit(1);
  }

  const int NUMBER_OF_THREADS = atoi(argv[1]);
  const int DATA_SIZE = atoi(argv[2]);
  const int CHUNK_SIZE = DATA_SIZE / NUMBER_OF_THREADS;

  srand(time(NULL));
  tbb::task_scheduler_init init(NUMBER_OF_THREADS);

  std::vector<float> data(DATA_SIZE);
  for (int i = 0; i < DATA_SIZE; i++)
    data[i] = rand() % RANDOM_MAX + RANDOM_MIN;

  itbbMap im(data);

  timespec startTime;
  clock_gettime(CLOCK_MONOTONIC, &startTime);

  tbb::parallel_for(tbb::blocked_range<size_t>(0, data.size(), CHUNK_SIZE), im);

  timespec endTime;
  clock_gettime(CLOCK_MONOTONIC, &endTime);
  timespec timeDiff = diff(startTime, endTime);
  std::cout << timeDiff.tv_sec << "." << timeDiff.tv_nsec << std::endl;

  return 0;
}
