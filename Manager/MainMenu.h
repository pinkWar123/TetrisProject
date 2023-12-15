#pragma once
#include "Screen.h"
#include "StateManager.h"
#include <vector>
#include "Button.h"
#include "MainMenuConstants.h"
#include "../Sound/SoundManager.h"
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

// class Program;

class MainMenu : public IScreen
{
private:
	std::vector<Button> button;
	SoundManager *sound;
	bool CloseGame = false;

public:
	MainMenu();
	MainMenu(sf::RenderWindow *window);
	MainMenu(sf::RenderWindow *window, SoundManager *&sound);
	void loadWidgets() override;

	tgui::Group::Ptr getWidgets();

	std::vector<Button> getButton();

	void handleExit();

	void Update(sf::RenderWindow *window, bool HasExitGame) override;
};
