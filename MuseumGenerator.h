#ifndef MUSEUMGENERATOR_H
#define MUSEUMGENERATOR_H

#include "Room.h"
#include <vector>
#include <memory>
#include <string>

class MuseumGenerator {
public:
    std::shared_ptr<Room> createRoom(int id, std::string name, RoomType type);

    std::shared_ptr<Room> buildRandomPath(int& startId, int length, std::shared_ptr<Room> exitRoom, int depth = 0);

    std::shared_ptr<Room> createEntranceRoom(int id);

    std::shared_ptr<Room> createExitRoom(int id);

    std::vector<std::shared_ptr<Room>> generate(int numOfIntermediateRooms);
};

#endif
