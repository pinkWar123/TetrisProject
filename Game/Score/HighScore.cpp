#include "HighScore.h"

HighScore::HighScore() : IScreen()
{

}

HighScore::HighScore(sf::RenderWindow* window) : IScreen(window)
{
	loadWidgets();
}

void HighScore::Update(sf::RenderWindow* window, bool HasExitGame)
{
	while (window->isOpen())
	{
		if (StateManager::getInstance().getState() == AppState::MAIN_MENU) break;
		sf::Event event;
		while (window->pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				HasExitGame = true;
				return;
			}
			Draw(window);
			gui.handleEvent(event);

		}
	}
}
void HighScore::loadWidgets()
{

}