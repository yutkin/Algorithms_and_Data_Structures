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
    friend class BinarySearchTree;
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
  };

public:
  typedef struct BstIterator iterator;

  explicit BinarySearchTree(): 
    // Initalize header node by random value
    _header(std::make_shared<BstNode>(42)),
    _leftmost(_header),
    _rightmost(_header),
    _end(_header) {}

  ~BinarySearchTree() {
    // TODO
  }

  void insert(const DataType&);
  void erase(const DataType&);
  void erase(iterator&);

  DataType min() const;
  DataType max() const;
  void printTree() const;
  
  iterator begin() const {
    return _leftmost;
  };

  iterator end() const { 
    return _end;
  }

  size_t size() const { 
    return _tree_size; 
  }

  iterator find(const DataType& key);

private:
  void _printSubTree(const BstNodePtr&) const;
  void _transplant(BstNodePtr, BstNodePtr);
  BstNodePtr _min(const BstNodePtr&) const;
  void _increment(iterator&);


  BstNodePtr _root;
  BstNodePtr _header;
  size_t _tree_size = 0;

  iterator _leftmost;
  iterator _rightmost;
  iterator _end;
};

template <typename T>
void BinarySearchTree<T>::_printSubTree(const BstNodePtr& subTree) const {
  if (subTree == nullptr)
    return;

  _printSubTree(subTree->_leftChild);
  std::cout << subTree->_key << std::endl;
  _printSubTree(subTree->_rightChild);
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
    _leftmost._node = _root;
    _rightmost._node = _root;
  } else if (newNode->_key < y->_key) {
    y->_leftChild = newNode;
    if (newNode->_key < _leftmost._node->_key)
      _leftmost._node = newNode;
  } else {
    y->_rightChild = newNode;
    if (newNode->_key > _rightmost._node->_key)
      _rightmost._node = newNode;
  }
  ++_tree_size;
}

template <typename T>
typename BinarySearchTree<T>::BstNodePtr
BinarySearchTree<T>::_min(const BstNodePtr& node) const {
  auto x = node;
  while (x->_leftChild != nullptr)
    x = x->_leftChild;
  return x;
}

template <typename T>
T BinarySearchTree<T>::min() const {
  assert(_leftmost._node != nullptr && "Getting min from empty tree");
  return _leftmost._node->_key;
}

template <typename T>
T BinarySearchTree<T>::max() const {
  assert(_rightmost._node != nullptr && "Getting max from empty tree");
  return _rightmost._node->_key;
}

template <typename T>
inline void BinarySearchTree<T>::printTree() const {
  _printSubTree(_root);
}

template <typename T>
typename BinarySearchTree<T>::iterator
BinarySearchTree<T>::find(const T& key) {
  iterator foundNode = end();
  auto node = _root;
  while (node != nullptr)
    if (key > node->_key)
      node = node->_rightChild;
    else if (key < node->_key)
      node = node->_leftChild;
    else {
      foundNode = node;
      break;
    }
  return foundNode;
}

template <typename T>
void BinarySearchTree<T>::_transplant(BstNodePtr u, BstNodePtr v) {
  if (u->_parent == _header) {
    _root = v;
    _header->_leftChild = v;
  } else if (u == u->_parent->_leftChild)
    u->_parent->_leftChild = v;
  else
    u->_parent->_rightChild = v;

  if (v != nullptr)
    v->_parent = u->_parent;
}

template <typename T>
void BinarySearchTree<T>::erase(iterator& it) {
  auto node = it._node;

  if (node->_leftChild == nullptr)
    _transplant(node, node->_rightChild);
  else if (node->_rightChild == nullptr)
    _transplant(node, node->_leftChild);
  else {
    auto x = _min(node->_rightChild);
    if (x->_parent != node) {
      _transplant(x, x->_rightChild);
      x->_rightChild = node->_rightChild;
      x->_rightChild->_parent = x;
    }
    _transplant(node, x);
    x->_leftChild = node->_leftChild;
    node->_leftChild->_parent = x;
  }

  if (node == _leftmost._node)
    ++_leftmost;
  
  node.reset();
  
  --_tree_size;
}

template <typename T>
void BinarySearchTree<T>::erase(const T& key) {
  auto node = find(key);
  
  if (node != end())
    erase(node);
}

template <typename T>
typename BinarySearchTree<T>::iterator&
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
