#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <functional>
#include <vector>
#include <cassert>
#include <initializer_list>

using std::swap;
using std::function;
using std::less;

namespace custom {

template<typename DataType, typename Predicate=less<DataType> >
class BinaryHeap {
public:
  explicit BinaryHeap() {}

  BinaryHeap(std::initializer_list<DataType> init) {
    for (auto it = init.begin(); it != init.end(); ++it)
      push(*it);
  }
  
  template <typename T>
  BinaryHeap(T begin, T end) {
    for (auto it = begin; it != end; ++it)
      push(*it);
  }

  size_t size() {
    return heap_size;
  }

  bool empty() {
    return heap_size == 0;
  }

  void push(DataType val) {
    heap.push_back(val);
    siftUp(heap_size++);
  }

  DataType top() {
    assert(heap_size > 0 && "Top from empty heap");
    return heap.front();
  }

  void pop() {
    assert(heap_size > 0 && "Pop from empty heap");
    heap[0] = heap[--heap_size];
    siftDown(0);
  }

  const DataType* getPtr() {
    return heap.data();
  }

private:
  size_t parent(size_t i) { return (i - 1)/2; }
  size_t leftChild(size_t i) { return 2*i + 1; }
  size_t rightChild(size_t i) { return 2*i + 2; }
  
  void siftUp(size_t i) {
    while (i > 0 && compare(heap[parent(i)], heap[i])) {
      swap(heap[parent(i)], heap[i]);
      i = parent(i);
    }
  }

  void siftDown(size_t i) {
    while (leftChild(i) < heap_size) {
      auto maxInd = i;
      
      auto lChild = leftChild(i);
      auto rChild = rightChild(i);

      if (lChild < heap_size && compare(heap[maxInd], heap[lChild]))
        maxInd = lChild;
      
      if (rChild < heap_size && compare(heap[maxInd], heap[rChild]))
        maxInd = rChild;

      if (i != maxInd) {
        swap(heap[i], heap[maxInd]);
        i = maxInd;
      } else break;
    }
  }

  std::vector<DataType> heap;
  size_t heap_size = 0;
  Predicate compare = Predicate();
};

template<typename T>
void siftDown(T begin, T end, size_t i, size_t sz,
  function<bool(decltype(*begin), decltype(*begin))> compare = less<decltype(*begin)>()) {
  
  while (2*i+1 < sz) {
    size_t maxInd = i;
    size_t l = 2*i+1;
    size_t r = 2*i+2;

    if (l < sz && compare(*(begin + maxInd), *(begin + l)))
      maxInd = l;
    if (r < sz && compare(*(begin + maxInd), *(begin + r)))
      maxInd = r;
    
    if (i != maxInd) {
      swap(*(begin + i), *(begin + maxInd));
      i = maxInd;
    }
    else break;
  }
}

template<typename T>
void heapify(T begin, T end,
  function<bool(decltype(*begin), decltype(*begin))> compare = less<decltype(*begin)>()) {  
  
  size_t n = std::distance(begin, end);
  for (size_t j = (n - 1)/2 + 1; j > 0; --j) {
    siftDown(begin, end, j-1, n, compare);
  }
}

template<typename T>
void heap_sort(T begin, T end,
  function<bool(decltype(*begin), decltype(*begin))> compare = less<decltype(*begin)>()) {  
  
  heapify(begin, end, compare);
  size_t heap_size = std::distance(begin, end);
  size_t counter = heap_size - 1;
  for (size_t j = 0; j < heap_size; ++j) {
    swap(*begin, *(begin + counter));
    siftDown(begin, end, 0, counter, compare);
    --counter;
  }
}

} // custom namespace

#endif // BINARY_HEAP_H