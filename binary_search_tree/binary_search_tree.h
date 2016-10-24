#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <cassert>
#include <memory>
#include <stack>

namespace custom {

template <typename DataType>
class BinarySearchTree {

  /* Binary Search Tree (BST) */

  struct BstNode {
    typedef std::shared_ptr<BstNode> BstNodePtr;

    BstNode(const DataType& key,
            BstNodePtr leftChild = nullptr,
            BstNodePtr rightChild = nullptr):
    _key(key), _left(leftChild), _right(rightChild) {}

    DataType _key;
    BstNodePtr  _left;
    BstNodePtr  _right;
    BstNodePtr  _parent;
  };

  typedef typename BstNode::BstNodePtr BstNodePtr;

  struct BstIterator {
    friend class BinarySearchTree; // For access to _node member
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
      /* Undefined behavior providing that _node is nullptr ¯\_(ツ)_/¯.
         Maybe throw an exception? */
      return _node->_key; 
    };
  private:
    BstNodePtr _node;
  };

public:
  typedef struct BstIterator iterator;

  explicit BinarySearchTree(): 
    // 42 is random value. Just to meet a constructor requirements.
    _header(std::make_shared<BstNode>(42)),
    _leftmost(_header),
    _rightmost(_header),
    _end(_header) {}

  ~BinarySearchTree() {
    clear();
    _tree_size = 0;
    _leftmost._node = _header;
    _end._node = _header;
  }

  void clear();
  void insert(const DataType&);
  void erase(const DataType&);
  void erase(iterator&);

  DataType min() const;
  DataType max() const;
  
  iterator begin() const {
    return _leftmost;
  };

  iterator end() const { 
    return _end;
  }

  size_t size() const { 
    return _tree_size;
  }

  bool empty() const {
    return _tree_size == 0;
  }

  iterator find(const DataType&);

private:
  void _transplant(const BstNodePtr&, const BstNodePtr&);
  BstNodePtr _min(const BstNodePtr&) const;

  size_t _tree_size = 0;

  BstNodePtr _root;

  /* _header is a special fake node for end() purpose.
     _header->_left is ponter to the _root of the tree. */
  BstNodePtr _header;

  /* _leftmost is an iterator on the (minimal) node that
     points on the begin() of the tree. Also, allows
     return min() for O(1). */
  iterator _leftmost;

  /* _rightmost points to the maximum node of the tree.
    Allows return max() for O(1). */
  iterator _rightmost;

  // _end always points to the _header
  iterator _end;
};

template <typename T>
void BinarySearchTree<T>::insert(const T& key) {
  /* Insert new node in the tree */

  // Create new node
  auto newNode = std::make_shared<BstNode>(key);

  // The trailing pointer at the parent of x
  BstNodePtr y = _header;

  auto x = _root;
  
  // Find appropriate position for new node
  while (x != nullptr) {
    y = x;
    if (newNode->_key < x->_key)
      x = x->_left;
    else if (newNode->_key > x->_key)
      x = x->_right;
    else
      // Force the tree to store only unique elements
      return;
  }
  
  newNode->_parent = y;
  
  if (y == _header) {
    // Tree is empty. newNode is new root.
    _root = newNode;
    _header->_left = _root;
    _leftmost._node = _root;
    _rightmost._node = _root;
  } else if (newNode->_key < y->_key) {
    y->_left = newNode;
    /* If new node < _leftmost (minimal) node.
       Than update that. */
    if (newNode->_key < _leftmost._node->_key)
      _leftmost._node = newNode;
  } else {
    y->_right = newNode;
    /* If new node > _rightmost (maximal) node.
       Than update that. */
    if (newNode->_key > _rightmost._node->_key)
      _rightmost._node = newNode;
  }
  ++_tree_size;
}

template <typename T>
typename BinarySearchTree<T>::BstNodePtr
BinarySearchTree<T>::_min(const BstNodePtr& subTree) const {
  /* Find minimal node in a sub-tree. */

  auto x = subTree;
  while (x->_left != nullptr)
    x = x->_left;
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
typename BinarySearchTree<T>::iterator
BinarySearchTree<T>::find(const T& key) {
  /* Search given key in a tree.
     Return iterator on node if it is found, else end(). */

  iterator foundNode = end();
  auto node = _root;
  while (node != nullptr)
    if (key > node->_key)
      node = node->_right;
    else if (key < node->_key)
      node = node->_left;
    else {
      foundNode = node;
      break;
    }
  return foundNode;
}

template <typename T>
void BinarySearchTree<T>::_transplant(const BstNodePtr& u, const BstNodePtr& v) {
  /* Transplant tree with root in v to u node */

  if (u->_parent == _header) {
    _root = v;
    _header->_left = v;
  } else if (u == u->_parent->_left)
    u->_parent->_left = v;
  else
    u->_parent->_right = v;

  if (v != nullptr)
    v->_parent = u->_parent;
}

template <typename T>
void BinarySearchTree<T>::erase(iterator& it) {
  /* Erase node from tree by iterator */

  auto node = it._node;

  if (node->_left == nullptr)
    _transplant(node, node->_right);
  else if (node->_right == nullptr)
    _transplant(node, node->_left);
  else {
    auto x = _min(node->_right);
    if (x->_parent != node) {
      _transplant(x, x->_right);
      x->_right = node->_right;
      x->_right->_parent = x;
    }
    _transplant(node, x);
    x->_left = node->_left;
    node->_left->_parent = x;
  }

  /* If removed node was the _leftmost node 
     than update _leftmost by incrementing. */
  if (node == _leftmost._node)
    ++_leftmost;
  
  --_tree_size;
}

template <typename T>
void BinarySearchTree<T>::erase(const T& key) {
  // Erase node by key. Initially tries to find such key in the tree

  auto node = find(key);
  
  // If node was found - remove it
  if (node != end())
    erase(node);
}

template <typename T>
typename BinarySearchTree<T>::iterator&
BinarySearchTree<T>::BstIterator::operator++() {
  /* In-order traverse. Next after _rightmost element is _header (end) */

  if (_node->_right != nullptr) {
    _node = _node->_right;
    while (_node->_left != nullptr)
      _node = _node->_left;
    return *this;
  }
  
  auto parent = _node->_parent;
  while (parent->_right == _node) {
    _node = parent;
    parent = _node->_parent;
  }  

  if (_node->_right != parent)
    _node = parent;
  
  return *this;
}

template <typename T>
void BinarySearchTree<T>::clear() {
  // Post-order traverse nodes and clear them

  auto node = _header;
  auto stack = std::stack<BstNodePtr>();
  BstNodePtr lastVisited = nullptr;
  while (!stack.empty() || node != nullptr) {
    if (node != nullptr) {
      stack.push(node);
      node = node->_left;
    } else {
      auto topNode = stack.top();
      if (topNode->_right != nullptr && lastVisited != topNode->_right)
        node = topNode->_right;
      else {
        topNode->_left = nullptr;
        topNode->_right = nullptr;
        topNode = nullptr;
        lastVisited = stack.top();
        stack.pop();
      }
    }
  }
}

} // custom namespace
#endif // BINARY_SEARCH_TREE_H
