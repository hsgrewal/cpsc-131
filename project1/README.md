# Project 1: OO Programming

## Introduction
In this project, an object-oriented (OO) C++ modules involving several
interrelated classes is written. The module implements a simulation of
the boarding process of an airplane, in which a set of passengers attempt
to stow their carry-on bags and take their assigned seats in an orderly
fashion.

The primary focus of the project is on using essential OOP features
appropriately: classes, pointers, encapsulation, exceptions, and modularity.

### Files
The following files are present in this project:

1. `airline.hh` - a header file that declares the `Bag`, `Passenger`,
  `Airplane`, and `BoardingProcess` classes as well as related exception
  classes and an enum type

2. `airline.cc` - corresponding C++ source file

3. `test_main.cc` - source file for a program, based upon the airline module,
  that uses the `assert(...)` function to test whether the airline classes
  work properly

4. `simulation_main.cc` - source file for a program that uses the airline
  module to simulate a pseudo-random boarding process. It is a terminal
  program that takes some key parameters as command-line arguments,
  simulates the boarding process, and prints a summary of the process to
  standard output

5. `Makefile` - a control file for the `make` utility available in Linux
  and other Unix-like command-line environments

### Sample Output
Correct run of `test_main.cc`:
```
$ ./test
TEST 1: constructors
TEST 2: constructor argument exceptions
TEST 3: Bag business logic
TEST 4: Passenger business logic
TEST 5: BoardingProcess business logic
TEST 6: all bins full
```

Simulation where all bins are full:
```
$ ./simulation 0 5 4 12
Airline simulation with 5 rows, 4 width, and 12 passengers
passenger 8 seated at row 3, seat 2 and their carryon is in row 1 on port side
passenger 12 seated at row 4, seat 3 and their carryon is in row 1 on starboard side
passenger 9 seated at row 3, seat 3 and their carryon is in row 2 on port side
passenger 10 seated at row 4, seat 1 and their carryon is in row 2 on starboard side
passenger 2 seated at row 1, seat 2 and their carryon is in row 3 on port side
passenger 5 seated at row 2, seat 2 and their carryon is in row 3 on starboard side
passenger 7 seated at row 3, seat 1 and their carryon is in row 4 on port side
passenger 4 seated at row 2, seat 1 and their carryon is in row 4 on starboard side
passenger 3 seated at row 1, seat 3 and their carryon is in row 5 on port side
passenger 6 seated at row 2, seat 3 and their carryon is in row 5 on starboard side
ALL BINS FULL
```

Simulation where no issues arise:
```
$ ./simulation 0 5 4 8
Airline simulation with 5 rows, 4 width, and 8 passengers
passenger 8 seated at row 3, seat 2 and their carryon is in row 1 on port side
passenger 5 seated at row 2, seat 2 and their carryon is in row 1 on starboard side
passenger 4 seated at row 2, seat 1 and their carryon is in row 2 on port side
passenger 1 seated at row 1, seat 1 and their carryon is in row 2 on starboard side
passenger 3 seated at row 1, seat 3 and their carryon is in row 3 on port side
passenger 6 seated at row 2, seat 3 and their carryon is in row 3 on starboard side
passenger 2 seated at row 1, seat 2 and their carryon is in row 4 on port side
passenger 7 seated at row 3, seat 1 and their carryon is in row 4 on starboard side
SUCCESS
```
