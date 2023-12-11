#include "ScoreManager.h"

ScoreManager::ScoreManager() : score(0) {}

ScoreManager& ScoreManager::getInstance()
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

void ScoreManager::increaseScore(int score)
{
	this->score += score;
}

void ScoreManager::resetScore()
{
	this->score = 0;
}

void ScoreManager::saveScore()
{
    std::ifstream stream("user.json", std::ios::in);
    json object = json::parse(stream);
    stream.close();

    // Check if the username already exists in the database
    auto it = std::find_if(object["user"].begin(), object["user"].end(), [this](const json& user) {
        return user["Username"] == UserManager::getInstance().getUserName()
            && user["Password"] == UserManager::getInstance().getPassword(); // Replace "Username" with the actual field name in your JSON
        });

    if (it != object["user"].end()) {
        // Username exists, update the existing entry
        if (!object["user"].contains("HighScore"))
            (*it)["HighScore"] = json::array();
        (*it)["HighScore"].push_back(score); // Update the password (replace "Password" with the actual field name)
    }
    else {
        // Username doesn't exist, add a new entry
        json newObject;
        newObject["Username"] = UserManager::getInstance().getUserName(); // Add the username (replace "Username" with the actual field name)
        newObject["Password"] = UserManager::getInstance().getPassword();
        newObject["Favorite"] = json::array();
        newObject["HighScore"] = score;
        object["user"].push_back(newObject);
    }

    std::ofstream os("user.json");
    os << object;
    os.close();
}

std::vector<int> ScoreManager::getHighScores()
{
    std::ifstream stream("user.json", std::ios::in);
    json object = json::parse(stream);
    stream.close();

    std::vector<int> highScores;
    auto it = std::find_if(object["user"].begin(), object["user"].end(), [this](const json& user) {
        return user["Username"] == UserManager::getInstance().getUserName()
            && user["Password"] == UserManager::getInstance().getPassword(); // Replace "Username" with the actual field name in your JSON
        });

    if (it != object["user"].end()) {
        // Username exists, update the existing entry
        if (!object["user"].contains("HighScore"))
            return (*it)["HighScore"]; // Update the password (replace "Password" with the actual field name)
    }
    return highScores;
}