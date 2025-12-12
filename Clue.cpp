#include "Clue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cctype>

// Initialize static members
Clue* Clue::clueDatabase = nullptr;
int Clue::databaseSize = 0;
int Clue::databaseCapacity = 0;

// Default constructor
Clue::Clue() : id(0), problem(""), solution(""), hint(""), category(""), maxAttempts(3) {}

// Parameterized constructor
Clue::Clue(int id, const std::string& problem, const std::string& solution, 
           const std::string& hint, const std::string& category, int maxAttempts)
    : id(id), problem(problem), solution(solution), hint(hint), 
      category(category), maxAttempts(maxAttempts) {}

// Getters
int Clue::getID() const { return id; }
std::string Clue::getProblem() const { return problem; }
std::string Clue::getSolution() const { return solution; }
std::string Clue::getHint() const { return hint; }
std::string Clue::getCategory() const { return category; }
int Clue::getMaxAttempts() const { return maxAttempts; }

// Setters
void Clue::setID(int id) { this->id = id; }
void Clue::setProblem(const std::string& problem) { this->problem = problem; }
void Clue::setSolution(const std::string& solution) { this->solution = solution; }
void Clue::setHint(const std::string& hint) { this->hint = hint; }
void Clue::setCategory(const std::string& category) { this->category = category; }
void Clue::setMaxAttempts(int attempts) { this->maxAttempts = attempts; }

/*
 * Load clues from a file into the database
 * File format (one clue per set of lines):
 * ID
 * PROBLEM
 * SOLUTION
 * HINT
 * CATEGORY
 * MAX_ATTEMPTS
 * --- (separator)
*/
bool Clue::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    // Clear existing database
    if (clueDatabase != nullptr) {
        delete[] clueDatabase;
        clueDatabase = nullptr;
    }
    databaseSize = 0;
    databaseCapacity = 10; // Initial capacity
    clueDatabase = new Clue[databaseCapacity];

    std::string line;
    int clueCount = 0;

    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        try {
            // Read ID
            int clueID = std::stoi(line);
            
            // Read problem
            std::string problem;
            if (!std::getline(file, problem)) break;
            
            // Read solution
            std::string solution;
            if (!std::getline(file, solution)) break;
            
            // Read hint
            std::string hint;
            if (!std::getline(file, hint)) break;
            
            // Read category
            std::string category;
            if (!std::getline(file, category)) break;
            
            // Read max attempts
            std::string attemptsStr;
            if (!std::getline(file, attemptsStr)) break;
            int maxAttempts = std::stoi(attemptsStr);
            
            // Resize array if needed
            if (databaseSize >= databaseCapacity) {
                databaseCapacity *= 2;
                Clue* newDatabase = new Clue[databaseCapacity];
                for (int i = 0; i < databaseSize; i++) {
                    newDatabase[i] = clueDatabase[i];
                }
                delete[] clueDatabase;
                clueDatabase = newDatabase;
            }
            
            // Add clue to database
            clueDatabase[databaseSize] = Clue(clueID, problem, solution, hint, category, maxAttempts);
            databaseSize++;
            clueCount++;
            
            // Read separator line (---)
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

/**
 * Get a random clue from the database
 * Optional category filter
*/
Clue Clue::getRandomClue(const std::string& category) {
    if (clueDatabase == nullptr || databaseSize == 0) {
        std::cerr << "Error: Clue database is empty!" << std::endl;
        return Clue(); // Return default clue
    }

    // Count matching clues and create temporary array
    int matchCount = 0;
    int* matchIndices = new int[databaseSize];

    // Filter by category if specified
    if (!category.empty()) {
        for (int i = 0; i < databaseSize; i++) {
            if (clueDatabase[i].getCategory() == category) {
                matchIndices[matchCount++] = i;
            }
        }
        
        if (matchCount == 0) {
            std::cerr << "Warning: No clues found for category '" << category 
                      << "'. Returning random clue from all categories." << std::endl;
            // Add all clues
            for (int i = 0; i < databaseSize; i++) {
                matchIndices[matchCount++] = i;
            }
        }
    } else {
        // Add all clues
        for (int i = 0; i < databaseSize; i++) {
            matchIndices[matchCount++] = i;
        }
    }

    // Generate random index
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, matchCount - 1);
    
    int randomIndex = distribution(generator);
    Clue result = clueDatabase[matchIndices[randomIndex]];
    
    delete[] matchIndices;
    return result;
}

/**
 * Get a specific clue by ID
*/
Clue Clue::getClue(int id) {
    for (int i = 0; i < databaseSize; i++) {
        if (clueDatabase[i].getID() == id) {
            return clueDatabase[i];
        }
    }
    
    std::cerr << "Error: Clue with ID " << id << " not found!" << std::endl;
    return Clue(); // Return default clue if not found
}

/**
 * Normalize answer for comparison
 * - Convert to lowercase
 * - Remove leading/trailing whitespace
 * - Remove extra spaces
 * - Remove punctuation (except letters and numbers)
*/
std::string Clue::normalizeAnswer(std::string answer) {
    std::string normalized;
    
    // Convert to lowercase and remove punctuation
    for (char c : answer) {
        if (std::isalnum(c)) {
            normalized += std::tolower(c);
        } else if (std::isspace(c)) {
            // Add space only if the last character wasn't a space
            if (!normalized.empty() && normalized.back() != ' ') {
                normalized += ' ';
            }
        }
    }
    
    // Trim leading spaces
    size_t start = normalized.find_first_not_of(" ");
    if (start != std::string::npos) {
        normalized = normalized.substr(start);
    }
    
    // Trim trailing spaces
    size_t end = normalized.find_last_not_of(" ");
    if (end != std::string::npos) {
        normalized = normalized.substr(0, end + 1);
    }
    
    return normalized;
}

/**
 * Check if user's answer matches the solution
 */
bool Clue::checkAnswer(const std::string& userAnswer) const {
    std::string normalizedUser = normalizeAnswer(userAnswer);
    std::string normalizedSolution = normalizeAnswer(solution);
    
    return normalizedUser == normalizedSolution;
}

/**
 * Display the problem/question to the player
 */
void Clue::displayProblem() const {
    std::cout << "\n==================================" << std::endl;
    std::cout << "PUZZLE [" << category << "]" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << problem << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "You have " << maxAttempts << " attempt(s)." << std::endl;
}

/**
 * Display the hint to help the player
 */
void Clue::displayHint() const {
    std::cout << "\n💡 HINT: " << hint << std::endl;
}

/**
 * Get the size of the clue database
 */
int Clue::getDatabaseSize() {
    return databaseSize;
}

/**
 * Clear the clue database (useful for cleanup or testing)
*/
void Clue::clearDatabase() {
    if (clueDatabase != nullptr) {
        delete[] clueDatabase;
        clueDatabase = nullptr;
    }
    databaseSize = 0;
    databaseCapacity = 0;
}
