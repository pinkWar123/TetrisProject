#pragma once
#include "../../Manager/Screen.h"

class HighScore : public IScreen
{
public:
	HighScore();
	HighScore(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, bool HasExitGame) override;
	void loadWidgets() override;
};

