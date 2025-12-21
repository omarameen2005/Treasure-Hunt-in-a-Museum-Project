#include "museum.h"
#include <iostream>

using namespace std;

Museum::Museum() {
    generate();
}

void Museum::generate() {
    MuseumGenerator generator;
    entrances = generator.generate(3);
    currentRoom = nullptr;
    score = 0;
}

void Museum::startGame() {

    if(entrances.empty()) generate();

    cout << "====================================\n";
    cout << "   TREASURE HUNT IN THE MUSEUM     \n";
    cout << "====================================\n\n";
    cout << "You are standing outside the Grand Museum.\n";
    
    int choice = -1;
    while (true) {
        cout << "Choose an entrance (1 to " << entrances.size() << "):\n";
        for (size_t i = 0; i < entrances.size(); ++i) {
            cout << i + 1 << ". " << entrances[i]->name << '\n';
        }
        
        cout << "Your choice: ";
        if (!(cin >> choice)) { 
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << "Invalid input! Please enter a number.\n\n";
            continue;
        }

        if (choice >= 1 && choice <= (int)entrances.size()) {
            break;
        } else {
            cout << "Error: " << choice << " is not a valid entrance. Try again.\n\n";
        }
    }

    chooseEntrance(choice);

    while (!isGameWon()) {
        displayRoom();

        if (!solveCurrentClue()) {
            cout << "\nGAME OVER\n";
            return;
        }

        if (currentRoom->type == RoomType::EXIT) {
            break;
        }

        int doorChoice = 1;
        if (currentRoom->hasTwoDoors()) {
            while (true) {
                cout << "This is an EASY room. You see two doors! Choose (1 or 2): ";
                if (cin >> doorChoice && (doorChoice == 1 || doorChoice == 2)) {
                    break;
                }
                cout << "Invalid choice. ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        } else {
            cout << "This is a HARD room. There is only one path forward (Press 1 to proceed): ";
            cin >> doorChoice; 
        }

        navigate(doorChoice);
    }

    cout << "\n========================================\n";
    cout << " CONGRATULATIONS! YOU FOUND THE TREASURE! \n";
    cout << "Final Score: " << score << "\n";
    cout << "========================================\n";
}

void Museum::chooseEntrance(int choice) {
    if (choice < 1 || choice > (int)entrances.size()) {
        cout << "Invalid choice.\n";
        exit(1);
    }
    currentRoom = entrances[choice - 1].get();
}

bool Museum::navigate(int doorChoice) {
    history.push(currentRoom);

    if (doorChoice == 1 && currentRoom->next1) {
        currentRoom = currentRoom->next1.get();
        return true;
    }
    if (doorChoice == 2 && currentRoom->next2) {
        currentRoom = currentRoom->next2.get();
        return true;
    }

    cout << "Invalid door.\n";
    return false;
}

void Museum::displayRoom() const {
    cout << "\n--- ROOM ---\n";
    cout << "Name: " << currentRoom->name << '\n';
    cout << "Clue: " << currentRoom->entryClue.getProblem() << '\n';
}



bool Museum::solveCurrentClue() {
    if (currentRoom->cleared) return true;

    int attempts = 0;
    int maxAttempts = currentRoom->entryClue.getMaxAttempts(); 
    string answer;
    bool hintUsed = false;

    while (attempts < maxAttempts) {
        cout << "\nAttempt " << (attempts + 1) << " of " << maxAttempts;
        if (hintUsed) cout << " (Hint used: -2 points if correct)";
        cout << "\nYour answer: ";
        
        getline(cin >> ws, answer); 

        if (currentRoom->entryClue.checkAnswer(answer)) {
            cout << "Correct! The door unlocks.\n";
            currentRoom->cleared = true;
            
            int points = 10;
            if (hintUsed) points = 8; 
            score += points;
            
            cout << "Points earned: " << points << " | Total Score: " << score << endl;
            return true;
        } else {
            attempts++;
            if (attempts < maxAttempts) {
                cout << "Wrong answer!";
                currentRoom->entryClue.displayHint();
                hintUsed = true; 
            }
        }
    }

    cout << "\nNo more attempts left! The guards escort you out.\n";
    cout << "The correct answer was: " << currentRoom->entryClue.getSolution() << endl;
    return false;
}



bool Museum::isGameWon() const {
    return currentRoom && currentRoom->type == RoomType::EXIT && currentRoom->cleared;
}

void Museum::showMap() const {
    for (const auto& e : entrances) {
        e->printTree();
    }
}
