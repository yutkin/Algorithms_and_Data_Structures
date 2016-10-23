#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <vector>
#include <cassert>
#include <initializer_list>

using std::swap;

namespace custom {

template <typename DataType, typename Compare = std::less<DataType> >
class BinaryHeap {
public:
  explicit BinaryHeap(): heap(1) {}

  explicit BinaryHeap(const std::initializer_list<DataType>& init): heap(1) {
    for (auto it = init.begin(); it != init.end(); ++it)
      push(*it);
  }
  
  template <typename T>
  explicit BinaryHeap(T begin, T end): heap(1) {
    for (auto it = begin; it != end; ++it)
      push(*it);
  }

  size_t size() const {
    return heap_size;
  }

  bool empty() const {
    return heap_size == 0;
  }

  void push(const DataType& val) {
    // If there is no enough space in heap, than allocate new
    if (heap_size == heap.capacity())
      heap.resize(heap.capacity()*2);
    
    // Add new element as the leave
    heap[heap_size] = val;

    // And sift it up
    siftUp(heap_size);
    ++heap_size;
  }

  DataType top() const {
    assert(heap_size > 0 && "Top from empty heap");
    return heap.front();
  }

  void pop() {
    assert(heap_size > 0 && "Pop from empty heap");

    // Set rightmost of leaves on the top position
    heap[0] = heap[--heap_size];

    // And sift it down
    siftDown(0);
  }

  const std::vector<DataType>& getPtr() const {
    // Return pointer to the underlying data
    return heap;
  }

private:
  // (i-1)/2 parent's node
  size_t parent(size_t i) const {
    return (i - 1) >> 1;
  }
  
  // 2*i+1 - left child
  size_t leftChild(size_t i) const {
    return (i << 1) + 1;
  } 

  // 2*i+2 - right child
  size_t rightChild(size_t i) const {
    return (i + 1) << 1;
  }
  
  void siftUp(size_t i) {
    // While i-th node is not a root and heap property is violated
    while (i > 0 && compare(heap[parent(i)], heap[i])) {
      
      // Swap i-th node with its parent
      swap(heap[parent(i)], heap[i]);

      // Check heap property for i-th node parent
      i = parent(i);
    }
  }

  void siftDown(size_t i) {
    
    // While i-th node has left child
    while (leftChild(i) < heap_size) {
      auto maxInd = i;
      
      auto lChild = leftChild(i);
      auto rChild = rightChild(i);

      // Find maximum of i-th node children
      if (lChild < heap_size && compare(heap[maxInd], heap[lChild]))
        maxInd = lChild;
      
      if (rChild < heap_size && compare(heap[maxInd], heap[rChild]))
        maxInd = rChild;


      // If heap property is NOT violated
      if (i == maxInd) break;

      // Swap i-th node with its max child
      swap(heap[i], heap[maxInd]);

      // Check heap property at the new position
      i = maxInd;
    }
  }

  std::vector<DataType> heap;
  size_t heap_size = 0;
  Compare compare = Compare{};
};

} // custom namespace

#endif // BINARY_HEAP_H