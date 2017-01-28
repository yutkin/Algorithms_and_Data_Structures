#include <algorithm>
#include <iostream>
#include <random>

#include "heap_sort.h"

using namespace std;

random_device rd;
mt19937 rng(rd());
uniform_int_distribution<int> uni(-100, 100);

template <typename T>
void printVector(T& v, const char* str = "") {
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

  custom::heapify(v.begin(), v.end(), greater<int>());
  assert(v[0] == *min_element(v.begin(), v.end()));
  printVector(v, "\nMin-Heapified vector:\n");

  vector<int> v2(30);
  for (auto& i : v2) i = uni(rng);
  printVector(v2, "\nInital vector:\n");

  custom::heap_sort(v2.begin(), v2.end(), greater<int>());
  assert(is_sorted(v2.begin(), v2.end(), greater<int>()));
  printVector(v2, "\nReverse sorted by heap sort:\n");

  return 0;
}