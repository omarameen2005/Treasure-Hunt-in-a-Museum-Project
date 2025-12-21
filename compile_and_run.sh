#!/bin/bash

# Compile the project
echo "Compiling the project..."
g++ -std=c++17 -o treasure_hunt main.cpp Clue.cpp museum.cpp MuseumGenerator.cpp Room.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the project..."
    ./treasure_hunt
else
    echo "Compilation failed."
fi