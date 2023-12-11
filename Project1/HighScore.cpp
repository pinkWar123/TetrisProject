#include "HighScore.h"

HighScore::HighScore() : IScreen()
{

}

HighScore::HighScore(sf::RenderWindow* window) : IScreen(window)
{
	loadWidgets();
}

void HighScore::Update(sf::RenderWindow* window)
{
	while (window->isOpen())
	{
		if (StateManager::getInstance().getState() == AppState::MAIN_MENU) break;
		sf::Event event;
		while (window->pollEvent(event))
		{
			Draw(window);
			gui.handleEvent(event);

		}
	}
}
void HighScore::loadWidgets()
{

}