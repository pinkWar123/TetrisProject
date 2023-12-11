#pragma once
#include <vector>
#include "json.hpp"
#include <fstream>
#include "UserManager.h"
using json = nlohmann::json;

class ScoreManager
{
public:
    static ScoreManager& getInstance();

    void setScore(int score);
    void increaseScore(int score);
    void resetScore();
    int getScore() const;

    void saveScore();
    std::vector<int> getHighScores();
private:
    int score;

    ScoreManager();
};

