#include "Block.h"

Block::Block()
{
}

Block::Block(sf::Vector2i position, Color color)
	: position(position), color(color)
{
}
Block::Block(Color color)
	: color(color)
{
}

sf::Vector2i Block::getPosition() const
{
	return position;
}
Color Block::getColor() const
{
	return color;
}

void Block::setPosition(sf::Vector2i position)
{
	this->position = position;
}
void Block::setColor(Color color)
{
	this->color = color;
}