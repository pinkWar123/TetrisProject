#pragma once
#include <SFML/Graphics.hpp>

// This class defines the base class for any buttons

class Button
{
private:
	
	sf::RectangleShape rect;

	sf::Color color;
	sf::Color highlightColor;
	bool isFocused = false;

	sf::Font* font;
	sf::Text text;
	sf::Color textColor;
	sf::String string;

	sf::Texture* texture;

	virtual void SetFocus(sf::RenderWindow* window);
	virtual void setTextPosition(sf::Vector2f pos);
	bool IsMouseOnButton(sf::RenderWindow* window);
	
	
public:
	Button();
	Button(sf::Vector2f pos, sf::Vector2f size,sf::Font* font,sf::String string,sf::Color textColor, sf::Texture* texture);
	
	void Execute(sf::RenderWindow* window);
	void Initialize();
	
	bool isClicked(sf::RenderWindow* window);
	sf::RectangleShape getRect();
	sf::Text getText();
	void Update(sf::RenderWindow* window);
	void Draw(sf::RenderWindow* window);
};