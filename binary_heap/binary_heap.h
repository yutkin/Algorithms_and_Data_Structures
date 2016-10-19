#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <functional>
#include <vector>
#include <cassert>
#include <initializer_list>

using std::swap;

namespace custom {

template<typename DataType, typename Predicate=std::less<DataType> >
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
    auto maxInd = i;
    
    auto lChild = leftChild(i);
    if (lChild < heap_size && compare(heap[maxInd], heap[lChild]))
      maxInd = lChild;
    
    auto rChild = rightChild(i);
    if (rChild < heap_size && compare(heap[maxInd], heap[rChild]))
      maxInd = rChild;

    if (i != maxInd) {
      swap(heap[i], heap[maxInd]);
      siftDown(maxInd);
    }
  }

  std::vector<DataType> heap;
  size_t heap_size = 0;
  Predicate compare = Predicate();
};

} // custom namespace

#endif // PRIORITY_QUEUE_H