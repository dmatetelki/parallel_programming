#include <iostream> // cout
#include <vector>
#include <algorithm> // sort

#include <cstdlib> // srand, rand, atoi
#include <ctime> // time, timespec, clock_gettime

#include <omp.h> // omp_set_num_threads

#include "openMp_quicksort2.h"


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


void openMpSort(std::vector<float>& data)
{
  sample_qsort_adaptive(data.data(), data.data() + data.size());
}

int main(int argc, char* argv[])
{
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <NUMBER_OF_THREADS> <DATA_SIZE>" << std::endl;
    exit(1);
  }

  const int NUMBER_OF_THREADS = atoi(argv[1]);
  const int DATA_SIZE = atoi(argv[2]);
  // const int CHUNK_SIZE = DATA_SIZE / NUMBER_OF_THREADS;

  srand(time(NULL));
  omp_set_num_threads(NUMBER_OF_THREADS);

  std::vector<float> data(DATA_SIZE);
  for (int i = 0; i < DATA_SIZE; i++)
    data[i] = rand() % RANDOM_MAX + RANDOM_MIN;

  timespec startTime;
  clock_gettime(CLOCK_MONOTONIC, &startTime);

  openMpSort(data);

  timespec endTime;
  clock_gettime(CLOCK_MONOTONIC, &endTime);
  timespec timeDiff = diff(startTime, endTime);
  std::cout << timeDiff.tv_sec << "." << timeDiff.tv_nsec << std::endl;

  return 0;
}
