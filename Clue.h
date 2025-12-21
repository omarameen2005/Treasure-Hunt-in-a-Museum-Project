#ifndef CLUE_H
#define CLUE_H

#include <string>

class Clue {
private:
    int id;
    std::string problem;
    std::string solution;
    std::string hint;
    std::string category;
    int maxAttempts;

    static Clue* clueDatabase;
    static int databaseSize;
    static int databaseCapacity;

public:
    Clue();
    Clue(int id, const std::string& problem, const std::string& solution, 
         const std::string& hint, const std::string& category, int maxAttempts);

    int getID() const;
    std::string getProblem() const;
    std::string getSolution() const;
    std::string getHint() const;
    std::string getCategory() const;
    int getMaxAttempts() const;

    void setID(int id);
    void setProblem(const std::string& problem);
    void setSolution(const std::string& solution);
    void setHint(const std::string& hint);
    void setCategory(const std::string& category);
    void setMaxAttempts(int attempts);

    static bool loadFromFile(const std::string& filename);
    static Clue getRandomClue(const std::string& category = "");
    static Clue getClue(int id);
    static std::string normalizeAnswer(std::string answer);
    
    bool checkAnswer(const std::string& userAnswer) const;
    void displayProblem() const;
    void displayHint() const;
    static int getDatabaseSize();
    static void clearDatabase();
};

#endif 