/*
  airline.cc

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

#include <cassert>

#include "airline.hh"

using namespace std;

ArgumentException::ArgumentException(const char* description) {
  assert(description != NULL);
  _description = description;
}

const char* ArgumentException::description() {
  return _description;
}

InvalidStateException::InvalidStateException(const char* description)
  throw(ArgumentException) {

  if (NULL == description)
    throw ArgumentException("null pointer");

  _description = description;
}

const char* InvalidStateException::description() {
  return _description;
}
SeatConflictException::SeatConflictException(Passenger* first, Passenger* second)
  throw(ArgumentException) {

  if ((NULL == first) ||
      (NULL == second))
    throw ArgumentException("null pointer");

  _first = first;
  _second = second;
}

Passenger* SeatConflictException::first() {
  return _first;
}

Passenger* SeatConflictException::second() {
  return _second;
}

VacantException::VacantException(int row, int seat)
  throw(ArgumentException) {

  if (row < 1)
    throw ArgumentException("invalid row");
  if (seat < 1)
    throw ArgumentException("invalid seat");

  _row = row;
  _seat = seat;
}

int VacantException::row() {
  return _row;
}

int VacantException::seat() {
  return _seat;
}

// TODO: write definitions for all the other member functions declared
// in airline.hh
