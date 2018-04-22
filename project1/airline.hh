/*
  airline.hh

  CPSC 131, Fall 2015, Prof. Kevin Wortman, Project 1

  STUDENT NAME: Harkishan Grewal

  Written in 2015 by Kevin Wortman (kwortman@fullerton.edu)

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the
  public domain worldwide. This software is distributed without any
  warranty. You should have received a copy of the CC0 Public Domain
  Dedication along with this software. If not, see
  <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#pragma once

#include <string>

// ENUMS

// Side of an airplane, port or starboard. These terms are more
// precise than "left" and "right," which vary depending on whether
// you're facing forward or backward.
enum Side { PORT, STARBOARD };

class Passenger;

// EXCEPTIONS

// Each of these exception classes follows the conventional pattern,
// of having straightforward data members, a constructor, getters, and
// nothing else.

// A function argument is invalid.
class ArgumentException {
public:
  ArgumentException(const char* description);

  const char* description();

private:
  const char* _description;
};

// Airplane has run out of storage bins.
class BinSpaceException {
public:
  BinSpaceException() { }
};

// Class instance is in an invalid state.
class InvalidStateException {
public:
  InvalidStateException(const char* description) throw(ArgumentException);

  const char* description();

private:
  const char* _description;
};

// Two passengers are trying to sit in the same seat.
class SeatConflictException {
public:
  // first is the passenger that sat down first, second is the
  // passenger that is trying to sit down second.
  SeatConflictException(Passenger* first, Passenger* second) throw(ArgumentException);

  Passenger* first();
  Passenger* second();

private:
  Passenger *_first, *_second;
};

// A seat is unexpectedly vacant.
class VacantException {
public:
  VacantException(int row, int seat) throw(ArgumentException);

  int row();
  int seat();

private:
  int _row, _seat;
};

// CLASSES

// Represents a carryon bag owned by a passenger.
class Bag {
public:
  // owner must be a valid pointer to a Passenger object. A bag is
  // initialized not "stowed," meaning that it hasn't been stored in a
  // bin.
  Bag(Passenger* owner) throw(ArgumentException);

  // getters
  Passenger* owner();

  // Return true if the bag is stowed.
  bool is_stowed();

  // Stow the bag at the given bin location. This bag must not already
  // be stowed; throw InvalidStateException if the bag was already
  // stowed.
  void stow(Side side, int row) throw(InvalidStateException);

  // Getters for the stow location. Throw InvalidStateException if the
  // bag has not been stowed yet.
  Side side() throw(InvalidStateException);
  int row() throw(InvalidStateException);

private:
  // TODO: add appropriate data members
};

// Represents one passenger, who may or may not have one carryon bag.
class Passenger {
public:
  // Create a passenger. id is a unique number which must be
  // positive. row and seat designate a seat location, which each must
  // also be positive. The passenger is created with no carryon yet.
  Passenger(int id, int row, int seat) throw(ArgumentException);

  // getters
  int id();
  int row();
  int seat();

  // Getters and setters for the carryon.
  bool has_carryon();
  // Set the passenger's carryon to this bag.
  void set_carryon(Bag* bag) throw(ArgumentException);
  // carryon getter. Throw InvalidStateException if the passenger has
  // no carryon defined.
  Bag* carryon() throw(InvalidStateException);

private:
  // TODO: add appropriate data members
};

// Represents a model of airplane.
class Airplane {
 public:
  // Initialize an airplane with a given number of rows of seats, and
  // width (number of passengers per row). Each argument must be
  // positive.
  Airplane(int rows, int width) throw(ArgumentException);

  // getters
  int rows();
  int width();

 private:
  // TODO: add appropriate data members
};

// Represents the entire process of getting passengers and carryon
// bags loaded onto an airplane.
class BoardingProcess {
public:
  // Initialize with an empty cabin, based on the given airplane. Each
  // row has (width) seats, so there are a total of (width) * (height)
  // seats available. In addition, each row has two storage bins, one
  // on the port side and the other on the starboard side. All seats
  // and bins are initially empty.
  BoardingProcess(Airplane* airplane) throw(ArgumentException);
  ~BoardingProcess();

  // Return true if the given seat location is occupied with a passenger.
  bool is_seat_occupied(int row, int seat) throw(ArgumentException);
  // Return a pointer to the passenger at the given seat
  // location. Throws VacantException if that seat is empty.
  Passenger* passenger_at(int row, int seat) throw(ArgumentException, VacantException);

  // Return true if the given bin location is occupied with a bag.
  bool is_bin_full(Side side, int row) throw(ArgumentException);

  // Place the given passenger at their assigned seat.
  //
  // First, if the passenger has a carryon, try to find a location for
  // it. Try row 1 port side; if full, try row 1 starboard side; if
  // full, try row 2 port side; if full, try row 2 starboard side; if
  // full, try row 3 port side. And so on. If a vacant bin is found,
  // call the carryon's stow() function to record where the bag is. If
  // no bin is available, throw BinSpaceException.
  //
  // Then, try to place the passenger at their assigned seat. If
  // another passenger is somehow already sitting there, throw
  // SeatConflictException.
  //
  // When both the passenger and bag (if any) are succesfully placed,
  // update member variables to record where they are located, and do
  // not throw any exceptions.
  void seat_passenger(Passenger* passenger) throw(SeatConflictException, BinSpaceException);

private:
  // TODO: add appropriate data members
};
