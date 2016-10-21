#include "binary_search_tree.h"

#include <algorithm>
#include <cassert>
#include <random>

using namespace std;

int N = 30;

random_device rd;
mt19937 rng(rd());
uniform_int_distribution<int> uni(-2*N,2*N);

int main() {
  custom::BinarySearchTree<int> bst;
  
  vector<int> v(N);
  for (int i = 0; i < N; ++i) {
    auto r = uni(rng);
    v[i] = r;
    bst.insert(r);
  }

  auto vec_min = *min_element(v.begin(), v.end());
  auto tree_min = bst.min();
  assert(vec_min == tree_min);
  
  bst.printTree();
  return 0;
}
