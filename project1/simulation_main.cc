/*
  simulation_main.cc

  CPSC 131, Fall 2015, Prof. Kevin Wortman, Project 1

  Written in 2015 by Kevin Wortman (kwortman@fullerton.edu)

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the
  public domain worldwide. This software is distributed without any
  warranty. You should have received a copy of the CC0 Public Domain
  Dedication along with this software. If not, see
  <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "airline.hh"

using namespace std;

void print_usage() {
}

int main(int argc, char** argv) {

  if (argc != 5) {
  cerr << "usage: simulation <SEED> <ROWS> <WIDTH> <PASSENGER COUNT>" << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  if ((seed < 0) || (seed == INT_MAX)) {
    cerr << "seed must be in [0, INT_MAX)" << endl;
    return 1;
  }
  int rows = atoi(argv[2]);
  if ((rows < 1) || (rows > 99)) {
    cerr << "rows must be between 1 and 99" << endl;
    return 1;
  }
  int width = atoi(argv[3]);
  if ((width < 1) || (width > 99)) {
    cerr << "width must be between 1 and 99" << endl;
    return 1;
  }
  int passenger_count = atoi(argv[4]);
  if (passenger_count < 0) {
    cerr << "passenger count must be positive" << endl;
    return 1;
  }

  cout << "Airline simulation with "
       << rows << " rows, "
       << width << " width, and "
       << passenger_count << " passengers"
       << endl;

  Airplane plane(rows, width);
  BoardingProcess boarding(&plane);

  Passenger* passengers[passenger_count];
  Bag* bags[passenger_count];
  {
    int row = 1, seat = 1;
    for (int i = 0; i < passenger_count; ++i) {
      passengers[i] = new Passenger(i+1, row, seat);
      bags[i] = new Bag(passengers[i]);
      passengers[i]->set_carryon(bags[i]);

      seat++;
      if (seat == width) {
        row++;
        seat = 1;
      }
    }
  }

  vector<Passenger*> unseated(passengers, passengers + passenger_count);
  srand(0);
  bool halt = false;
  for (int i = 0; (!halt) && (i < passenger_count); ++i) {
    int j = rand() % unseated.size();
    Passenger* now = unseated[j];
    unseated.erase(unseated.begin() + j);

    try {
      boarding.seat_passenger(now);
      cout << "passenger " << now->id()
          << " seated at row " << now->row()
          << ", seat " << now->seat()
          << " and their carryon is in row " << now->carryon()->row()
          << " on " << (now->carryon()->side() == PORT ? "port" : "starboard")
          << " side" << endl;
    } catch (SeatConflictException e) {
      cout << "SEAT CONFLICT between passengers " << e.first()->id()
          << " and " << e.second()->id() << endl;
      halt = true;
    } catch (BinSpaceException e) {
      cout << "ALL BINS FULL" << endl;
      halt = true;
    }
  }

  if (!halt) {
    cout << "SUCCESS" << endl;
  }

  for (int i = 0; i < passenger_count; ++i) {
    delete passengers[i];
    delete bags[i];
  }

  return 0;
}
