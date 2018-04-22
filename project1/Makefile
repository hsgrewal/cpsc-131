#
# Makefile
#
# CPSC 131, Fall 2015, Prof. Kevin Wortman, Project 1
#
# Written in 2015 by Kevin Wortman (kwortman@fullerton.edu)
#
# To the extent possible under law, the author(s) have dedicated all
# copyright and related and neighboring rights to this software to the
# public domain worldwide. This software is distributed without any
# warranty. You should have received a copy of the CC0 Public Domain
# Dedication along with this software. If not, see
# <http://creativecommons.org/publicdomain/zero/1.0/>.

all: test simulation

test: airline.hh airline.cc test_main.cc
	g++ airline.cc test_main.cc -o test

simulation: airline.hh airline.cc simulation_main.cc
	g++ airline.cc simulation_main.cc -o simulation

clean:
	rm -f test simulation
