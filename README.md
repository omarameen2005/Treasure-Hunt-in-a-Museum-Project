# Treasure Hunt in the Museum
A text-based adventure game where players explore a procedurally generated museum, solving puzzles and riddles to reach the ultimate treasure room.

Table of Contents:-
Overview
Features
Game Mechanics
Project Structure
Requirements
Installation & Setup
How to Run
How to Play
File Descriptions

Overview:-
Treasure Hunt in the Museum is a console-based adventure game built with C++ that demonstrates the practical application of data structures, particularly linked lists. Players navigate through a dynamically generated museum, choosing paths, solving puzzles, and accumulating points to reach the final treasure.
Every playthrough generates a unique museum layout with randomized room connections and puzzle assignments, ensuring high replay value.

Features:-

Procedurally Generated Museum - Unique layout every game
Dynamic Puzzle System - Clues loaded from external database
Strategic Choices - EASY rooms offer 2 paths, HARD rooms have 1 path
Scoring System - Earn points for correct answers, penalty for hints
Hint System - Get help when stuck (costs 2 points)
Multiple Entrances - Choose from 4 different starting points
Map Preview - See museum structure before playing
Input Validation - Robust error handling for user inputs
Extensible Clue Database - Easy to add new puzzles


Game Mechanics:-
Room Types

ENTRANCE (4 rooms): Starting points with simple introductory clues
INTERMEDIATE (Variable): Main museum halls with challenging puzzles
EXIT (1 room): Final treasure room with ultimate challenge

Difficulty Levels

EASY Rooms 🟢: Two doors to choose from, offering strategic branching
HARD Rooms 🔴: Single path forward, more linear progression

Scoring

Correct Answer (No Hint): +10 points
Correct Answer (Hint Used): +8 points (-2 point penalty)
Wrong Answers: No point deduction, but 3 attempts maximum
Game Over: Failed to solve clue after 3 attempts


Project Structure:-
treasure-hunt-museum/
├── main.cpp              # Entry point, game initialization
├── Museum.h              # Museum class declaration
├── Museum.cpp            # Museum class implementation (game logic)
├── Room.h                # Room class declaration
├── Room.cpp              # Room class implementation
├── Clue.h                # Clue class declaration
├── Clue.cpp              # Clue class implementation
├── MuseumGenerator.h     # Generator class declaration
├── MuseumGenerator.cpp   # Procedural generation logic
├── clues.txt             # Puzzle database (REQUIRED)
└── README.md             # This file

Requirements:-
Software Requirements

C++ Compiler with C++17 support:

GCC 7.0+ (Linux/macOS)
MinGW-w64 (Windows)
Clang 5.0+
MSVC 2017+ (Visual Studio)



System Requirements

OS: Windows 10/11, Linux, macOS
RAM: 50 MB minimum
Storage: 5 MB

Dependencies

Standard C++ Library (included with compiler)
No external libraries required ✅


Installation & Setup:-
Step 1: Clone or Download
Download all project files to a single directory:
treasure-hunt-museum/
├── All .cpp files
├── All .h files
└── clues.txt
Step 2: Verify clues.txt
Ensure the clues.txt file is in the same directory as your source files. The game cannot run without this file.
Sample clues.txt format:
1
What has keys but no locks, space but no room?
Keyboard
Think about what you use for typing
Riddle
3
---
2
I speak without a mouth and hear without ears. What am I?
Echo
Sound comes back to you
Riddle
3
---
Step 3: Open Terminal/Command Prompt
Navigate to your project directory:
Windows:
cmdcd C:\path\to\treasure-hunt-museum
Linux/macOS:
bashcd /path/to/treasure-hunt-museum

How to Run:-
Quick Start (Recommended)
Windows:
cmdg++ *.cpp -o game.exe
.\game.exe
Linux/macOS:
bashg++ *.cpp -o game
./game
Why This Command Works
g++ *.cpp -o game.exe
Let's break down this compilation command:

g++: The GNU C++ compiler

