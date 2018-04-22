/*
  test_main.cc

  CPSC 131, Fall 2015, Prof. Kevin Wortman, Project 2

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

#include "blist.hh"

using namespace std;

// This main() function performs unit tests to confirm that the BList
// class is implemented properly.
int main() {
  cout << "BList tests:" << endl << endl;

  BList<int> empty, one, three, thousand;
  bool thrown;

  // Try to construct lists with 0, 1, 3, and 1000 elements
  // respectively.
  cout << "BList::BList" << endl;
  cout << "BList::add_back" << endl;
  assert(empty.is_empty());
  assert(one.is_empty());
  assert(three.is_empty());
  assert(thousand.is_empty());
  assert(0 == empty.size());
  assert(0 == one.size());
  assert(0 == three.size());
  assert(0 == thousand.size());
  for (int i = 0; i < 1000; i++) {
    if (i < 1) {
      one.add_back(i);
      assert(!one.is_empty());
      assert(one.size() == (i+1));
    }
    if (i < 3) {
      three.add_back(i);
      assert(three.size() == (i+1));
    }
    thousand.add_back(i);
      assert(thousand.size() == (i+1));
  }

  cout << "BList::is_empty" << endl;
  assert(empty.is_empty());
  assert(!one.is_empty());
  assert(!three.is_empty());
  assert(!thousand.is_empty());

  cout << "BList::size" << endl;
  assert(0 == empty.size());
  assert(1 == one.size());
  assert(3 == three.size());
  assert(1000 == thousand.size());

  cout << "BList::front" << endl;
  thrown = false;
  try {
    empty.front();
  } catch (UnderflowException x) {
    thrown = true;
  }
  assert(thrown);
  assert(0 == one.front());
  assert(0 == three.front());
  assert(0 == thousand.front());

  cout << "BList::back" << endl;
  thrown = false;
  try {
    empty.front();
  } catch (UnderflowException x) {
    thrown = true;
  }
  assert(thrown);
  assert(0 == one.back());
  assert(2 == three.back());
  assert(999 == thousand.back());

  cout << "BList::add_front" << endl;
  {
    BList<int> hundred;
    for (int i = 0; i < 100; i++) {
      hundred.add_front(i);
      assert(!hundred.is_empty());
      assert(hundred.size() == (i+1));
      assert(hundred.front() == i);
      assert(hundred.back() == 0);
    }
  }

  cout << "BList::remove_front" << endl;
  cout << "BList::remove_back" << endl;

  thrown = false;
  try {
    empty.remove_front();
  } catch (UnderflowException x) {
    thrown = true;
  }
  assert(thrown);

  thrown = false;
  try {
    empty.remove_back();
  } catch (UnderflowException x) {
    thrown = true;
  }
  assert(thrown);

  {
    BList<int> hundred;
    for (int i = 0; i < 100; i++)
      hundred.add_back(i);
    // simultaneously remove elements from both ends
    for (int f = 0, b = 99; f < 50; f++, b--) {
      assert(!hundred.is_empty());
      assert(hundred.front() == f);
      assert(hundred.back() == b);
      hundred.remove_front();
      hundred.remove_back();
    }
    assert(hundred.is_empty());
  }

  cout << "BList::get" << endl;

  thrown = false;
  try {
    three.get(-1);
  } catch (IndexException x) {
    thrown = true;
  }
  assert(thrown);

  thrown = false;
  try {
    three.get(3);
  } catch (IndexException x) {
    thrown = true;
  }
  assert(thrown);

  for (int i = 0; i < 1000; i++) {
    assert(thousand.get(i) == i);
  }

  cout << "BList::set" << endl;

  thrown = false;
  try {
    three.set(-1, 0);
  } catch (IndexException x) {
    thrown = true;
  }
  assert(thrown);

  thrown = false;
  try {
    three.set(3, 0);
  } catch (IndexException x) {
    thrown = true;
  }
  assert(thrown);

  {
    BList<int> hundred;
    for (int i = 0; i < 100; i++)
      hundred.add_back(i);
    for (int i = 0; i < 100; i++) {
      hundred.set(i, -i);
      assert(hundred.get(i) == -i);
    }
  }

  return 0;
}
