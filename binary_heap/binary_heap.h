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
    // Add new element as the leave
    heap.push_back(val);
    
    // Then sift it up
    siftUp(heap_size++);
  }

  DataType top() {
    assert(heap_size > 0 && "Top from empty heap");
    return heap.front();
  }

  void pop() {
    assert(heap_size > 0 && "Pop from empty heap");

    // Set rightmost of leaves on the top position
    heap[0] = heap[--heap_size];

    // Then sift it down
    siftDown(0);
  }

  const DataType* getPtr() {
    // Return pointer to the underlying data
    return heap.data();
  }

private:
  size_t parent(size_t i) { return (i - 1)/2; }
  size_t leftChild(size_t i) { return 2*i + 1; }
  size_t rightChild(size_t i) { return 2*i + 2; }
  
  void siftUp(size_t i) {
    // While i-th node is not a root and heap property is violated
    while (i > 0 && compare(heap[parent(i)], heap[i])) {
      
      // Swap i-th node with his parent
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

      // Find max from i-th node children
      if (lChild < heap_size && compare(heap[maxInd], heap[lChild]))
        maxInd = lChild;
      
      if (rChild < heap_size && compare(heap[maxInd], heap[rChild]))
        maxInd = rChild;


      // If heap property is violated
      if (i != maxInd) {

        // Swap i-th node with his max child
        swap(heap[i], heap[maxInd]);

        // Check heap property for max child
        i = maxInd;
      } else break;
    }
  }

  std::vector<DataType> heap;
  size_t heap_size = 0;
  Predicate compare = Predicate();
};

} // custom namespace

#endif // BINARY_HEAP_H