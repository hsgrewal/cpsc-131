/*
  test_main.cc

  CPSC 131, Fall 2015, Prof. Kevin Wortman, Project 1

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

#include "airline.hh"

using namespace std;

int main() {
  const char* DESCRIPTION = "test string";
  bool thrown;

  cout << "TEST 1: constructors" << endl;

  thrown = false;
  try {
    throw ArgumentException(DESCRIPTION);
  } catch (ArgumentException e) {
    assert(DESCRIPTION == e.description());
    thrown = true;
  }
  assert(thrown);

  thrown = false;
  try {
    throw BinSpaceException();
  } catch (BinSpaceException e) {
    thrown = true;
  }
  assert(thrown);

  thrown = false;
  try {
    throw InvalidStateException(DESCRIPTION);
  } catch (InvalidStateException e) {
    assert(DESCRIPTION == e.description());
    thrown = true;
  }
  assert(thrown);

  {
    Passenger p1(1, 1, 1), p2(2, 1, 2);
    thrown = false;
    try {
      throw SeatConflictException(&p1, &p2);
    } catch (SeatConflictException e) {
      assert(&p1 == e.first());
      assert(&p2 == e.second());
      thrown = true;
    }
    assert(thrown);
  }

  thrown = false;
  try {
    throw VacantException(1, 2);
  } catch (VacantException e) {
    assert(1 == e.row());
    assert(2 == e.seat());
    thrown = true;
  }
  assert(thrown);

  {
    Passenger owner(1, 1, 1);
    Bag obj(&owner);
    assert(false == obj.is_stowed());
  }

  {
    Passenger obj(1, 2, 3);
    assert(1 == obj.id());
    assert(2 == obj.row());
    assert(3 == obj.seat());
    assert(false == obj.has_carryon());
  }

  {
    Airplane obj(3, 4);
    assert(3 == obj.rows());
    assert(4 == obj.width());
  }

  {
    Airplane a(3, 4);
    BoardingProcess obj(&a);
  }

  cout << "TEST 2: constructor argument exceptions" << endl;

  thrown = false;
  try {
    InvalidStateException obj(NULL);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    Passenger p1(1, 1, 1);
    SeatConflictException obj(NULL, &p1);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    Passenger p1(1, 1, 1);
    SeatConflictException obj(&p1, NULL);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    VacantException obj(0, 1);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    VacantException obj(1, 0);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    Bag obj(NULL);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    Passenger obj(0, 2, 3);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    Passenger obj(1, 0, 2);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    Passenger obj(1, 2, 0);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    Airplane obj(0, 8);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    Airplane obj(24, 0);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  thrown = false;
  try {
    BoardingProcess obj(NULL);
  } catch (ArgumentException e) {
    thrown = true;
  }
  assert(true == thrown);

  cout << "TEST 3: Bag business logic" << endl;

  {
    Passenger owner(1, 1, 1);
    Bag bag(&owner);

    // owner is preserved
    assert(&owner == bag.owner());

    // starts out not stowed
    assert(false == bag.is_stowed());

    // side getter throws exception while not stowed
    thrown = false;
    try {
      bag.side();
    } catch(InvalidStateException e) {
      thrown = true;
    }
    assert(thrown);

    // row getter throws exception while not stowed
    thrown = false;
    try {
      bag.row();
    } catch(InvalidStateException e) {
      thrown = true;
    }
    assert(thrown);

    // stow operation makes bag stowed
    bag.stow(PORT, 7);
    assert(true == bag.is_stowed());

    // getters now work without exceptions
    assert(PORT == bag.side());
    assert(7 == bag.row());
  }

  cout << "TEST 4: Passenger business logic" << endl;

  {
    Passenger passenger(1, 2, 3);

    // getters
    assert(1 == passenger.id());
    assert(2 == passenger.row());
    assert(3 == passenger.seat());

    // start without a carryon
    assert(false == passenger.has_carryon());

    // getter throws exceptions when appropriate
    thrown = false;
    try {
      passenger.carryon();
    } catch (InvalidStateException e) {
      thrown = true;
    }
    assert(true == thrown);

    // set carryon
    Bag bag(&passenger);
    passenger.set_carryon(&bag);
    assert(&bag == passenger.carryon());
  }

  cout << "TEST 5: BoardingProcess business logic" << endl;

  {
    Airplane plane(3, 4);
    BoardingProcess boarding(&plane);

    // throw exception for invalid row
    thrown = false;
    try {
      boarding.is_seat_occupied(-1, 2);
    } catch (ArgumentException e) {
      thrown = true;
    }
    assert(true == thrown);

    // throw exception for invalid seat
    thrown = false;
    try {
      boarding.is_seat_occupied(1, -1);
    } catch (ArgumentException e) {
      thrown = true;
    }
    assert(true == thrown);

    // all bins start out empty
    for (int row = 1; row <= 3; ++row) {
      assert(false == boarding.is_bin_full(PORT, row));
      assert(false == boarding.is_bin_full(STARBOARD, row));
    }

    // all seats start out empty
    for (int row = 1; row <= 3; ++row) {
      for (int seat = 1; seat <= 4; ++seat) {
        assert(false == boarding.is_seat_occupied(row, seat));
      }
    }

    // VacantException
    thrown = false;
    try {
      boarding.passenger_at(1, 1);
    } catch (VacantException e) {
      thrown = true;
    }
    assert(true == thrown);

    // succesfully seat a passenger
    Passenger p1(1, 2, 3);
    boarding.seat_passenger(&p1);
    assert(true == boarding.is_seat_occupied(2, 3));
    assert(&p1 == boarding.passenger_at(2, 3));

    // SeatConflictException
    Passenger p2(2, 2, 3);
    thrown = false;
    try {
      boarding.seat_passenger(&p2);
    } catch (SeatConflictException e) {
      thrown = true;
      assert(&p1 == e.first());
      assert(&p2 == e.second());
    }
    assert(true == thrown);

    // bins start to get full
    // passenger 3 puts their carryon in port row 1
    Passenger p3(3, 1, 1);
    Bag b3(&p3);
    p3.set_carryon(&b3);
    boarding.seat_passenger(&p3);
    assert(true == boarding.is_bin_full(PORT, 1));
    // passenger 4 puts their carryon in starboard row 1
    Passenger p4(4, 1, 2);
    Bag b4(&p4);
    p4.set_carryon(&b4);
    boarding.seat_passenger(&p4);
    assert(true == boarding.is_bin_full(STARBOARD, 1));
    // passenger 5 puts their carryon in port row 2
    Passenger p5(5, 1, 3);
    Bag b5(&p5);
    p5.set_carryon(&b5);
    boarding.seat_passenger(&p5);
    assert(true == boarding.is_bin_full(PORT, 2));
  }

  cout << "TEST 6: all bins full" << endl;

  {
    Airplane plane(2, 20); // two rows = only 4 bins
    BoardingProcess boarding(&plane);
    Passenger *passengers[5];
    Bag* bags[5];
    // create 5 passengers each with a bag
    for (int i = 0; i < 5; ++i) {
      passengers[i] = new Passenger(i+1, 1, i+1);
      bags[i] = new Bag(passengers[i]);
      passengers[i]->set_carryon(bags[i]);
    }
    // seat the first 4, no problem
    for (int i = 0; i < 4; ++i) {
      boarding.seat_passenger(passengers[i]);
    }
    // passenger 5 throws BinSpaceException
    thrown = false;
    try {
      boarding.seat_passenger(passengers[4]);
    } catch (BinSpaceException e) {
      thrown = true;
    }
    assert(thrown);
    // free heap objects
    for (int i = 0; i < 5; ++i) {
      delete passengers[i];
      delete bags[i];
    }
  }

  return 0;
}
