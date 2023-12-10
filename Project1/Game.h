#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Button.h"
#include "Board.h"
#include "Screen.h"

class Game : public IScreen
{
private:
	tgui::Button::Ptr backButton;
public:
	Game();
	~Game();
	void Draw(sf::RenderWindow* window) override;
	void Update(sf::RenderWindow* window, sf::Event ev) override;

};