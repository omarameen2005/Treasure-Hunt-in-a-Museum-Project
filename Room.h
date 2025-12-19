#ifndef ROOM_H
#define ROOM_H


#include <string>
#include <memory>
#include <iostream>
#include "Clue.h"


enum class RoomType { ENTRANCE, INTERMEDIATE, EXIT };
enum class Difficulty { EASY, HARD };


class Room {
public:
    int roomID;
    std::string name;
    RoomType type;
    Difficulty difficulty;

    Clue entryClue;


    std::shared_ptr<Room> next1;
    std::shared_ptr<Room> next2;


    Room(int id, std::string name, RoomType type);

    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;


    void connectNext1(std::shared_ptr<Room> room);
    void connectNext2(std::shared_ptr<Room> room);


    bool hasTwoDoors() const;
    void printTree(int depth = 0) const;
};


#endif