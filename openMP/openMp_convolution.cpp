#include <iostream>
#include <vector>
#include <algorithm> // sort

#include <cstdlib> // srand, rand, atoi
#include <ctime> // time

const int RANDOM_MAX = 1000;
const int RANDOM_MIN = 1;

void openMpConvolution(std::vector<double>& output,
                       const std::vector<double>& input,
                       const std::vector<double>& kernel,
                       const int numberOfThreads,
                       const int chunkSize)
{
  size_t i;
  double sum;
  int middle = kernel.size() / 2;
  output.resize(input.size());

#pragma omp parallel for      \
  default(shared) private(i)  \
  schedule(dynamic, chunkSize) \
  num_threads(numberOfThreads)

  for (i = 0; i < input.size(); i++) {
    sum = 0;
    for (int j = -middle; j <= middle; j++)
      if ( (int)i+j < 0 ) {
        sum += input[0] * kernel[j+middle];
      } else if ( i+j > input.size()-1 ) {
        sum += input[input.size()-1] * kernel[j+middle];
      } else {
        sum += input[i+j] * kernel[j+middle];
      }

    output[i] = sum;
  }
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

  // initialize random seed
  srand(time(NULL));

  // fillup data vector
  std::vector<double> data(DATA_SIZE);
  for (int i = 0; i < DATA_SIZE; i++)
    data[i] = rand() % RANDOM_MAX + RANDOM_MIN;

  // the kernel for the gaussian smooth
  double kernelArray[7] = { 0.06, 0.061, 0.242, 0.383, 0.242, 0.061, 0.06 };
  std::vector<double> kernel (kernelArray, kernelArray + sizeof(kernelArray) / sizeof(double) );

  // the convolution is not in-place, the result is stored in output
  std::vector<double> output(DATA_SIZE);

  clock_t start = clock();

  openMpConvolution(output, data, kernel, NUMBER_OF_THREADS, CHUNK_SIZE);

  clock_t end = clock();
  double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
  std::cout << elapsed << std::endl;

  return 0;
}
