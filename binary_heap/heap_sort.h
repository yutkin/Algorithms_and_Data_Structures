#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <functional>
#include <cassert>

using std::swap;
using std::function;
using std::less;

namespace custom {

template<typename T>
void siftDown(T begin, T end, size_t i, size_t heap_size,
  function<bool(decltype(*begin), decltype(*begin))> compare = less<decltype(*begin)>()) {
  
  // 2*i+1 - left child
  while (2*i+1 < heap_size) {
    size_t maxInd = i;
    size_t l = 2*i+1;
    size_t r = 2*i+2;

    // Find maximum from children
    if (l < heap_size && compare(*(begin + maxInd), *(begin + l)))
      maxInd = l;
    if (r < heap_size && compare(*(begin + maxInd), *(begin + r)))
      maxInd = r;
    
    if (i != maxInd) {
      // Swap with maximum of children
      swap(*(begin + i), *(begin + maxInd));
      i = maxInd;
    }
    // "Break" if heap property isn't violated
    else break;
  }
}

template<typename T>
void heapify(T begin, T end,
  function<bool(decltype(*begin), decltype(*begin))> compare = less<decltype(*begin)>()) {  
  
  // Get heap size for O(1)
  size_t n = std::distance(begin, end);

  // Sift down first n/2 elements
  for (size_t j = (n - 1)/2 + 1; j > 0; --j) {
    siftDown(begin, end, j-1, n, compare);
  }
}

template<typename T>
void heap_sort(T begin, T end,
  function<bool(decltype(*begin), decltype(*begin))> compare = less<decltype(*begin)>()) {  
  
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