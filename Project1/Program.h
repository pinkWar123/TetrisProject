#pragma once
#include "MainMenu.h"
#include "SearchBox.h"
#include "Game.h"
#include "Login.h"
#include "Favorite.h"
#include "MainMenu.h"
#include "StateManager.h"



class Program
{
private:
	sf::RenderWindow* window;
	MainMenu* mainMenu;
	Login* login;
	Favorite* favorite;
	Game game;

	sf::Texture* texture;
	sf::Sprite* sprite;
	sf::Event ev;

	//void SwitchState(int nextState);
public:
	static tgui::Gui gui;
	Program();
	void Run();
};

