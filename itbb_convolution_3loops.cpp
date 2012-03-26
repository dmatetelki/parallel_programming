#include <iostream>
#include <vector>
#include <algorithm> // sort

#include <cstdlib> // srand, rand, atoi
#include <ctime> // time

#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

const int RANDOM_MAX = 1000;
const int RANDOM_MIN = 1;

class itbbConvolution {

public:

  itbbConvolution(std::vector<double>& output,
                  const std::vector<double>& data,
                  const std::vector<double>& kernel)
    : m_output(output)
    , m_data(data)
    , m_kernel(kernel)
  {
    output.resize(data.size());
  }

  void operator()(const tbb::blocked_range<size_t>& r) const
  {
    double sum;
    int middle = m_kernel.size() / 2;

    // before
    for (size_t i = r.begin(); i != r.end(); i++) {
      sum = 0;
      for (int j = -middle; j <= middle; j++)
        if ( (int)i+j < 0 ) {
          sum += m_data[0] * m_kernel[j+middle];
        } else if ( i+j > m_data.size()-1 ) {
          sum += m_data[m_data.size()-1] * m_kernel[j+middle];
        } else {
          sum += m_data[i+j] * m_kernel[j+middle];
        }

      m_output[i] = sum;
    }

    for (size_t i = r.begin(); i != r.end(); i++) {
      sum = 0;
      for (int j = -middle; j <= middle; j++)
        if ( (int)i+j < 0 ) {
          sum += m_data[0] * m_kernel[j+middle];
        } else if ( i+j > m_data.size()-1 ) {
          sum += m_data[m_data.size()-1] * m_kernel[j+middle];
        } else {
          sum += m_data[i+j] * m_kernel[j+middle];
        }

      m_output[i] = sum;
    }

    // after
    for (size_t i = r.begin(); i != r.end(); i++) {
      sum = 0;
      for (int j = -middle; j <= middle; j++)
        if ( (int)i+j < 0 ) {
          sum += m_data[0] * m_kernel[j+middle];
        } else if ( i+j > m_data.size()-1 ) {
          sum += m_data[m_data.size()-1] * m_kernel[j+middle];
        } else {
          sum += m_data[i+j] * m_kernel[j+middle];
        }

      m_output[i] = sum;
    }
  }

private:
  std::vector<double>& m_output;
  const std::vector<double>& m_data;
  const std::vector<double>& m_kernel;
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

  // initialize random seed
  srand(time(NULL));
  tbb::task_scheduler_init init(NUMBER_OF_THREADS);

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

  itbbConvolution ic(output, data, kernel);
  tbb::parallel_for(tbb::blocked_range<size_t>(0, data.size(), CHUNK_SIZE), ic);

  clock_t end = clock();
  double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
  std::cout << elapsed << std::endl;

  return 0;
}
