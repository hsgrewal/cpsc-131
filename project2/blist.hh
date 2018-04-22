/*
  blist.hh

  CPSC 131, Fall 2015, Prof. Kevin Wortman, Project 2

  Written in 2015 by Kevin Wortman (kwortman@fullerton.edu)

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the
  public domain worldwide. This software is distributed without any
  warranty. You should have received a copy of the CC0 Public Domain
  Dedication along with this software. If not, see
  <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#pragma once

#include <deque>

#include "exceptions.hh"

const int B_NODE_CAPACITY = 16;

// Create a template class called BNode that represents a
// doubly-linked node holding a fixed-capacity array of
// B_NODE_CAPACITY elements.
template <typename ELEMENT>
class BList {
public:
  BList() {}

  ~BList() {}

  bool is_empty() { return _deque.empty(); }

  int size() { return _deque.size(); }

  ELEMENT front() throw(UnderflowException) {
    check_nonempty();
    return _deque.front();
  }

  ELEMENT back() throw(UnderflowException) {
    check_nonempty();
    return _deque.back();
  }

  void add_front(ELEMENT e) { _deque.push_front(e); }

  void add_back(ELEMENT e) { _deque.push_back(e); }

  void remove_front() throw(UnderflowException) {
    check_nonempty();
    _deque.pop_front();
  }

  void remove_back() throw(UnderflowException) {
    check_nonempty();
    _deque.pop_back();
  }

  ELEMENT get(int index) throw(IndexException) {
    check_index(index);
    return _deque[index];
  }

  void set(int index, ELEMENT e) throw(IndexException) {
    check_index(index);
    _deque[index] = e;
  }

  void clear() { _deque.clear(); }

private:
  std::deque<ELEMENT> _deque;

  void check_nonempty() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();
  }

  void check_index(int index) throw(IndexException) {
    if (! ((index >= 0) && (index < size())) )
      throw IndexException(size(), index);
  }

};
