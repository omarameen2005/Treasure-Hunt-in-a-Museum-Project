#include "Room.h"
#include <cstdlib> 
#include <memory>
#include <string> 
#include "MuseumGenerator.h"

using namespace std;

shared_ptr<Room> MuseumGenerator::createRoom(int id, string name, RoomType type) 
{
    auto newRoom = make_shared<Room>(id, name, type);
    newRoom->entryClue = Clue::getRandomClue();

    return newRoom;
}

shared_ptr<Room> MuseumGenerator::buildRandomPath(int& startId, int intermediateRoomsAmount, shared_ptr<Room> exitRoom, int depth) 
{
    shared_ptr<Room> head = nullptr;
    shared_ptr<Room> current = nullptr;
    int currentId = startId;

    for (int i = 0; i < intermediateRoomsAmount; i++) 
    {
        string name = "Hall Room " + to_string(currentId);
        auto newRoom = createRoom(currentId++, name, RoomType::INTERMEDIATE);
        newRoom->difficulty = Difficulty::HARD;

        if (!head) 
        {
            head = newRoom;
            current = newRoom;

        } else 
        {
            current->connectNext1(newRoom);
            current = newRoom;
        }

        if (rand() % 100 < 50 && depth < 3) 
        {
            current->difficulty = Difficulty::EASY;
            int branchLength = intermediateRoomsAmount - i;
            current->connectNext2(buildRandomPath(currentId, branchLength, exitRoom, depth + 1));
        }
    }

    current->connectNext1(exitRoom);
    return head;
}

shared_ptr<Room> MuseumGenerator::createEntranceRoom(int id) 
{
    return createRoom(id, "Entrance: " + to_string(id), RoomType::ENTRANCE);
}

shared_ptr<Room> MuseumGenerator::createExitRoom(int id) 
{
    return createRoom(id, "Treasure Room", RoomType::EXIT);
}

std::vector<std::shared_ptr<Room>> MuseumGenerator::generate(int numOfIntermediateRooms) 
{
    std::vector<std::shared_ptr<Room>> entrances;
    int id = 1;

    auto exitRoom = createExitRoom(999);

    for (int i = 0; i < 4; i++) 
    {
        auto entrance = createEntranceRoom(id++);
        auto pathHead = buildRandomPath(id, numOfIntermediateRooms, exitRoom);
        entrance->connectNext1(pathHead);
        entrances.push_back(entrance);
    }

    return entrances;
}
