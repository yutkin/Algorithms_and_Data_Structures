#include "binary_search_tree.h"

#include <algorithm>
#include <set>
#include <cassert>
#include <random>

using namespace std;

size_t N = 100000;

random_device rd;
mt19937 rng(rd());
uniform_int_distribution<int> uni(-10*N,10*N);

int main() {
  custom::BinarySearchTree<int> bst;
  std::set<int> s;
  
  for (size_t i = 0; i < N; ++i) {
    auto k = uni(rng);
    s.insert(k);
    bst.insert(k);
  }


  auto set_min = *s.begin();
  auto set_max = *s.rbegin();

  assert(set_min == bst.min());
  assert(set_max == bst.max());

  assert(bst.find(set_min) != bst.end());
  assert(bst.find(set_max) != bst.end());

  auto bst_it = bst.begin();
  auto set_it = s.begin();
  for (size_t i = 0; i < bst.size(); ++i) {
    
    assert(*bst_it == *set_it);
    assert(bst.size() == s.size());
    
    auto old_bst = bst_it;
    auto old_set = set_it;
    
    ++bst_it;
    ++set_it;
    
    s.erase(old_set);
    bst.erase(old_bst);
  }

}
