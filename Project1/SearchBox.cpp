#include "SearchBox.h"
#include "SearchBoxConstants.h"
#include <TGUI/AllWidgets.hpp>
SearchBox::SearchBox()
{
	setRect();
	setText();
	isFocused = false;
}

SearchBox::SearchBox(sf::Vector2f pos, sf::Vector2f size, sf::Font* font)
{
	this->font = font;
	clock = sf::Clock();
	showCursor = false;
	rect.setPosition(pos);
	rect.setSize(size);
	rect.setFillColor(sf::Color::White);
	rect.setOutlineColor(idleColor);
	rect.setOutlineThickness(2.0f);
	
	string = "";
	
	text.setString(string);
	text.setFont(*font);
	text.setPosition(rect.getPosition().x + 10, rect.getPosition().y + 10);
	text.setFillColor(textIdleColor);
	
	emptyText.setString(emptyString);
	emptyText.setFont(*font);
	emptyText.setPosition(rect.getPosition().x + 10, rect.getPosition().y + 10);
	emptyText.setFillColor(textIdleColor);
	isFocused = false;
}
void SearchBox::setRect()
{
	rect.setPosition(searchPos);
	rect.setSize(searchSize);
	rect.setFillColor(fillColor);
	rect.setOutlineColor(idleColor);
	rect.setOutlineThickness(2.0f);
}
void SearchBox::setText()
{
	string = "";
	text.setString(string);
	emptyText.setString(emptyString);
	emptyText.setFont(*font);
	emptyText.setPosition(rect.getPosition().x + 10, rect.getPosition().y + 10);
	emptyText.setFillColor(sf::Color::Black);
	text.setFont(*font);
	text.setPosition(rect.getPosition().x + 10, rect.getPosition().y + 10);
	text.setFillColor(sf::Color::Black);
}
void SearchBox::Draw(sf::RenderWindow* window)
{
	window->draw(rect);
	if (string.empty()) window->draw(emptyText);
	else
	{
		
		window->draw(text);
	}
}
bool SearchBox::isMouseOnButton(sf::RenderWindow* window)
{
	return rect.getGlobalBounds().contains(static_cast<sf::Vector2f> (sf::Mouse::getPosition(*window)));
}

void SearchBox::Update(sf::RenderWindow* window,sf::Event ev)
{
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		isFocused = (isMouseOnButton(window) ? true : false);
	}
	rect.setOutlineColor((isFocused) ? activeColor : idleColor);
	
	HandleInput(ev);
}

void SearchBox::HandleInput(sf::Event ev)
{
	if (!isFocused) return;
	
	if (ev.type == sf::Event::TextEntered)
	{
		int charTyped = ev.key.code;
		if (charTyped < 0 || charTyped >= 128) {}
		else if (charTyped == DELETE_KEY)
		{
			if (!string.empty()) string.pop_back();
		}
		else if (charTyped == ENTER_KEY)
		{
			// TO DO
		}
		else
		{
			string += charTyped;
		}
	}
	text.setString(string + '_');
}