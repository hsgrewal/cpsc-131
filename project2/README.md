# Project 2: B-list

## Introduction
In this project, a *B-list* is implemented. *B-list* is a hybrid data
structure that combines the ideas of a doubly linked list and a fixed-
capacity vector (a.k.a partially-filled array).

## *B-list* Data Structure
A *B-list* is a deque data structure based on a doubly linked list; except
that, instead of each node storing one element, each node may store anywhere
between 1 and **_B_** elements, where **_B_** is some constant value greater
than 1. So if **_B = 4_**, then each node object in the *B-list* stores 1,
2, 3, or 4 elements.

The *B-list* is inspired by another data structure called a *B-tree*. Plain
binary search trees use nodes, and each node stores exactly one element.
However, there is a variation on a binary search tree called a *B-tree* that
stores multiple elements in each node. *B-trees* were invented in response
to the observation that node objects involve a lot of overhead. Since each
node stores 1 element and 2 pointers, only about ⅓ of the variables in a
doubly-linked list go toward actually storing elements; the other ⅔ goes to
overhead. If each node stores many elements, the proportion of space going
toward overhead is reduced. [More about *B-trees*](https://en.wikipedia.org/wiki/B-tree)

### Files
The following files are present in this project:

1. `blist.hh` - a header file that declares the `BList` class

2. `test_main.cc` - a source file for a program that uses the `assert(...)`
  function to test whether the `BList` class works properly

3. `exceptions.hh` - a header file that declares the various exceptions

### Sample Output
Correct run of `test_main.cc`:
```
BList tests:

BList::BList
BList::add_back
BList::is_empty
BList::size
BList::front
BList::back
BList::add_front
BList::remove_front
BList::remove_back
BList::get
BList::set
```
