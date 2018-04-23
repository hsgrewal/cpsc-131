/*
  test_main.cc

  CPSC 131, Fall 2015, Prof. Kevin Wortman, Project 4

  Written in 2015 by Kevin Wortman (kwortman@fullerton.edu)

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the
  public domain worldwide. This software is distributed without any
  warranty. You should have received a copy of the CC0 Public Domain
  Dedication along with this software. If not, see
  <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <cassert>
#include <iostream>
#include <map>

#include "cdtree.hh"

using namespace std;

int main() {

  const int N = 50*1000;

  // test CDTree's constructor
  CDTree<int, int> cd_tree;
  assert(cd_tree.is_empty());
  assert(0 == cd_tree.size());

  // insert N random keys and values, into both a CDTree, and also an
  // STL map that we'll check against
  cout << "validation with std::map...";
  map<int, int> stl_tree;
  for (int i = 0; i < N; ++i) {
    int key = rand(), value = rand();
    
    stl_tree[key] = value;

    cd_tree.put(key, value);
    assert(!cd_tree.is_empty());
  }
  // now check that the CDTree's contents agree with the map's
  for (map<int, int>::iterator i = stl_tree.begin(); i != stl_tree.end(); ++i) {
    int key = i->first, value = i->second;
    assert(value == cd_tree.get(key));
  }
  cout << endl;

  // clear the CDTree and make sure it really is empty
  cout << "clear...";
  cd_tree.clear();
  assert(cd_tree.is_empty());
  assert(0 == cd_tree.size());
  cout << endl;

  // intentionally trigger the worst-case scenario for non-balancing
  // BST: put many increasing keys
  cout << "worst case...";
  for (int i = 0; i < N; ++i) {
    cd_tree.put(i, i);
  }
  cout << endl;

  return 0;
}
