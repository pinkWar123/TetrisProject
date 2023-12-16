#pragma once
#include "MainMenu.h"
#include "../Game/Game.h"
#include "../Login/Login.h"
#include "Setting.h"
#include "StateManager.h"

class Program
{
private:
	sf::RenderWindow *window;
	MainMenu *mainMenu;
	Login *login;
	Setting *setting;
	std::shared_ptr<Game> game;

	sf::Event ev;

public:
	static tgui::Gui gui;
	Program();
	void Run();

	~Program();
};
