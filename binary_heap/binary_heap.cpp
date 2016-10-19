#include <iostream>

#include "binary_heap.h"

int main() {
  
  auto init_list = {5, 9, 1, 8, -999, 6, 35, -2, 22, -12, 129, 0, 3 , 6, 2, 1, 123};
  
  custom::BinaryHeap<int, std::less<int>> maxHeap(init_list.begin(), init_list.end());
  custom::BinaryHeap<int, std::greater<int>> minHeap = init_list;
  

  assert(maxHeap.size() == minHeap.size());
  assert(maxHeap.top() == 129);
  assert(minHeap.top() == -999);
  
  std::cout << "Max BinHeap:\n";
  while (!maxHeap.empty()) {
    std::cout << maxHeap.top() << ' ';
    maxHeap.pop();
  }
  std::cout << std::endl;

  std::cout << "\nMin BinHeap:\n";
  while (!minHeap.empty()) {
    std::cout << minHeap.top() << ' ';
    minHeap.pop();
  }
  std::cout << std::endl;
  return 0;
}