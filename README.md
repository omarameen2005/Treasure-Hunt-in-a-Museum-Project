# Treasure-Hunt-in-a-Museum-Project

# Project layout

project/
├── main.cpp               # Entry point
├── Room.h/.cpp            # Room node class
├── Clue.h/.cpp            # Clue system
├── Museum.h/.cpp          # Game manager
├── MuseumGenerator.h/.cpp # Random museum generator
├── Utils.h/.cpp           # Helper functions
└── clues.txt              # Puzzle database







Youssef 3lak el Room.h/.cpp

Room.h/.cpp — Room Developer

Role: Build the core room structure, manage room connections, and implement visualization/debug methods.

Functions to implement & explanations:

Function	Purpose / Explanation
connectNext1(std::unique_ptr<Room> next)	Connect this room to another room via the first door (left). Handles movement in the game map.
connectNext2(std::unique_ptr<Room> next)	Connect this room to another room via the second door (right). Used only for rooms with two doors.
getExits()	Returns the number of doors/exits this room has. Useful to check navigation options.
printInfo()	Prints room details: name, type, if visited/cleared, and current clue. Useful for player display.
printTreeHelper(int depth)	Recursively prints the room and all rooms reachable from it with indentation for depth. Used internally by printTree().
printTree()	Calls printTreeHelper(0) to print the full room tree for debugging or “mini-map” visualization.

Notes for Room Developer:

This module is the foundation; everything else depends on it.

Make sure ownership of unique_ptrs is handled correctly to avoid crashes.

Implement hasTwoDoors() helper if needed to check if next2 exists.



Nayra 3laky el Clue.h/.cpp

Clue.h/.cpp — Clue Developer

Role: Implement the puzzle system, including clue storage, random selection, and answer validation.

Functions to implement & explanations:

Function	Purpose / Explanation
loadFromFile(const std::string& filename)	Load clues from a file (e.g., clues.txt) into a database for random selection.
getRandomClue(const std::string& category = "")	Returns a random clue. Can filter by category if specified.
getClue(int id)	Returns a specific clue by its index/ID. Useful for testing or debugging.
normalizeAnswer(std::string answer)	Converts a user answer to a standard format: lowercase, remove extra spaces/punctuation. Ensures correct comparison.

Notes for Clue Developer:

Ensure clue structure supports problem, solution, hint, category, maxAttempts.

Use normalizeAnswer whenever comparing user input with the solution.

Clues must integrate with rooms (entryClue).




Habiba el Museum.h/.cpp

Museum.h/.cpp — Game Developer

Role: Manage gameplay, user interaction, score, navigation, and winning conditions.

Functions to implement & explanations:

Function	Purpose / Explanation
generateNewMuseum()	Calls MuseumGenerator to create a new random museum. Resets score, player position, and history stack.
startGame()	Main game loop. Displays entrances, lets player choose starting room, and starts navigation.
printAllEntrances()	Prints the names of all entrance rooms.
chooseEntrance(int choice)	Sets the player’s starting room based on entrance choice and marks it as visited.
displayRoom()	Shows current room info and options. Calls solveCurrentClue() if needed.
solveCurrentClue()	Manages clue solving in the current room, tracks attempts, provides hints, updates score.
giveHint()	Prints a hint for the current clue (if available). Reduces score when used.
navigate(int doorChoice)	Moves player to the chosen door (1 or 2) and updates current room and history stack.
isGameWon()	Checks if the current room is an exit and cleared.
showMap()	Calls printTree() on each entrance to show the full museum layout.

Notes for Museum Developer:

Use currentRoom->next1 and next2 for navigation.

Ensure score updates and visited/cleared flags are handled correctly.

Integrate clues from ClueManager and rooms.



Omar el MuseumGenerator.h/.cpp

MuseumGenerator.h/.cpp — Map / Level Designer

Role: Create random museum layouts, assign clues to rooms, and handle entrances/exits.

Functions to implement & explanations:

Function	Purpose / Explanation
createRoom(int id, const std::string& name, RoomType type)	Creates a new room with a given ID, name, and type. Assigns a clue to it.
assignRandomClue(Room* room, const std::string& category = "")	Assigns a random clue to the room. Entrances and exits get special predefined clues.
buildRandomPath(int startId, int length, RoomType type)	Generates a sequence of connected rooms, optionally with branches (2 doors). Returns head and tail for linking.
createExitRoom(int id)	Creates the final exit room with a special treasure clue.
generate() / generate(unsigned int seed)	Main function. Creates 4 entrance paths, generates random paths, connects tails to exit, returns entrances + exit.

Notes for MuseumGenerator Developer:

Return unique_ptr for ownership transfer.

Ensure paths do not overlap IDs.

Make use of Room functions to connect rooms.




taha el Utils.h/.cpp

Utils.h/.cpp — Utility Developer

Role: Provide helper functions for string handling, randomization, input validation, and debugging.

Suggested Functions & Explanations:

Function	Purpose / Explanation
string toLower(const string& s)	Converts string to lowercase. Used for answer normalization.
string trim(const string& s)	Removes leading/trailing spaces from a string.
string normalizeAnswer(const string& s)	Combines toLower and trim for user answer validation.
int randomInt(int min, int max)	Returns a random integer in [min, max]. Used in MuseumGenerator.
bool confirm(const string& prompt)	Prints prompt and returns true/false for yes/no input.
void pause()	Pauses console output until user presses enter. Useful for readability during gameplay.

Notes for Utility Developer:

Keep functions modular and independent.

Avoid direct dependencies on Room or Museum; other modules call them.

Helps standardize repetitive tasks across the project.


