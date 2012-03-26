#include <iostream> // cout
#include <vector>

#include <cstdlib> // srand, rand, atoi
#include <ctime> // time, timespec, clock_gettime
#include <cmath> // pow, sqrt, log
#include <cfloat> // FLT_MAX

#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_reduce.h"


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


class itbbReduce {

public:
    float m_min;

    itbbReduce(std::vector<float>& data)
      : m_data(data)
      , m_min(FLT_MAX)
    {}

    itbbReduce(itbbReduce& other, tbb::split)
      : m_data(other.m_data)
      , m_min(FLT_MAX)
    {}

    void operator()(const tbb::blocked_range<size_t>& r)
    {
      float min = m_min;
      for(size_t i = r.begin(); i != r.end(); i++)
        if ( m_data[i] < min )
          min = m_data[i];

      m_min = min;
    }

    void join(const itbbReduce& other)
    {
      if ( other.m_min < m_min )
        m_min = other.m_min;
    }

private:
      const std::vector<float>& m_data;
};


int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cout << "Usage: " << argv[0] << " <NUMBER_OF_THREADS> <DATA_SIZE> <CHUNK_SIZE>" << std::endl;
    exit(1);
  }

  const int NUMBER_OF_THREADS = atoi(argv[1]);
  const int DATA_SIZE = atoi(argv[2]);
  const int CHUNK_SIZE = atoi(argv[3]);

  std::cout << "got: " << NUMBER_OF_THREADS << " " << DATA_SIZE << " " << CHUNK_SIZE << std::endl;
  return 0;

  srand(time(NULL));
  tbb::task_scheduler_init init(NUMBER_OF_THREADS);

  std::vector<float> data(DATA_SIZE);
  for (int i = 0; i < DATA_SIZE; i++)
    data[i] = rand() % RANDOM_MAX + RANDOM_MIN;

  itbbReduce mif(data);

  timespec startTime;
  clock_gettime(CLOCK_MONOTONIC, &startTime);

  tbb::parallel_reduce(tbb::blocked_range<size_t>(0, data.size(), CHUNK_SIZE), mif);
  float min = mif.m_min;

  timespec endTime;
  clock_gettime(CLOCK_MONOTONIC, &endTime);
  timespec timeDiff = diff(startTime, endTime);
  std::cout << timeDiff.tv_sec << "." << timeDiff.tv_nsec << std::endl;

  return 0;
}
