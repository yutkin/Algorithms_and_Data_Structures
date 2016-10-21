#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <iomanip>
#include <memory>

namespace custom {

template <typename DataType>
class BinarySearchTree {

  struct BstNode {
    typedef std::shared_ptr<BstNode> nodeptr;

    BstNode(const DataType& key,
            nodeptr leftChild = nullptr,
            nodeptr rightChild = nullptr):
    _key(key), _leftChild(leftChild), _rightChild(rightChild) {}

    DataType _key;
    nodeptr  _leftChild;
    nodeptr  _rightChild;
    nodeptr  _parent;
  };

  typedef typename BstNode::nodeptr nodeptr;
public:
  explicit BinarySearchTree() {};

  void insert(const DataType&);
  DataType min() const;
  void printTree() const;
private:
  void printSubTree(const nodeptr& subTree) const {    
    if (subTree == nullptr)
      return;

    printSubTree(subTree->_leftChild);
    std::cout << subTree->_key << std::endl;
    printSubTree(subTree->_rightChild);
  }

  nodeptr _root;
};

template <typename T>
void BinarySearchTree<T>::insert(const T& key) {
  
  // Create new node
  auto newNode = std::make_shared<BstNode>(key);
  
  // Find appropriate position for new node
  nodeptr y = nullptr;
  auto x = _root;
  while (x != nullptr) {
    y = x;
    if (newNode->_key < x->_key)
      x = x->_leftChild;
    else if (newNode->_key > x->_key)
      x = x->_rightChild;
    else
      // Force the tree store only unique elements
      return;
  }
  newNode->_parent = y;
  if (y == nullptr)
    _root = newNode;
  else if (newNode->_key < y->_key)
    y->_leftChild = newNode;
  else
    y->_rightChild = newNode;
}

template <typename T>
T BinarySearchTree<T>::min() const {
  auto x = _root;
  while (x->_leftChild != nullptr)
    x = x->_leftChild;
  return x->_key;
}

template <typename T>
inline void BinarySearchTree<T>::printTree() const {
  printSubTree(_root);
}

}
#endif // BINARY_SEARCH_TREE_H
