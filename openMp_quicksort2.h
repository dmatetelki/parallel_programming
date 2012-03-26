void sample_qsort(float* begin, float* end) { ... }

void sample_qsort_serial(float* begin, float* end) { ... }

void sample_qsort_adaptive(float* begin, float* end, const long nthreshold)
{
  if (begin != end) {
    // parition ...
    if (end - begin + 1 <= nthreshold) {
      sample_qsort_serial(begin, middle);
      sample_qsort_serial(++middle, ++end);
    } else {
#pragma omp task
      sample_qsort_adaptive(begin, middle, nthreshold);
#pragma omp task
      sample_qsort_adaptive(++middle, ++end, nthreshold);
    }
  }
}

void sample_qsort_adaptive(float* begin, float* end)
{
  long nthreshold = ceil(sqrt(end - begin + 1)) / 2;
#pragma omp parallel
#pragma omp single nowait
  sample_qsort_adaptive(begin, end, nthreshold);
}