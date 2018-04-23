/*
  project2.cc

  CPSC 131, Fall 2015, Prof. Kevin Wortman, Project 3

  STUDENT NAME(S): Harkishan Grewal

  Written in 2015 by Kevin Wortman (kwortman@fullerton.edu)

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the
  public domain worldwide. This software is distributed without any
  warranty. You should have received a copy of the CC0 Public Domain
  Dedication along with this software. If not, see
  <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <algorithm>
#include <cassert>
#include <chrono>
#include <forward_list>
#include <iostream>
#include <list>
#include <fstream>
#include <set>
#include <string>
#include <vector>

// Maximum number of elements, in units of thousands.
const int MAX_N_IN_THOUSANDS = 200;

// Our test elements will be random strings; this is the length of
// each random string.
const int STRING_DIGITS = 8;

// Random number seed. This is a constant so that the program will
// behave consistently from run to run.
const int SEED = 0xCAFECAFE;

using namespace std;

// This class functions as a stopwatch, making accurate readings of
// code execution time. The timer may be in one of three states: never
// used, running, or stopped. To use the timer, you start it, then do
// whatever you want to be timed, then stop the timer. In the stopped
// state, the timer can report the number of seconds elapsed between
// when it was started and stopped.
class Timer {
public:
  Timer() {
    _state = TIMER_NEVER_STARTED;
  }

  // Start the timer. The timer must not already be running.
  void start() {
    assert(_state != TIMER_RUNNING);
    _state = TIMER_RUNNING;
    _start = chrono::high_resolution_clock::now();
  }

  // Stop the timer. The timer must be currently running.
  void stop() {
    assert(_state == TIMER_RUNNING);
    _end = chrono::high_resolution_clock::now();
    _state = TIMER_STOPPED;
  }

  // Return the number of seconds elapsed in the previous start-stop
  // interval. The timer must currently be stopped.
  double elapsed_seconds() {
    assert(_state == TIMER_STOPPED);
    int microseconds = chrono::duration_cast<chrono::microseconds>(_end - _start).count();
    double seconds = microseconds / 1E6;
    return seconds;
  }

private:

  enum State { TIMER_NEVER_STARTED, TIMER_RUNNING, TIMER_STOPPED };

  State _state;
  chrono::high_resolution_clock::time_point _start, _end;
};

// This class keeps a log of elapsed times for a particular
// operation. Each entry is a value of n and an elapsed time in
// seconds. It can write all its entries to a spreadsheet in CSV
// format.
class DataLog {
public:

  DataLog () { }

  // Remove all entries.
  void clear() {
    _entries.clear();
  }

  // Add an entry.
  void record(int n, double seconds) {
    _entries.push_back(Entry(n, seconds));
  }

  // Write all entries to a spreadsheet in CSV format. The first
  // column contains n values and the second column contains elapsed
  // time values. Returns true on success or false on an I/O error.
  bool write_csv(string& filename) {
    ofstream f(filename.c_str());
    if (!f)
      return false;

    f << "n, time (seconds)" << endl;
    for (vector<Entry>::iterator i = _entries.begin(); i != _entries.end();
      ++i) {
      f << i->n << ", " << i->seconds << endl;
    }

    bool failed = f.fail();

    f.close();

    return !failed;
  }

private:

  // Private struct representing one entry.
  struct Entry {
    int n;
    double seconds;

    Entry(int _n, double _seconds) {
      n = _n;
      seconds = _seconds;
    }
  };

  vector<Entry> _entries;
};

// Generates one pseudorandom string containing exactly STRING_DIGITS
// upper case letters.
string random_string() {
  string s;

  for (int j = 0; j < STRING_DIGITS; ++j) {
    char c = 'A' + (rand() % 26);
    s.push_back(c);
  }

  assert(s.size() == STRING_DIGITS);

  return s;
}

int main() {

  // Compute the values of n we will use: 1000, 2000, ...,
  // (MAX_N_IN_THOUSANDS * 100) .
  vector<int> n_values;
  for (int thousand = 1; thousand <= MAX_N_IN_THOUSANDS; ++thousand) {
    n_values.push_back(thousand * 1000);
  }

  // Generating random strings is relatively slow, so we create one
  // large set of strings to reuse across all trials.
  cout << "generating test data...";
  vector<string> random_strings;
  for (int i = 0; i < n_values.back(); ++i) {
    random_strings.push_back(random_string());
  }
  cout << endl;

  // Create other objects that will be reused.
  Timer timer;
  DataLog data;
  string operation_name, filename;

  // List (doubly-linked list): add to front
  // In theory, each operation should take O(1) time.
  operation_name = "list_add_front";
  cout << operation_name << endl;
  data.clear();
  // Loop through each n value.
  for (vector<int>::iterator i = n_values.begin(); i != n_values.end(); ++i) {
    // Get the current n value out of the iterator object.
    int n = *i;

    // Construct a list of size n, using the first n elements of random_strings.
    list<string> the_list(random_strings.begin(), random_strings.begin() + n);
    string element = random_string();

    // Start timer
    timer.start();
    // Push new element to front of doubly-linked list
    the_list.push_front(element);
    // Stop the timer
    timer.stop();

    // Get elapsed time.
    double et = timer.elapsed_seconds();

    // Print a status update since this takes a long time.
    cout << "    n=" << n << ", time=" << et << endl;

    // Record the data point.
    data.record(n, et);
  }
  // Write all data points to disk.
  cout << "    writing CSV..." << endl;
  filename = operation_name + ".csv";
  assert(data.write_csv(filename));

  // List (doubly-linked list): add to back
  // In theory, each operation should take O(1) time.
  operation_name = "list_add_back";
  cout << operation_name << endl;
  data.clear();
  for (vector<int>::iterator i = n_values.begin(); i != n_values.end(); ++i) {
    int n = *i;

    list<string> the_list(random_strings.begin(), random_strings.begin() + n);
    string element = random_string();

    timer.start();
    the_list.push_back(element);
    timer.stop();

    double et = timer.elapsed_seconds();

    cout << "    n=" << n << ", time=" << et << endl;

    data.record(n, et);
  }
  cout << "    writing CSV..." << endl;
  filename = operation_name + ".csv";
  assert(data.write_csv(filename));

  // Set (self-balancing binary search tree): erase
  // In theory, each operation should take O(log n) time.
  operation_name = "set_erase";
  cout << operation_name << endl;
  data.clear();
  for (vector<int>::iterator i = n_values.begin(); i != n_values.end(); ++i) {
    int n = *i;
    set<string> the_set(random_strings.begin(), random_strings.begin() + n);
    string element = random_string();

    timer.start();
    the_set.erase(element);
    timer.stop();
    double et = timer.elapsed_seconds();

    cout << "    n=" << n << ", time=" << et << endl;

    data.record(n, et);
  }
  cout << "    writing CSV..." << endl;
  filename = operation_name + ".csv";
  assert(data.write_csv(filename));

  // Set (self-balancing binary search tree): insert
  // In theory, each operation should take O(log n) time.
  operation_name = "set_insert";
  cout << operation_name << endl;
  data.clear();
  for (vector<int>::iterator i = n_values.begin(); i != n_values.end(); ++i) {
    int n = *i;
    set<string> the_set(random_strings.begin(), random_strings.begin() + n);
    string element = random_string();

    timer.start();
    the_set.insert(element);
    timer.stop();
    double et = timer.elapsed_seconds();

    cout << "    n=" << n << ", time=" << et << endl;

    data.record(n, et);
  }
  cout << "    writing CSV..." << endl;
  filename = operation_name + ".csv";
  assert(data.write_csv(filename));

  // Forward list (singly linked list): add to front
  // In theory, each operation should take O(1) time.
  operation_name = "forward_list_add_front";
  cout << operation_name << endl;
  data.clear();
  for (vector<int>::iterator i = n_values.begin(); i != n_values.end(); ++i) {
    int n = *i;

    forward_list<string> the_list(random_strings.begin(),
      random_strings.begin() + n);
    string element = random_string();

    timer.start();
    the_list.push_front(element);
    timer.stop();

    double et = timer.elapsed_seconds();

    cout << "    n=" << n << ", time=" << et << endl;

    data.record(n, et);
  }
  cout << "    writing CSV..." << endl;
  filename = operation_name + ".csv";
  assert(data.write_csv(filename));

  // Forward list (singly linked list): compute size
  // In theory each operation should take O(n) time.
  operation_name = "forward_list_size";
  cout << operation_name << endl;
  data.clear();
  for (vector<int>::iterator i = n_values.begin(); i != n_values.end(); ++i) {
    int n = *i;

    forward_list<string> the_list(random_strings.begin(),
      random_strings.begin() + n);

    timer.start();
    distance(the_list.begin(), the_list.end());
    timer.stop();

    double et = timer.elapsed_seconds();
    cout << "    n=" << n << ", time=" << et << endl;

    data.record(n, et);
  }
  cout << "    writing CSV..." << endl;
  filename = operation_name + ".csv";
  assert(data.write_csv(filename));

  // Vector: add to back
  // In theory, each operation should take O(1) amortized time.
  operation_name = "vector_add_back";
  cout << operation_name << endl;
  data.clear();
  for (vector<int>::iterator i = n_values.begin(); i != n_values.end(); ++i) {
    int n = *i;
    vector<string> the_vector(random_strings.begin(), random_strings.begin()
      + n);
    string element = random_string();

    timer.start();
    the_vector.push_back(element);
    timer.stop();
    double et = timer.elapsed_seconds();

    cout << "    n=" << n << ", time=" << et << endl;

    data.record(n, et);
  }
  cout << "    writing CSV..." << endl;
  filename = operation_name + ".csv";
  assert(data.write_csv(filename));

  // Vector: add to front
  // In theory, each operation should take O(n) time.
  operation_name = "vector_add_front";
  cout << operation_name << endl;
  data.clear();
  for (vector<int>::iterator i = n_values.begin(); i != n_values.end(); ++i) {
    int n = *i;
    vector<string> the_vector(random_strings.begin(), random_strings.begin()
      + n);
    string element = random_string();

    timer.start();
    the_vector.insert(the_vector.begin(), element);
    timer.stop();
    double et = timer.elapsed_seconds();

    cout << "    n=" << n << ", time=" << et << endl;

    data.record(n, et);
  }
  cout << "    writing CSV..." << endl;
  filename = operation_name + ".csv";
  assert(data.write_csv(filename));

  return 0;
}
