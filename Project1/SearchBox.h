#pragma once
#include <SFML/Graphics.hpp>
#include "SearchBoxConstants.h"
#include <sstream>
// This class defines a search box where we search for words

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class SearchBox
{
private:
	
	sf::RectangleShape rect;
	
	sf::Text text;
	sf::Text emptyText;
	bool isFocused;

	std::string string;
	const sf::String emptyString = "Enter a word ...";
	sf::Font* font;
	sf::Clock clock;
	bool showCursor;

	void setFocus(sf::RenderWindow* window);
	bool isMouseOnButton(sf::RenderWindow* window);
	bool isClicked(sf::RenderWindow* window);
	void HandleInput(sf::Event ev);
	void setRect();
	void setText();
public:
	SearchBox();
	SearchBox(sf::Vector2f pos, sf::Vector2f size,sf::Font* font);
	void Draw(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window,sf::Event ev);
	
};