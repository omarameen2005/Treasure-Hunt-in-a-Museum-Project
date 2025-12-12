// #ifndef ROOM_H
// #define ROOM_H

// #include <string>
// #include <memory>
// #include <vector>
// #include <iostream>
// #include <iomanip>
// #include "Clue.h"

// enum class RoomType { ENTRANCE, INTERMEDIATE, EXIT };
// enum class Difficulty { EASY, HARD };

// class Room {
// private:
//     static void printTreeHelper(const Room* r, int depth, std::ostream& os);

// public:
//     int roomID;
//     std::string name;
//     RoomType type;
//     Difficulty difficulty = Difficulty::HARD;

//     Clue entryClue;

//     std::shared_ptr<Room> next1;
//     std::shared_ptr<Room> next2 = nullptr;

//     bool visited = false;
//     bool cleared = false;

//     Room(int id, std::string name, RoomType t);

//     // Disable copying for safety
//     Room(const Room&) = delete;
//     Room& operator=(const Room&) = delete;

//     // Allow moving
//     Room(Room&&) = default;
//     Room& operator=(Room&&) = default;

//     ~Room() = default;

//     void connectNext1(std::shared_ptr<Room> room);
//     void connectNext2(std::shared_ptr<Room> room);

//     [[nodiscard]] bool hasTwoDoors() const noexcept { return next2 != nullptr; }
//     [[nodiscard]] bool isEasy() const noexcept { return difficulty == Difficulty::EASY; }

//     [[nodiscard]] std::vector<Room*> getExits() const {
//         std::vector<Room*> exits;
//         if (next1) exits.push_back(next1.get());
//         if (next2) exits.push_back(next2.get());
//         return exits;
//     }

//     void printInfo() const;
//     void printTree(std::ostream& os = std::cout) const;
// };

// #endif


#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Clue.h"

enum class RoomType { ENTRANCE, INTERMEDIATE, EXIT };
enum class Difficulty { EASY, HARD };

class Room {
private:
    static void printTreeHelper(const Room* r, int depth, std::ostream& os);

public:
    int roomID;
    std::string name;
    RoomType type;
    Difficulty difficulty = Difficulty::HARD;

    Clue entryClue;

    std::shared_ptr<Room> next1;
    std::shared_ptr<Room> next2 = nullptr;

    bool visited = false;
    bool cleared = false;

    Room(int id, std::string name, RoomType t);

    // Disable copying for safety
    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;

    // Allow moving
    Room(Room&&) = default;
    Room& operator=(Room&&) = default;

    ~Room() = default;

    void connectNext1(std::shared_ptr<Room> room);
    void connectNext2(std::shared_ptr<Room> room);

    [[nodiscard]] bool hasTwoDoors() const noexcept { return next2 != nullptr; }
    [[nodiscard]] bool isEasy() const noexcept { return difficulty == Difficulty::EASY; }

    [[nodiscard]] std::vector<Room*> getExits() const {
        std::vector<Room*> exits;
        if (next1) exits.push_back(next1.get());
        if (next2) exits.push_back(next2.get());
        return exits;
    }

    void printInfo() const;
    void printTree(std::ostream& os = std::cout) const;
};

#endif
