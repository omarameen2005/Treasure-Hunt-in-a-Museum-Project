#include "Room.h"
using namespace std;


Room::Room(int id, string n, RoomType t)
: roomID(id), name(move(n)), type(t), difficulty(Difficulty::HARD),
    next1(nullptr), next2(nullptr){

    entryClue = Clue::getRandomClue();
}


void Room::connectNext1(shared_ptr<Room> room) {
    next1 = room;
}


void Room::connectNext2(shared_ptr<Room> room) {
    if (type != RoomType::INTERMEDIATE) return;
    if (next2) return;


    difficulty = Difficulty::EASY;
    next2 = room;
}


bool Room::hasTwoDoors() const {
    return next2 != nullptr;
}


void Room::printTree(int depth) const {
    for (int i = 0; i < depth; ++i)
    cout << " ";


    cout << "[" << roomID << "] " << name;
    cout << (hasTwoDoors() ? " (EASY)" : " (HARD)") << '\n';


    if (next1) next1->printTree(depth + 1);
    if (next2) next2->printTree(depth + 1);
}

