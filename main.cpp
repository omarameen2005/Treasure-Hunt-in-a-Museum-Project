#include <iostream>
#include "Clue.h"
#include "Room.h"

using namespace std;

int main() {
    // Load all clues
    if (!Clue::loadFromFile("clues.txt")) {
        cout << "Failed to load clues. Make sure clues.txt exists!\n";
        return 1;
    }

    cout << "Clues loaded successfully!\n\n";

    // Create three test rooms
    Room entranceRoom(0, "Entrance Hall", RoomType::ENTRANCE);
    Room midRoom(1, "Ancient Gallery", RoomType::INTERMEDIATE);
    Room exitRoom(2, "Treasure Vault", RoomType::EXIT);

    // Display each room info using getters
    cout << "=== Testing Rooms ===\n\n";

    cout << "Room ID: " << entranceRoom.roomID << "\n";
    cout << "Name: " << entranceRoom.name << "\n";
    cout << "Type: Entrance\n";
    cout << "Clue: " << entranceRoom.entryClue.getProblem() << "\n\n";

    cout << "Room ID: " << midRoom.roomID << "\n";
    cout << "Name: " << midRoom.name << "\n";
    cout << "Type: Intermediate\n";
    cout << "Random Clue: " << midRoom.entryClue.getProblem() << "\n\n";

    cout << "Room ID: " << exitRoom.roomID << "\n";
    cout << "Name: " << exitRoom.name << "\n";
    cout << "Type: Exit\n";
    cout << "Exit Clue: " << exitRoom.entryClue.getProblem() << "\n\n";

    // Test solving a clue manually (use getters)
    cout << "=== Testing Clue Solving ===\n";
    cout << "Clue: " << midRoom.entryClue.getProblem() << "\n";

    string ans;
    cout << "Your answer: ";
    cin >> ans;

    if (midRoom.entryClue.checkAnswer(ans)) {
        cout << "Correct! Clue solved.\n";
    } else {
        cout << "Wrong. Correct answer was: " << midRoom.entryClue.getSolution() << "\n";
    }

    return 0;
}

