#pragma once
#include <SFML/Graphics.hpp>
#include "StateManager.h"
class IScreen
{
public:
	//IScreen(tgui::Gui &gui) : gui(gui) {}
	virtual void Draw(sf::RenderWindow* window) = 0;
	
	virtual void Update(sf::RenderWindow* window, sf::Event ev) = 0;
	
	virtual void Execute(sf::RenderWindow* window, sf::Event ev)
	{
		Draw(window);
		Update(window, ev);
	}

	void setState(AppState appState)
	{
		StateManager::getInstance().setState(appState);
	}
};