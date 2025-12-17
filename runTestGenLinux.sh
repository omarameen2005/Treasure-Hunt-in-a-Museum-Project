#!/bin/bash

g++ -g -std=c++17 -fdiagnostics-color=always test_generator.cpp MuseumGenerator.cpp Room.cpp Clue.cpp -o test_generator && ./test_generator
