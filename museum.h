#ifndef MUSEUM_H
#define MUSEUM_H

#include "Room.h"
#include "MuseumGenerator.h"
#include <vector>
#include <memory>
#include <stack>

class Museum {
private:
    std::vector<std::shared_ptr<Room>> entrances;

    Room* currentRoom = nullptr;
    int score = 0;
    std::stack<Room*> history;

    void displayRoom() const;
    bool solveCurrentClue();

public:
    Museum();

    void generate();
    void startGame();
    void chooseEntrance(int choice);
    bool navigate(int doorChoice);

    void showMap() const;
    bool isGameWon() const;
    int getScore() const { return score; }
    Room* getCurrentRoom() const { return currentRoom; }
};

#endif