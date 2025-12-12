// #include "Room.h"
// #include <iomanip>
// #include <string>
// #include <iostream>
// #include <vector>
// #include "Clue.h"

// using namespace std;

// Room::Room(int id, string n, RoomType t)
//     : roomID(id), name(move(n)), type(t)
// {
//     if (type == RoomType::ENTRANCE) {
//         cleared = true;
//         visited = true;

//         // Simple intro clue (using the first Clue version constructor)
//         entryClue = Clue(
//             0,
//             "Welcome to the museum.",
//             "", 
//             "Just begin your journey.",
//             "Intro",
//             1
//         );
//     }
//     else if (type == RoomType::EXIT) {
//         entryClue = Clue(
//             999,
//             "Final challenge! What is the treasure?",
//             "treasure",
//             "Think about why you are here.",
//             "Final",
//             3
//         );
//     }
//     else {
//         // IMPORTANT: We are using Clue version 1 (static DB)
//         entryClue = Clue::getRandomClue();
//     }
// }

// void Room::connectNext1(std::shared_ptr<Room> room) {
//     next1 = room;
// }

// void Room::connectNext2(std::shared_ptr<Room> room) {
//     if (type != RoomType::INTERMEDIATE) {
//         cerr << "[WARNING] Only INTERMEDIATE rooms can have two doors!\n";
//         return;
//     }
//     if (next2) {
//         cerr << "[WARNING] Room already has next2!\n";
//         return;
//     }

//     difficulty = Difficulty::EASY;
//     next2 = room;
// }

// void Room::printInfo() const {
//     cout << "=== Room " << roomID << " ===\n";
//     cout << "Name: " << name << "\n";
//     cout << "Type: ";

//     switch (type) {
//         case RoomType::ENTRANCE:     cout << "ENTRANCE"; break;
//         case RoomType::INTERMEDIATE: cout << "INTERMEDIATE"; break;
//         case RoomType::EXIT:         cout << "EXIT"; break;
//     }

//     cout << " | Difficulty: " << (isEasy() ? "EASY (2 doors)" : "HARD (1 door)") << "\n";

//     cout << "Visited: " << (visited ? "Yes" : "No")
//          << " | Cleared: " << (cleared ? "Yes" : "No") << "\n";

//     cout << "Clue: " << entryClue.getProblem() << "\n";
//     cout << "Hint: " << entryClue.getHint() << "\n";
// }

// void Room::printTreeHelper(const Room* r, int depth, ostream& os) {
//     if (!r) return;

//     string indent(depth * 3, ' ');
//     string diff = r->isEasy() ? "EASY" : "HARD";

//     os << indent << "┌─ [ID:" << setw(2) << r->roomID << "] "
//        << r->name << " (" << diff << ")\n";

//     if (r->next1) {
//         os << indent << "├─→ Door 1\n";
//         printTreeHelper(r->next1.get(), depth + 1, os);
//     }
//     if (r->next2) {
//         os << indent << "└─→ Door 2\n";
//         printTreeHelper(r->next2.get(), depth + 1, os);
//     }
// }

// void Room::printTree(ostream& os) const {
//     os << "\n=== MUSEUM LAYOUT ===\n";
//     printTreeHelper(this, 0, os);
//     os << "=====================\n\n";
// }



#include "Room.h"
#include <iomanip>
#include <string>
#include <iostream>
#include <vector>
#include "Clue.h"

using namespace std;

Room::Room(int id, string n, RoomType t)
    : roomID(id), name(move(n)), type(t)
{
    if (type == RoomType::ENTRANCE) {
        cleared = true;
        visited = true;

        // Use first Clue version constructor (id, problem, solution, hint, category, maxAttempts)
        entryClue = Clue(
            0,
            "Welcome to the museum.",
            "", 
            "Just begin your journey.",
            "Intro",
            1
        );
    }
    else if (type == RoomType::EXIT) {
        entryClue = Clue(
            999,
            "Final challenge! What is the treasure?",
            "treasure",
            "Think about why you are here.",
            "Final",
            3
        );
    }
    else {
        // IMPORTANT: We are using Clue version 1 (static DB)
        entryClue = Clue::getRandomClue();
    }
}

void Room::connectNext1(std::shared_ptr<Room> room) {
    next1 = room;
}

void Room::connectNext2(std::shared_ptr<Room> room) {
    if (type != RoomType::INTERMEDIATE) {
        cerr << "[WARNING] Only INTERMEDIATE rooms can have two doors!\n";
        return;
    }
    if (next2) {
        cerr << "[WARNING] Room already has next2!\n";
        return;
    }

    difficulty = Difficulty::EASY;
    next2 = room;
}

void Room::printInfo() const {
    cout << "=== Room " << roomID << " ===\n";
    cout << "Name: " << name << "\n";
    cout << "Type: ";

    switch (type) {
        case RoomType::ENTRANCE:     cout << "ENTRANCE"; break;
        case RoomType::INTERMEDIATE: cout << "INTERMEDIATE"; break;
        case RoomType::EXIT:         cout << "EXIT"; break;
    }

    cout << " | Difficulty: " << (isEasy() ? "EASY (2 doors)" : "HARD (1 door)") << "\n";

    cout << "Visited: " << (visited ? "Yes" : "No")
         << " | Cleared: " << (cleared ? "Yes" : "No") << "\n";

    // Use getters (these are public methods in Clue)
    cout << "Clue: " << entryClue.getProblem() << "\n";
    cout << "Hint: " << entryClue.getHint() << "\n";
}

void Room::printTreeHelper(const Room* r, int depth, ostream& os) {
    if (!r) return;

    string indent(depth * 3, ' ');
    string diff = r->isEasy() ? "EASY" : "HARD";

    os << indent << "┌─ [ID:" << setw(2) << r->roomID << "] "
       << r->name << " (" << diff << ")\n";

    if (r->next1) {
        os << indent << "├─→ Door 1\n";
        printTreeHelper(r->next1.get(), depth + 1, os);
    }
    if (r->next2) {
        os << indent << "└─→ Door 2\n";
        printTreeHelper(r->next2.get(), depth + 1, os);
    }
}

void Room::printTree(ostream& os) const {
    os << "\n=== MUSEUM LAYOUT ===\n";
    printTreeHelper(this, 0, os);
    os << "=====================\n\n";
}
