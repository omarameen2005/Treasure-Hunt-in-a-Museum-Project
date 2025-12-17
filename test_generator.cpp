#include "MuseumGenerator.h"
#include "Clue.h"
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

int countRooms(shared_ptr<Room> start) {
    map<int, bool> visited;
    vector<shared_ptr<Room>> stack;
    int count = 0;
    
    stack.push_back(start);
    
    while (!stack.empty()) {
        auto current = stack.back();
        stack.pop_back();
        
        if (!current || visited[current->roomID]) continue;
        visited[current->roomID] = true;
        count++;
        
        if (current->next1) stack.push_back(current->next1);
        if (current->next2) stack.push_back(current->next2);
    }
    
    return count;
}

bool reachesExit(shared_ptr<Room> start) {
    map<int, bool> visited;
    vector<shared_ptr<Room>> stack;
    
    stack.push_back(start);
    
    while (!stack.empty()) {
        auto current = stack.back();
        stack.pop_back();
        
        if (!current || visited[current->roomID]) continue;
        visited[current->roomID] = true;
        
        if (current->type == RoomType::EXIT) return true;
        
        if (current->next1) stack.push_back(current->next1);
        if (current->next2) stack.push_back(current->next2);
    }
    
    return false;
}

int main() {
    std::srand(std::time(nullptr));

    if (!Clue::loadFromFile("clues.txt")) {
        cerr << "ERROR: Failed to load clues.txt!" << endl;
        return 1;
    }
    
    cout << "Clues loaded.\n" << endl;
    
    MuseumGenerator generator;
    cout << "Generating museum...\n" << endl;
    auto entrances = generator.generate(3);
    
    cout << "=== RESULTS ===" << endl;
    cout << "Entrances: " << entrances.size() << "\n" << endl;
    
    for (size_t i = 0; i < entrances.size(); ++i) {
        int rooms = countRooms(entrances[i]);
        bool hasExit = reachesExit(entrances[i]);
        
        cout << "Path " << (i+1) << ": " << rooms << " rooms | Exit: " 
             << (hasExit ? "YES" : "NO") << endl;
        
        entrances[i]->printTree(cout);
    }
    
    cout << "Done." << endl;
    return 0;
}
