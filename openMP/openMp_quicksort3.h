// from http://berenger.eu/blog/2011/10/06/c-openmp-a-shared-memory-quick-sort-with-openmp-tasks-example-source-code/


template <class NumType>
inline void Swap(NumType& value, NumType& other)
{
  NumType temp = value;
  value = other;
  other = temp;
}


template <class SortType>
long QsPartition(SortType outputArray[], long left, long right)
{
  const long part = right;
  Swap(outputArray[part],outputArray[left + (right - left ) / 2]);
  const SortType partValue = outputArray[part];
  --right;

  while(true) {
    while(outputArray[left] < partValue)
      ++left;

    while(right >= left && partValue <= outputArray[right])
      --right;

    if(right < left)
      break;

    Swap(outputArray[left],outputArray[right]);
    ++left;
    --right;
  }

  Swap(outputArray[part],outputArray[left]);

  return left;
}


template <class SortType>
void QsSequential(SortType array[], const long left, const long right)
{
  if (left < right) {
    const long part = QsPartition(array, left, right);
    QsSequential(array,part + 1,right);
    QsSequential(array,left,part - 1);
  }
}


template <class SortType>
void QuickSortOmpTask(SortType array[], const long left, const long right, const int deep)
{
  if (left < right) {
    if (deep) {
      const long part = QsPartition(array, left, right);

#pragma omp task
      QuickSortOmpTask(array,part + 1,right, deep - 1);
#pragma omp task
      QuickSortOmpTask(array,left,part - 1, deep - 1);
    } else {
      const long part = QsPartition(array, left, right);
      QsSequential(array,part + 1,right);
      QsSequential(array,left,part - 1);
    }
  }
}


template <class SortType>
void QuickSortOmp(SortType array[], const long size)
{
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            QuickSortOmpTask(array, 0, size - 1 , 15);
        }
    }
}

