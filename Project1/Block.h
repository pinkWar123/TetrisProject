#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Block
{
private:
	sf::Vector2i position;
	unsigned char color;
public:
	Block();
	Block(sf::Vector2i position, unsigned char color);
	Block(unsigned char color);

	sf::Vector2i getPosition() const;
	unsigned char getColor() const;

	void setPosition(sf::Vector2i position);
	void setColor(unsigned char color);
};