Compiles C++ source code into executable programs
Part of GCC (GNU Compiler Collection)


*.cpp: Wildcard that matches all .cpp files

Automatically includes all C++ source files in the directory:

main.cpp
Museum.cpp
Room.cpp
Clue.cpp
MuseumGenerator.cpp


Why this matters: You don't need to list each file individually
Alternative: You could write g++ main.cpp Museum.cpp Room.cpp Clue.cpp MuseumGenerator.cpp -o game.exe


-o game.exe: Output filename specification

-o flag means "output file name"
game.exe is the name of the compiled executable
On Windows: Use .exe extension
On Linux/macOS: Extension is optional (use game)



What happens during compilation:
[Source Files] → [Compiler] → [Object Files] → [Linker] → [Executable]
   *.cpp      →    g++      →    *.o       →   Link    →   game.exe
The compiler:

Reads all .cpp files
Checks for syntax errors
Compiles each file to object code
Links all object files together
Creates a single executable: game.exe

.\game.exe (Windows) or ./game (Linux/macOS)
This command runs the compiled executable:

. = Current directory
\ (Windows) or / (Linux/macOS) = Directory separator
game.exe = Your executable file

Why you need .\ or ./:

Tells the system to look in the current directory
Without it, the system only searches PATH directories
Security feature to prevent accidental execution


How to Play:-
Step 1: Start the Game
Run the executable. You'll see:
===== INITIALIZING MUSEUM DATA =====
Successfully loaded 15 clues from clues.txt

===== MUSEUM MAP LAYOUT =====
[1] Entrance: 1 (HARD)
 [5] Hall Room 5 (EASY)
  ...
Step 2: Choose an Entrance
Select one of the 4 entrance rooms (1-4):
Choose an entrance (1 to 4):
1. Entrance: 1
2. Entrance: 2
3. Entrance: 3
4. Entrance: 4
Your choice: 1
Step 3: Solve Puzzles
Each room presents a clue:
--- ROOM ---
Name: Hall Room 5
Clue: What has keys but no locks?

Attempt 1 of 3
Your answer: keyboard

Correct! The door unlocks.
Points earned: 10 | Total Score: 10
Step 4: Navigate

EASY Rooms: Choose between 2 doors (1 or 2)
HARD Rooms: Automatic progression through single door

Step 5: Reach the Treasure
Solve the final puzzle in the treasure room to win!
========================================
 CONGRATULATIONS! YOU FOUND THE TREASURE! 
Final Score: 60
========================================

File Descriptions:-
Core Files
main.cpp

Purpose: Program entry point
Responsibilities:

Initialize random seed
Load clue database from clues.txt
Create Museum object
Start game loop
Cleanup resources



Museum.h / Museum.cpp

Purpose: Main game controller
Key Functions:

generate(): Create museum layout
startGame(): Main game loop
solveCurrentClue(): Handle puzzle attempts
navigate(): Move between rooms
showMap(): Display museum structure



Room.h / Room.cpp

Purpose: Linked list node representing museum rooms
Key Members:

next1, next2: Pointers to connected rooms
entryClue: Puzzle for this room
cleared: Tracks if puzzle is solved


Key Functions:

connectNext1(), connectNext2(): Link rooms
hasTwoDoors(): Check if EASY room
printTree(): Display room structure



Clue.h / Clue.cpp

Purpose: Puzzle management system
Key Functions:

loadFromFile(): Load puzzles from clues.txt
getRandomClue(): Select random puzzle
checkAnswer(): Validate user input
normalizeAnswer(): Case-insensitive comparison



MuseumGenerator.h / MuseumGenerator.cpp

Purpose: Procedural museum creation
Key Functions:

generate(): Create complete museum with 4 entrances
buildRandomPath(): Generate room chains with branching
createRoom(): Factory method for room creation



Data Files
clues.txt

Purpose: External puzzle database
Format: Plain text with structured data
Required: Must exist in same directory as executable
Customizable: Add/edit puzzles easily