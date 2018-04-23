# Project 4: Countdown Trees

## Introduction
In this project, a *countdown tree* is implemented. A *countdown tree* is
a kind of self-balancing binary search tree. Countdown trees are
significantly simpler than AVL trees, but their performance is slightly
worse.

### Files
The following files are present in this project:

1. `cdtree.hh` - a header file that declares declares a ​`CDNode` ​
  and ​`CDTree` class

2. `test_main.cc` - a source file for a program that uses the `assert(...)`
  function to test whether the countdown tree works properly. First, it puts
  many random keys and values into the tree, and checks that the countdown
  tree gets the same results as an STL ​map. Then, it inserts strictly
  increasing keys, which triggers the worst-case performance of a plain BST.

3. `exceptions.hh` - a header file that declares the various exceptions

### Sample Output
Correct run of `test_main.cc`:
```
validation with std::map...
clear...
worst case...
```
