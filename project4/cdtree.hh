/*
  cdtree.hh

  CPSC 131, Fall 2015, Prof. Kevin Wortman, Project 4

  Written in 2015 by Kevin Wortman (kwortman@fullerton.edu)

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the
  public domain worldwide. This software is distributed without any
  warranty. You should have received a copy of the CC0 Public Domain
  Dedication along with this software. If not, see
  <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#pragma once

#include <algorithm>
#include <cassert>

#include "exceptions.hh"

template <typename KEY, typename VALUE>
class CDNode {
public:
  CDNode(CDNode<KEY, VALUE>* left,
    KEY key,
    VALUE value,
    CDNode<KEY, VALUE>* right) {
      _left = left;
      _key = key;
      _value = value;
      _right = right;
      _timer = 1;
  }

  KEY key() {
    return _key;
  }

  void set_key(KEY key) {
    _key = key;
  }

  VALUE value() {
    return _value;
  }

  void set_value(VALUE value) {
    _value = value;
  }

  CDNode<KEY, VALUE>* left() {
    return _left;
  }

  void set_left(CDNode<KEY, VALUE> *left) {
    _left = left;
  }

  CDNode<KEY, VALUE>* right() {
    return _right;
  }

  void set_right(CDNode<KEY, VALUE> *right) {
    _right = right;
  }

  int timer(){
    return _timer;
  }

  void decrement_timer(){
    --_timer;
  }

  void set_timer(int timer){
    _timer = timer;
  }

private:
  KEY _key;
  VALUE _value;
  CDNode<KEY, VALUE> *_left, *_right;
  int _timer;
};

template <typename KEY, typename VALUE>
class CDTree {
public:
  CDTree() {
    _root = NULL;
    _size = 0;
  }

  ~CDTree() {
    clear();
  }

  bool is_empty() {
    return (0 == _size);
  }

  int size() {
    return _size;
  }

  VALUE get(KEY key) throw(KeyException) {
    // Use a recursive helper function to do all the work.
    CDNode<KEY, VALUE> *node = search(key, _root);
    if (NULL == node) {
      // This key isn't in the tree.
      throw KeyException();
    } else {
      // Otherwise just use the node's value getter.
      return node->value();
    }
  }

  void put(KEY key, VALUE value) {
    // Use recursive helper functions to do all the work.
    CDNode<KEY, VALUE> *node = search(key, _root);
    if (node != NULL) {
      // There's already a node for this key; update the node's value
      // member.
      node->set_value(value);
    } else {
      // Insert a new node for this key-value association.
      _root = insert(key, value, _root);
      _size++;
    }
  }

  void erase(KEY key) throw(KeyException) {
    // Use recursive helper functions to do all the work.
    if (search(key, _root) == NULL) {
      // This key isn't in the tree so we can't erase it.
      throw KeyException();
    } else {
      _root = remove(key, _root);
      _size--;
    }
  }

  void clear() {
    // Use a recursive helper function to do all the work.
    clear_helper(_root);
    _root = NULL;
    _size = 0;
  }

private:

  CDNode<KEY, VALUE> *_root;
  int _size;

  // Return the node containing query, or NULL if no such node exists.
  CDNode<KEY, VALUE>* search(KEY query, CDNode<KEY, VALUE>* subtree) {
    if (NULL == subtree) {
      // We've run down past the bottom of the tree, and never found a
      // matching node.
      return NULL;
    } else if (query < subtree->key()) {
      // Continue searching left.
      return search(query, subtree->left());
    } else if (query == subtree->key()) {
      // Found it!
      return subtree;
    } else {
      // Continue searching right.
      return search(query, subtree->right());
    }
  }

  // Insert a new node with the given key and value. The subtree must
  // not already have a node with this key. Returns a pointer to a
  // subtree that contains this new node.
  CDNode<KEY, VALUE>* insert(KEY key, VALUE value, CDNode<KEY, VALUE>* subtree)
  {
    if (NULL == subtree) {
      // Replace an empty tree with a new leaf node.
      return new CDNode<KEY, VALUE>(NULL, key, value, NULL);
    } else if (key < subtree->key()) {
      // Recursively add a node to the left subtree.
      subtree->set_left(insert(key, value, subtree->left()));
      return maintain(subtree);
    } else {
      // Confirm there's not already a node with this key.
      assert(key != subtree->key());
      // By process of elimination, key must be greater than subtree's
      // key.
      assert(key > subtree->key());
      // Recursively add a node to the right subtree.
      subtree->set_right(insert(key, value, subtree->right()));
      return maintain(subtree);
    }
  }

  // Decrement subtree's timer and rebuild subtree when necessary.
  CDNode<KEY, VALUE>* maintain(CDNode<KEY, VALUE>* subtree){
    subtree->decrement_timer();
    if (subtree->timer() > 0){
      return subtree;
    }
    else{
      int k = compute_size(subtree);
      CDNode<KEY, VALUE>** _array = new CDNode<KEY,VALUE>* [k];
      tree_to_array(_array, subtree, 0);
      subtree = array_to_tree(_array, 0, k);
      delete[] _array;
      return subtree;
    }
  }

  // Computes number of nodes in subtree
  int compute_size(CDNode<KEY,VALUE>* subtree){
    if (NULL == subtree){
      return 0;
    }
    else{
      return 1 + compute_size(subtree->left()) + compute_size(subtree->right());
    }
  }

  // Initializes an array of node pointers with all nodes of a subtree.
  int tree_to_array(CDNode<KEY, VALUE>**_array, CDNode<KEY, VALUE>* subtree,
      int start_index){
    if (NULL == subtree){
      return start_index;
    }
    else{
      start_index = tree_to_array(_array, subtree->left(), start_index);
      _array[start_index] = subtree;
      return tree_to_array(_array, subtree->right(), start_index + 1);
    }
  }

  // Rearranges all nodes with indicies between start_index and end_index into
  // a well-balanced tree and returns the root of that tree.
  CDNode<KEY, VALUE>* array_to_tree(
    CDNode<KEY, VALUE>**_array,
    int start_index,
    int end_index){

    int k = (end_index - start_index);
    if (0 == k){
      return NULL;
    }
    else{
      int middle = (start_index + end_index) / 2;
      CDNode<KEY, VALUE>* root = _array[middle];
      root->set_left(array_to_tree(_array, start_index, middle));
      root->set_right(array_to_tree(_array, middle+1, end_index));
      if (k >= 3){
        root->set_timer(k / 3);
      }
      else{
        root->set_timer(1);
      }
      return root;
    }
  }

  // Remove the node containing key query from subtree. This function
  // assumes that subtree actually does contain such a
  // node. Therefore, subtree must not be NULL. Returns a pointer to
  // a subtree that does not include the offending node.
  CDNode<KEY, VALUE>* remove(KEY query, CDNode<KEY, VALUE>* subtree) {

    assert(NULL != subtree);

    // We will refer to these data members many times, so it's easier
    // to save them in local variables than to call the getters over
    // and over.
    KEY key = subtree->key();
    CDNode<KEY, VALUE> *left = subtree->left(),
                        *right = subtree->right();

    if (query < key) {
      // Continue searching left.
      subtree->set_left(remove(query, left));
      return subtree;
    } else if (query > key) {
      // Continue searching right.
      subtree->set_right(remove(query, right));
      return subtree;
      // if we get past this if, we know by process of elimination
      // that (query == key)
    } else if ((NULL == left) && (NULL == right)) {
      // We've reached a leaf which, by process of elimination, must
      // be the node we need to delete. Just delete it and we're done.
      assert(query == key);
      delete subtree;
      return NULL;
    } else if (NULL == left) {
      // There is a right child but no left, so we can simply delete
      // this node and move the right child into the "hole" left
      // behind.
      assert(query == key);
      delete subtree;
      return right;
    } else if (NULL == right) {
      // Symmetrically, if there's no right child, the left child
      // takes the place of this node.
      assert(query == key);
      delete subtree;
      return left;
    } else {
      // Tricky case: this node contains query, and has two children.
      assert(query == key);
      assert(left != NULL);
      assert(right != NULL);
      // Find the node containing the key immediately following query
      // in an inorder traversal.
      CDNode<KEY, VALUE>* successor = left_leaf(right);
      assert(NULL != successor);
      // Move that node's key and value here.
      subtree->set_key(successor->key());
      subtree->set_value(successor->value());
      // We've successfully removed query from the tree, but now there
      // are two copies of successor. We fix this by recursively
      // deleting the deeper copy, which must be in the right subtree.
      subtree->set_right(remove(query, right));
      return subtree;
    }
  }

  CDNode<KEY, VALUE>* left_leaf(CDNode<KEY, VALUE>* subtree) {
    assert(NULL != subtree);
    if (NULL == subtree->left()) {
      return subtree;
    } else {
      return left_leaf(subtree->left());
    }
  }

  void clear_helper(CDNode<KEY, VALUE>* subtree) {
    if (NULL != subtree) {
      clear_helper(subtree->left());
      clear_helper(subtree->right());
      delete subtree;
    }
  }
};
