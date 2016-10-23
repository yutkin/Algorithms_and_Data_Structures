#include "binary_search_tree.h"

#include <algorithm>
#include <cassert>
#include <random>

using namespace std;

int N = 5;

random_device rd;
mt19937 rng(rd());
uniform_int_distribution<int> uni(-10*N,10*N);

int main() {
  custom::BinarySearchTree<int> bst;
  
  cout << "Generated:\n";
  vector<int> v(N);
  for (size_t i = 0; i < v.size(); ++i) {
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
  assert(bst.find(vec_min) != bst.end());

  cout << "Printed tree:\n";
  bst.printTree();
  cout << endl;

  // while (true) {
  //   custom::BinarySearchTree<int> bst;
  //   for (size_t i = 0; i < 100; ++i) {
  //     auto r = uni(rng);
  //     bst.insert(r);
  //   }    
  // }
  
}
