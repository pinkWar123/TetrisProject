#pragma once
#include <SFML/Graphics.hpp>
#include "StateManager.h"

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "BackGroundManager.h"
class IScreen
{
protected:
	tgui::Group::Ptr widgets;
	tgui::Gui gui;

public:
	IScreen()
	{
	}

	IScreen(sf::RenderWindow *window)
	{
		gui.setWindow(*window);
		widgets = tgui::Group::create();
	}

	virtual void Draw(sf::RenderWindow *window)
	{
		gui.draw();
		window->display();
	}

	virtual void Update(sf::RenderWindow *window, bool HasExitGame) = 0;

	virtual void loadWidgets() = 0;

	void setState(AppState appState)
	{
		StateManager::getInstance().setState(appState);
		widgets->setVisible(false);
	}

	
};