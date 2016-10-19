#include <iostream>
#include "binary_heap.h"

int main() {
  
  std::vector<int> v = {5, 9, 1, 8, -999, 6, 35, -2, 22, -12, 129, 0, 3 , 6, 2, 1, 123};

  custom::heapify(v.begin(), v.end(), std::greater<int>());
  std::cout << "Min-Heapified vector:\n";
  for (int i = 0; i < v.size(); ++i) {
    std::cout << v[i] << ' ';
  }
  std::cout << std::endl;
  
  custom::BinaryHeap<int, std::less<int>> maxHeap(v.begin(), v.end());
  
  assert(maxHeap.top() == *std::max_element(v.begin(), v.end()));
  
  std::cout << "Max BinHeap:\n";
  while (!maxHeap.empty()) {
    std::cout << maxHeap.top() << ' ';
    maxHeap.pop();
  }
  std::cout << std::endl;

  std::vector<int> v2 = {5, 9, 1, 8, -999, 6, 35, -2, 22, -12, 129, 0, 3 , 6, 2, 1, 123};
  custom::heap_sort(v2.begin(), v2.end());

  assert(std::is_sorted(v2.begin(), v2.end()));

  std::cout << "Sorted by heap sort:\n";
  for (auto& i : v2) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
  return 0;
}