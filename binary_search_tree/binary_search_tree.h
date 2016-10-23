#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <cassert>
#include <memory>

namespace custom {

template <typename DataType>
class BinarySearchTree {

  struct BstNode {
    typedef std::shared_ptr<BstNode> BstNodePtr;

    BstNode(const DataType& key,
            BstNodePtr leftChild = nullptr,
            BstNodePtr rightChild = nullptr):
    _key(key), _leftChild(leftChild), _rightChild(rightChild) {}

    DataType _key;
    BstNodePtr  _leftChild;
    BstNodePtr  _rightChild;
    BstNodePtr  _parent;
  };

  typedef typename BstNode::BstNodePtr BstNodePtr;

  struct BstIterator {
  public:
    BstIterator(const BstNodePtr& node): _node(node) {}
    BstIterator& operator++();

    bool operator==(const BstIterator& rhs) const {
      return rhs._node == this->_node;
    };
    
    bool operator!=(const BstIterator& rhs) const {
      return rhs._node != this->_node;
    };

    const DataType& operator*() const {
      // Undefined behavior providing that _node is nullptr ¯\_(ツ)_/¯
      return _node->_key; 
    };
  private:
    BstNodePtr _node;
    BstNodePtr _header;
  };

private:
  void printSubTree(const BstNodePtr& subTree) const;

public:
  explicit BinarySearchTree() {
    _header = std::make_shared<BstNode>(42);
  };

  void insert(const DataType&);
  void erase(const DataType&);
  DataType min() const;
  DataType max() const;
  void printTree() const;
  
  BstIterator begin() const {
    return BstIterator(_leftmost);
  };

  BstIterator end() const { 
    return BstIterator(_header); 
  }

  size_t size() const { 
    return _tree_size; 
  }

private:
  BstNodePtr _root;
  BstNodePtr _header;
  size_t _tree_size = 0;
  BstNodePtr _leftmost;
  BstNodePtr _rightmost;
};

template <typename T>
void BinarySearchTree<T>::printSubTree(const BstNodePtr& subTree) const {
  if (subTree == nullptr)
    return;

  printSubTree(subTree->_leftChild);
  std::cout << subTree->_key << std::endl;
  printSubTree(subTree->_rightChild);
}

template <typename T>
void BinarySearchTree<T>::insert(const T& key) {
  
  // Create new node
  auto newNode = std::make_shared<BstNode>(key);

  // The trailing pointer at the parent of x
  BstNodePtr y = _header;

  auto x = _root;
  
  // Find appropriate position for new node
  while (x != nullptr) {
    y = x;
    if (newNode->_key < x->_key)
      x = x->_leftChild;
    else if (newNode->_key > x->_key)
      x = x->_rightChild;
    else
      // Force the tree to store only unique elements
      return;
  }
  
  newNode->_parent = y;
  
  if (y == _header) {
    _root = newNode;
    _header->_leftChild = _root;
    _leftmost = _root;
    _rightmost = _root;
  } else if (newNode->_key < y->_key) {
    y->_leftChild = newNode;
    if (newNode->_key < _leftmost->_key)
      _leftmost = newNode;
  } else {
    y->_rightChild = newNode;
    if (newNode->_key > _rightmost->_key)
      _rightmost = newNode;
  }
  ++_tree_size;
}

template <typename T>
T BinarySearchTree<T>::min() const {
  assert(_leftmost != nullptr && "Getting min from empty tree");
  return _leftmost->_key;
}

template <typename T>
T BinarySearchTree<T>::max() const {
  assert(_rightmost != nullptr && "Getting max from empty tree");
  return _rightmost->_key;
}

template <typename T>
inline void BinarySearchTree<T>::printTree() const {
  printSubTree(_root);
}

template <typename T>
void BinarySearchTree<T>::erase(const T& key) {

}

template <typename T>
typename BinarySearchTree<T>::BstIterator&
BinarySearchTree<T>::BstIterator::operator++() {

  if (_node->_rightChild != nullptr) {
    _node = _node->_rightChild;
    while (_node->_leftChild != nullptr)
      _node = _node->_leftChild;
    return *this;
  }
  
  auto parent = _node->_parent;
  while (parent->_rightChild == _node) {
    _node = parent;
    parent = _node->_parent;
  }  

  if (_node->_rightChild != parent)
    _node = parent;
  
  return *this;
}

}
#endif // BINARY_SEARCH_TREE_H
