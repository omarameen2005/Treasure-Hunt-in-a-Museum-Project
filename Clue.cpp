#include "Clue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cctype>


Clue* Clue::clueDatabase = nullptr;
int Clue::databaseSize = 0;
int Clue::databaseCapacity = 0;

Clue::Clue() : id(0), problem(""), solution(""), hint(""), category(""), maxAttempts(3) {}

Clue::Clue(int id, const std::string& problem, const std::string& solution, 
           const std::string& hint, const std::string& category, int maxAttempts)
    : id(id), problem(problem), solution(solution), hint(hint), 
      category(category), maxAttempts(maxAttempts) {}

int Clue::getID() const { return id; }
std::string Clue::getProblem() const { return problem; }
std::string Clue::getSolution() const { return solution; }
std::string Clue::getHint() const { return hint; }
std::string Clue::getCategory() const { return category; }
int Clue::getMaxAttempts() const { return maxAttempts; }

void Clue::setID(int id) { this->id = id; }
void Clue::setProblem(const std::string& problem) { this->problem = problem; }
void Clue::setSolution(const std::string& solution) { this->solution = solution; }
void Clue::setHint(const std::string& hint) { this->hint = hint; }
void Clue::setCategory(const std::string& category) { this->category = category; }
void Clue::setMaxAttempts(int attempts) { this->maxAttempts = attempts; }

bool Clue::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    if (clueDatabase != nullptr) {
        delete[] clueDatabase;
        clueDatabase = nullptr;
    }
    databaseSize = 0;
    databaseCapacity = 10; 
    clueDatabase = new Clue[databaseCapacity];

    std::string line;
    int clueCount = 0;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        try {
            int clueID = std::stoi(line);
            
            std::string problem;
            if (!std::getline(file, problem)) break;
            
            std::string solution;
            if (!std::getline(file, solution)) break;
            
            std::string hint;
            if (!std::getline(file, hint)) break;
            
            std::string category;
            if (!std::getline(file, category)) break;
            
            std::string attemptsStr;
            if (!std::getline(file, attemptsStr)) break;
            int maxAttempts = std::stoi(attemptsStr);
            
            if (databaseSize >= databaseCapacity) {
                databaseCapacity *= 2;
                Clue* newDatabase = new Clue[databaseCapacity];
                for (int i = 0; i < databaseSize; i++) {
                    newDatabase[i] = clueDatabase[i];
                }
                delete[] clueDatabase;
                clueDatabase = newDatabase;
            }
            
            clueDatabase[databaseSize] = Clue(clueID, problem, solution, hint, category, maxAttempts);
            databaseSize++;
            clueCount++;
            
            std::getline(file, line);
            
        } catch (const std::exception& e) {
            std::cerr << "Error parsing clue: " << e.what() << std::endl;
            continue;
        }
    }

    file.close();
    
    if (clueCount > 0) {
        std::cout << "Successfully loaded " << clueCount << " clues from " << filename << std::endl;
        return true;
    } else {
        std::cerr << "Warning: No clues loaded from " << filename << std::endl;
        return false;
    }
}

Clue Clue::getRandomClue(const std::string& category) {
    if (clueDatabase == nullptr || databaseSize == 0) {
        std::cerr << "Error: Clue database is empty!" << std::endl;
        return Clue(); 
    }

    int matchCount = 0;
    int* matchIndices = new int[databaseSize];

    if (!category.empty()) {
        for (int i = 0; i < databaseSize; i++) {
            if (clueDatabase[i].getCategory() == category) {
                matchIndices[matchCount++] = i;
            }
        }
        
        if (matchCount == 0) {
            std::cerr << "Warning: No clues found for category '" << category 
                      << "'. Returning random clue from all categories." << std::endl;

            for (int i = 0; i < databaseSize; i++) {
                matchIndices[matchCount++] = i;
            }
        }
    } else {
        for (int i = 0; i < databaseSize; i++) {
            matchIndices[matchCount++] = i;
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, matchCount - 1);
    
    int randomIndex = distribution(generator);
    Clue result = clueDatabase[matchIndices[randomIndex]];
    
    delete[] matchIndices;
    return result;
}

Clue Clue::getClue(int id) {
    for (int i = 0; i < databaseSize; i++) {
        if (clueDatabase[i].getID() == id) {
            return clueDatabase[i];
        }
    }
    
    std::cerr << "Error: Clue with ID " << id << " not found!" << std::endl;
    return Clue();
}

std::string Clue::normalizeAnswer(std::string answer) {
    std::string normalized;
    
    for (char c : answer) {
        if (std::isalnum(c)) {
            normalized += std::tolower(c);
        } else if (std::isspace(c)) {
            if (!normalized.empty() && normalized.back() != ' ') {
                normalized += ' ';
            }
        }
    }
    
    size_t start = normalized.find_first_not_of(" ");
    if (start != std::string::npos) {
        normalized = normalized.substr(start);
    }
    
    size_t end = normalized.find_last_not_of(" ");
    if (end != std::string::npos) {
        normalized = normalized.substr(0, end + 1);
    }
    
    return normalized;
}

bool Clue::checkAnswer(const std::string& userAnswer) const {
    std::string normalizedUser = normalizeAnswer(userAnswer);
    std::string normalizedSolution = normalizeAnswer(solution);
    
    return normalizedUser == normalizedSolution;
}

void Clue::displayProblem() const {
    std::cout << "\n==================================" << std::endl;
    std::cout << "PUZZLE [" << category << "]" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << problem << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "You have " << maxAttempts << " attempt(s)." << std::endl;
}

void Clue::displayHint() const {
    std::cout << "\n HINT: " << hint << std::endl;
}

int Clue::getDatabaseSize() {
    return databaseSize;
}

void Clue::clearDatabase() {
    if (clueDatabase != nullptr) {
        delete[] clueDatabase;
        clueDatabase = nullptr;
    }
    databaseSize = 0;
    databaseCapacity = 0;
}
