#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

#include "binary_heap.h"
#include "heap_sort.h"

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<int> uni(-100,100);

template <typename T>
void printVector(T& v, const char* str="") {
  std::cout << str;
  for (const auto& i : v) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
}

int main() {

  std::vector<int> v(30);
  for (auto& i : v) i = uni(rng);
  printVector(v, "Inital vector:\n");

  custom::heapify(v.begin(), v.end(), std::greater<int>());
  assert(v[0] == *std::min_element(v.begin(), v.end()));
  printVector(v, "\nMin-Heapified vector:\n");
  
  


  std::cout << "\nMax BinHeap:\n";
  custom::BinaryHeap<int, std::less<int>> maxHeap(v.begin(), v.end());
  assert(maxHeap.top() == *std::max_element(v.begin(), v.end()));
  
  while (!maxHeap.empty()) {
    std::cout << maxHeap.top() << ' ';
    maxHeap.pop();
  }
  std::cout << std::endl;




  std::vector<int> v2(30);
  for (auto& i : v2) i = uni(rng);
  printVector(v2, "\nInital vector:\n");

  custom::heap_sort(v2.begin(), v2.end(), std::greater<int>());
  assert(std::is_sorted(v2.begin(), v2.end(), std::greater<int>()));
  printVector(v2, "\nReverse sorted by heap sort:\n");

  return 0;
}