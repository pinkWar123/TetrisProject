#include "Button.h"
#include <iostream>

Button::Button()
{
	isFocused = false;
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Font* font,sf::String string,sf::Color textColor, sf::Texture* texture)
{
	
	this->texture = texture;
	this->textColor = textColor;
	this->string = string;
	this->highlightColor = highlightColor;
	this->font = new sf::Font(*font);
	
	rect = sf::RectangleShape(size);
	rect.setFillColor(sf::Color::Transparent);
	rect.setPosition(pos);
	rect.setSize(size);
	
	rect.setTexture(this->texture);

	text.setFont(*font);
	text.setString(string);
	//text.setCharacterSize(40);
	text.setFillColor(textColor);
	text.setStyle(sf::Text::Bold);
	setTextPosition(pos);

	isFocused = false;
}
void Button::setTextPosition(sf::Vector2f pos)
{
	float pos_x = (pos.x + rect.getGlobalBounds().width / 2.0f) -
		(text.getGlobalBounds().width / 2);
	float pos_y = (pos.y + rect.getGlobalBounds().height / 2.0f) -
		(text.getGlobalBounds().height / 2) - 5;
	text.setPosition(pos_x, pos_y);
}
void Button::Draw(sf::RenderWindow* window)
{
	if (isFocused) rect.setFillColor(sf::Color::Yellow);
	else rect.setFillColor(sf::Color::White);
	window->draw(rect);
	window->draw(text);
}

void Button::Update(sf::RenderWindow* window)
{
	SetFocus(window);
	
}

void Button::Initialize()
{
}
void Button::Execute(sf::RenderWindow* window)
{
	Update(window);
	Draw(window);
}
bool Button::IsMouseOnButton(sf::RenderWindow* window)
{
	return rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)));
}

void Button::SetFocus(sf::RenderWindow* window)
{
	if (IsMouseOnButton(window))
	{
		isFocused = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || !IsMouseOnButton(window))
	{
		isFocused = false;
	}
}

bool Button::isClicked(sf::RenderWindow* window)
{
	return IsMouseOnButton(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

sf::RectangleShape Button::getRect()
{
	return rect;
}

sf::Text Button::getText()
{
	return text;
}