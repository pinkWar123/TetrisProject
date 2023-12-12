#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include"Color.h"
class Block
{
private:
	sf::Vector2i position;
	Color color;
public:
	Block();
	Block(sf::Vector2i position, Color color);
	Block(Color color);

	sf::Vector2i getPosition() const;
	Color getColor() const;

	void setPosition(sf::Vector2i position);
	void setColor(Color color);
};
