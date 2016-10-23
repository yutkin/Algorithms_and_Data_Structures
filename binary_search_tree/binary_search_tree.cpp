#include "binary_search_tree.h"

#include <algorithm>
#include <cassert>
#include <random>

using namespace std;

int N = 8;

random_device rd;
mt19937 rng(rd());
uniform_int_distribution<int> uni(-10*N,10*N);

int main() {
  custom::BinarySearchTree<int> bst;
  
  cout << "Generated:\n";
  vector<int> v(N);
  for (int i = 0; i < N; ++i) {
    auto r = uni(rng);
    v[i] = r;
    bst.insert(r);
    cout << r << endl;
  }
  cout << endl;

  auto vec_min = *min_element(v.begin(), v.end());
  auto tree_min = bst.min();
  cout << "Tree min: ";
  cout << tree_min << " vec min: " << vec_min << endl;
  cout << endl;
  assert(vec_min == tree_min);
  
  cout << "Printed tree:\n";
  bst.printTree();
  cout << endl;

  cout << "Printed by iters:\n";
  for (auto it = bst.begin(); it != bst.end(); ++it) {
    cout << *it << endl;
  }

  return 0;
}
