#include <iostream>
#include <random>

#include "binary_heap.h"
#include "heap_sort.h"

int main() {
  
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(-100,100);

  std::vector<int> v(20);

  std::cout << "Inital vector:\n";
  for (int i = 0; i < v.size(); ++i) {
    v[i] = uni(rng);
    std::cout << v[i] << ' ';
  }
  std::cout << std::endl;

  custom::heapify(v.begin(), v.end(), std::greater<int>());
  assert(v[0] == *std::min_element(v.begin(), v.end()));
  
  std::cout << "\nMin-Heapified vector:\n";
  for (int i = 0; i < v.size(); ++i) {
    std::cout << v[i] << ' ';
  }
  std::cout << std::endl;
  
  custom::BinaryHeap<int, std::less<int>> maxHeap(v.begin(), v.end());  
  assert(maxHeap.top() == *std::max_element(v.begin(), v.end()));
  
  std::cout << "\nMax BinHeap:\n";
  while (!maxHeap.empty()) {
    std::cout << maxHeap.top() << ' ';
    maxHeap.pop();
  }
  std::cout << std::endl;

  std::vector<int> v2(20);
  for (int i = 0; i < v2.size(); ++i) {
    v2[i] = uni(rng);
  }

  custom::heap_sort(v2.begin(), v2.end());

  assert(std::is_sorted(v2.begin(), v2.end()));

  std::cout << "\nSorted by heap sort:\n";
  for (auto& i : v2) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
  return 0;
}