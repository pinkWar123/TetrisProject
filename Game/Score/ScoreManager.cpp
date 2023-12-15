#include "ScoreManager.h"

ScoreManager::ScoreManager() : score(0) {}

ScoreManager &ScoreManager::getInstance()
{
    static ScoreManager scoreManager;
    return scoreManager;
}

void ScoreManager::setScore(int score)
{
    this->score = score;
}
int ScoreManager::getScore() const
{
    return score;
}
int ScoreManager::getHighestScores() const
{
    std::vector<int> scores = ScoreManager::getInstance().getHighScores();

    if (scores.size() > 0)
        return scores[0];

    return 0;
}
void ScoreManager::increaseScore(int score)
{
    this->score += score;
    if (this->score > HighestScore)
        HighestScore = this->score;
}

void ScoreManager::resetScore()
{
    this->score = 0;
}

void ScoreManager::saveScore()
{
    std::ifstream stream("Login/user.json", std::ios::in);
    json object = json::parse(stream);
    stream.close();

    // Check if the username already exists in the database
    auto it = std::find_if(object["user"].begin(), object["user"].end(), [this](const json &user)
                           {
                               return user["Username"] == UserManager::getInstance().getUserName() && user["Password"] == UserManager::getInstance().getPassword(); // Replace "Username" with the actual field name in your JSON
                           });

    if (it != object["user"].end())
    {
        // Username exists, update the existing entry
        if (!(*it).contains("HighScore"))
            (*it)["HighScore"] = json::array();
        //(*it)["HighScore"].push_back(score); // Update the password (replace "Password" with the actual field name)
        std::cout << "HighScore updated" << std::endl;
        if ((*it)["HighScore"].size() > 5)
        {
            bool flag = false; //
            for (int i = 0; i < (*it)["HighScore"].size(); i++)
            {
                if ((score > (*it)["HighScore"][i]))
                {
                    (*it)["HighScore"].insert((*it)["HighScore"].begin() + i, score);
                    flag = true;
                    break;
                }
            }

            if (flag)
            {
                (*it)["HighScore"].erase((*it)["HighScore"].end());
            }
        }
        else
        {
            std::cout << "Before: " << (*it)["HighScore"].size() << std::endl;
            (*it)["HighScore"].push_back(score);
            std::cout << "after: " << (*it)["HighScore"].size() << std::endl;
            sort((*it)["HighScore"].begin(), (*it)["HighScore"].end(), std::greater<int>());
        }
    }
    else
    {
        std::cout << "Error";
    }

    std::ofstream os("Login/user.json");
    os << object;
    os.close();
}

std::vector<int> ScoreManager::getHighScores()
{
    std::ifstream stream("Login/user.json", std::ios::in);
    json object = json::parse(stream);
    stream.close();
    std::vector<int> highScores;
    auto it = std::find_if(object["user"].begin(), object["user"].end(), [this](const json &user)
                           {
                               return user["Username"] == UserManager::getInstance().getUserName() && user["Password"] == UserManager::getInstance().getPassword(); // Replace "Username" with the actual field name in your JSON
                           });

    if (it != object["user"].end())
    {
        if ((*it).contains("HighScore"))
            return (*it)["HighScore"];
    }
    return highScores;
}
