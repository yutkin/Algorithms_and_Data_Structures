#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <cassert>

using std::swap;

namespace custom {

template<
  typename T,
  typename Compare = std::less<typename std::iterator_traits<T>::value_type>
>
void siftDown(T begin, T end, size_t i, size_t heap_size,
  Compare compare = Compare{})
{
  // 2*i+1 - left child
  while ((i << 1) + 1 < heap_size) {
    size_t maxInd = i;
    size_t l = (i << 1) + 1;
    size_t r = (i + 1) << 1;

    // Find maximum from children
    if (l < heap_size && compare(*(begin + maxInd), *(begin + l)))
      maxInd = l;
    if (r < heap_size && compare(*(begin + maxInd), *(begin + r)))
      maxInd = r;
    
    // "Break" if heap property is NOT violated
    if (i == maxInd) break;
    
    // Swap with maximum of children
    swap(*(begin + i), *(begin + maxInd));
    
    // Check heap property for max child 
    i = maxInd; 
  }
}

template<
  typename T,
  typename Compare = std::less<typename std::iterator_traits<T>::value_type>
>
void heapify(T begin, T end, Compare compare = Compare{}) {  
  
  // Get heap size for O(1)
  size_t n = std::distance(begin, end);

  // Sift down first n/2 elements
  for (size_t j = n/2; j > 0; --j) {
    siftDown(begin, end, j-1, n, compare);
  }
}

template<
  typename T,
  typename Compare = std::less<typename std::iterator_traits<T>::value_type>
>
void heap_sort(T begin, T end, Compare compare = Compare{}) {

  // Build a heap
  heapify(begin, end, compare);

  // Get heap size for O(1)
  size_t heap_size = std::distance(begin, end);
  
  for (size_t j = 0; j < heap_size; ++j) {

    // heap_bound points to the rightmost element
    // of the unsorted part of the container
    size_t heap_bound = heap_size - j - 1;

    // Swap highest element in the heap
    // with heap bound
    swap(*begin, *(begin + heap_bound));

    // Sift down new top of heap
    siftDown(begin, end, 0, heap_bound, compare);
  }
}

} // custom namespace

#endif // HEAP_SORT_H