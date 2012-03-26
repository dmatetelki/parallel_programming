#include <iostream> // cout
#include <vector>
//#include <algorithm> // min, min_element

#include <cstdlib> // srand, rand, atoi
#include <ctime> // timespec, clock_gettime
#include <cfloat> // FLT_MAX

#include <omp.h> // omp_get_thread_num()

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


int openMpReduce(std::vector<float>& data,
                 const int numberOfThreads,
                 const int chunkSize)
{
  size_t i;
  std::vector<float> separate_results(numberOfThreads, FLT_MAX);

#pragma omp parallel \
  default(shared) private(i) \
  num_threads(numberOfThreads)
  {
    int threadId = omp_get_thread_num();

#pragma omp for \
  schedule(dynamic, chunkSize)

  for (i = 0; i < data.size(); i++)
    if (separate_results[threadId] < data[i])
      separate_results[threadId] = data[i];
  }

  // serial reduce
  float min(FLT_MAX);
  for (i  = 0; i < numberOfThreads; i++)
    if (separate_results[i] < min)
      min = separate_results[i];

  return min;
}


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

  std::vector<float> data(DATA_SIZE);
  for (int i = 0; i < DATA_SIZE; i++)
    data[i] = rand() % RANDOM_MAX + RANDOM_MIN;

  timespec startTime;
  clock_gettime(CLOCK_MONOTONIC, &startTime);

  float min = openMpReduce(data, NUMBER_OF_THREADS, CHUNK_SIZE);

  timespec endTime;
  clock_gettime(CLOCK_MONOTONIC, &endTime);
  timespec timeDiff = diff(startTime, endTime);
  std::cout << timeDiff.tv_sec << "." << timeDiff.tv_nsec << std::endl;

  return 0;
}
