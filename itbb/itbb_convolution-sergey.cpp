#include <iostream>
#include <vector>
#include <algorithm> // sort

#include <cstdlib> // srand, rand, atoi
#include <ctime> // time

#include <tbb/tbb.h>

const int RANDOM_MAX = 1000;
const int RANDOM_MIN = 1;

template<int n> class itbbConvolution {

public:

  itbbConvolution(std::vector<float>& output,
                  const std::vector<float>& data,
                  const std::vector<float>& kernel)
    : m_output(output)
    , m_data(data)
    , m_kernel(kernel)
  {
    output.resize(data.size());
  }

  void operator()(const tbb::blocked_range<size_t>& r) const
  {
    float sum;
    
    const float* __restrict p = &m_data[0] + r.begin();
    float* __restrict d = &m_output[0]+r.begin();

    float k[n];
    float c[n];
    k[0] = m_kernel[0];
    for (int i = 1; i < n; ++i)
    {
      c[i] = p[i-1];
      k[i] = m_kernel[i];
    }

    for (int i = 0, e = r.size()-n-1; i < e ; i += n) {
      d[i+0] = (c[0] = p[i+0]) * k[0] + c[1]*k[2]+c[2]*k[2]+c[3]*k[3]+c[4]*k[4]+c[5]*k[5]+c[6]*k[6];
      d[i+1] = (c[6] = p[i+1]) * k[0] + c[0]*k[2]+c[1]*k[2]+c[2]*k[3]+c[3]*k[4]+c[4]*k[5]+c[5]*k[6];
      d[i+2] = (c[5] = p[i+2]) * k[0] + c[6]*k[2]+c[0]*k[2]+c[1]*k[3]+c[2]*k[4]+c[3]*k[5]+c[4]*k[6];
      d[i+3] = (c[4] = p[i+3]) * k[0] + c[5]*k[2]+c[6]*k[2]+c[0]*k[3]+c[1]*k[4]+c[2]*k[5]+c[3]*k[6];
      d[i+4] = (c[3] = p[i+4]) * k[0] + c[4]*k[2]+c[5]*k[2]+c[6]*k[3]+c[0]*k[4]+c[1]*k[5]+c[2]*k[6];
      d[i+5] = (c[2] = p[i+5]) * k[0] + c[3]*k[2]+c[4]*k[2]+c[5]*k[3]+c[6]*k[4]+c[0]*k[5]+c[1]*k[6];
      d[i+6] = (c[1] = p[i+6]) * k[0] + c[2]*k[2]+c[3]*k[2]+c[4]*k[3]+c[5]*k[4]+c[6]*k[5]+c[0]*k[6];
    }


  }

#if 0
  void operator()(const tbb::blocked_range<size_t>& r) const
  {
    float sum;
    int middle = m_kernel.size() / 2;

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
#endif

private:
  std::vector<float>& m_output;
  const std::vector<float>& m_data;
  const std::vector<float>& m_kernel;
};

int main(int argc, char* argv[])
{
  /*if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <NUMBER_OF_THREADS> <DATA_SIZE>" << std::endl;
    exit(1);
  }*/

  const int NUMBER_OF_THREADS = 1;//tbb::task_scheduler_init::default_num_threads();//atoi(argv[1]);
  const int DATA_SIZE = 300000000;//atoi(argv[2]);
  const int CHUNK_SIZE = DATA_SIZE / NUMBER_OF_THREADS;

  // initialize random seed
  srand(time(NULL));
  tbb::task_scheduler_init init(NUMBER_OF_THREADS);

  // fillup data vector
  std::vector<float> data(DATA_SIZE);
  for (int i = 0; i < DATA_SIZE; i++)
    data[i] = rand() % RANDOM_MAX + RANDOM_MIN;

  // the kernel for the gaussian smooth
  float kernelArray[7] = { 0.06, 0.061, 0.242, 0.383, 0.242, 0.061, 0.06 };
  std::vector<float> kernel (kernelArray, kernelArray + sizeof(kernelArray) / sizeof(float) );

  // the convolution is not in-place, the result is stored in output
  std::vector<float> output(DATA_SIZE);

  
  itbbConvolution<7> ic(output, data, kernel);

  clock_t start = clock();
  tbb::parallel_for(tbb::blocked_range<size_t>(0, data.size(), CHUNK_SIZE), ic);

  clock_t end = clock();
  float elapsed = ((float) (end - start)) / CLOCKS_PER_SEC;
  std::cout << elapsed << std::endl;

  return 0;
}
