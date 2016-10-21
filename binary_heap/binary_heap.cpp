#include <algorithm>
#include <iostream>
#include <random>

#include "binary_heap.h"

using namespace std;

random_device rd;
mt19937 rng(rd());
uniform_int_distribution<int> uni(-100,100);

template <typename T>
void printVector(T& v, const char* str="") {
  cout << str;
  for (const auto& i : v) {
    cout << i << ' ';
  }
  cout << endl;
}

int main() {
  vector<int> v(30);
  for (auto& i : v) i = uni(rng);
  printVector(v, "Inital vector:\n");
  
  cout << "\nMax BinHeap:\n";
  custom::BinaryHeap<int, less<int>> maxHeap(v.begin(), v.end());
  assert(*max_element(v.begin(), v.end()) == maxHeap.top());

  
  while (!maxHeap.empty()) {
    cout << maxHeap.top() << ' ';
    maxHeap.pop();
  }
  cout << endl;

  return 0;
}