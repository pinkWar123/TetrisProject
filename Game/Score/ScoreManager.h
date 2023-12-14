#pragma once
#include <vector>
#include "../../Login/json.hpp"
#include <fstream>
#include <algorithm>
#include<iostream>
#include "../../Manager/UserManager.h"
using json = nlohmann::json;

class ScoreManager
{
public:
    static ScoreManager &getInstance();

    void setScore(int score);
    void increaseScore(int score);
    void resetScore();
    int getScore() const;
    int getHighestScores() const;
    void saveScore();
    std::vector<int> getHighScores();

private:
    int score;
    int HighestScore = 0;
    ScoreManager();
};
