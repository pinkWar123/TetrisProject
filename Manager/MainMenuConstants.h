#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum MainButton
{
	DICITONARY,
	FAVORITE_LIST,
	QUIZ,
	ABOUT_US
};

enum Extrabutton
{
	LOGO,
	TITLEAPP,
	USER_LOGO,
	USER_NAME,
	SETTINGS
};

// Font and color
const std::string fontPath = "Font/arial.ttf";
const sf::Color textColor = sf::Color::Black;
const sf::Color bkgColor = sf::Color(128,128,128);

// Title
const sf::Vector2f titlePos = sf::Vector2f(450.f, 100.f);
const sf::Vector2f titleSize = sf::Vector2f(540.f, 70.f);

// Dictionary
const sf::Vector2f dictPos = sf::Vector2f(520.f, 370.f);
const sf::Vector2f dictSize = sf::Vector2f(400, 104);

// Favorite list
const sf::Vector2f favPos = sf::Vector2f(520.f, dictPos.y + 149);
const sf::Vector2f favSize = dictSize;

// Quiz
const sf::Vector2f quizPos = sf::Vector2f(520.f, favPos.y + 149);
const sf::Vector2f quizSize = dictSize;

// About us
const sf::Vector2f aboutPos = sf::Vector2f(520.f, quizPos.y + 149);
const sf::Vector2f aboutSize = dictSize;
