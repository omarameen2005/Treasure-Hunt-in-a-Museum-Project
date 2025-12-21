#include <iostream>
#include <memory>
#include <ctime>   
#include <cstdlib> 

#include "Clue.h"
#include "Room.h"
#include "MuseumGenerator.h"
#include "Museum.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "===== INITIALIZING MUSEUM DATA =====\n";
    if (!Clue::loadFromFile("clues.txt")) {
        cout << "ERROR: 'clues.txt' not found! Please create the file.\n";
        return 1;
    }

    Museum museum;
    museum.generate();

    cout << "\n===== MUSEUM MAP LAYOUT =====\n";
    museum.showMap();
    cout << "==============================\n";

    cout << "\nPress Enter to begin your adventure...";
    cin.get();
    
    museum.startGame();

    Clue::clearDatabase();

    cout << "\nThank you for playing!\n";
    return 0;
}

