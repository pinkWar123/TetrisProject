#include "Block.h"

Block::Block()
{

}

Block::Block(sf::Vector2i position, unsigned char color)
	: position(position), color(color)
{

}
Block::Block(unsigned char color)
	: color(color)
{

}

sf::Vector2i Block::getPosition() const
{
	return position;
}
unsigned char Block::getColor() const
{
	return color;
}

void Block::setPosition(sf::Vector2i position)
{
	this->position = position;
}
void Block::setColor(unsigned char color)
{
	this -> color = color;
}