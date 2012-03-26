#include <iostream> // cout
#include <vector>

#include <cstdlib> // srand, rand, atoi
#include <ctime> // timespec, clock_gettime


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


/// @todo rewrite it
void serialConvolution(std::vector<float>& output,
                       const std::vector<float>& input,
                       const std::vector<float>& kernel)
{
  float sum;
  int middle = kernel.size() / 2;

  // before
  for (size_t i = 0; i < middle; i++) {
    sum = 0;
    for (int j = -middle; j <= middle; j++)
      if ( (int)i+j < 0 ) {
        sum += input[0] * kernel[j+middle];
      } else {
        sum += input[i+j] * kernel[j+middle];
      }

    output[i] = sum;
  }

  // unfolded loop
  const float* p = &input[0];
  float* d = &output[0];
  size_t n = kernel.size();
  float k[n];
  float c[n];
  k[0] = kernel[0];
  for (int i = 1; i < n; ++i)
  {
    c[i] = p[i-1];
    k[i] = kernel[i];
  }

  for (int i = 0, e = input.size()-n-1; i < e ; i += n) {
    d[i+0] = (c[0] = p[i+0]) * k[0] + c[1]*k[2]+c[2]*k[2]+c[3]*k[3]+c[4]*k[4]+c[5]*k[5]+c[6]*k[6];
    d[i+1] = (c[6] = p[i+1]) * k[0] + c[0]*k[2]+c[1]*k[2]+c[2]*k[3]+c[3]*k[4]+c[4]*k[5]+c[5]*k[6];
    d[i+2] = (c[5] = p[i+2]) * k[0] + c[6]*k[2]+c[0]*k[2]+c[1]*k[3]+c[2]*k[4]+c[3]*k[5]+c[4]*k[6];
    d[i+3] = (c[4] = p[i+3]) * k[0] + c[5]*k[2]+c[6]*k[2]+c[0]*k[3]+c[1]*k[4]+c[2]*k[5]+c[3]*k[6];
    d[i+4] = (c[3] = p[i+4]) * k[0] + c[4]*k[2]+c[5]*k[2]+c[6]*k[3]+c[0]*k[4]+c[1]*k[5]+c[2]*k[6];
    d[i+5] = (c[2] = p[i+5]) * k[0] + c[3]*k[2]+c[4]*k[2]+c[5]*k[3]+c[6]*k[4]+c[0]*k[5]+c[1]*k[6];
    d[i+6] = (c[1] = p[i+6]) * k[0] + c[2]*k[2]+c[3]*k[2]+c[4]*k[3]+c[5]*k[4]+c[6]*k[5]+c[0]*k[6];
  }

  // after
  for (size_t i = input.size()-middle; i < input.size(); i++) {
    sum = 0;
    for (int j = -middle; j <= middle; j++)
      if ( i+j > input.size()-1 ) {
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

  srand(time(NULL));

  std::vector<float> data(DATA_SIZE);
  for (int i = 0; i < DATA_SIZE; i++)
    data[i] = rand() % RANDOM_MAX + RANDOM_MIN;


  // the kernel for the gaussian smooth
  float kernelArray[7] = { 0.06, 0.061, 0.242, 0.383, 0.242, 0.061, 0.06 };
  std::vector<float> kernel (kernelArray, kernelArray + sizeof(kernelArray) / sizeof(float) );

  // the convolution is not in-place, the result is stored in output
  std::vector<float> output(DATA_SIZE);

  timespec startTime;
  clock_gettime(CLOCK_MONOTONIC, &startTime);

  serialConvolution(output, data, kernel);

  timespec endTime;
  clock_gettime(CLOCK_MONOTONIC, &endTime);
  timespec timeDiff = diff(startTime, endTime);
  std::cout << timeDiff.tv_sec << "." << timeDiff.tv_nsec << std::endl;

  return 0;
}
