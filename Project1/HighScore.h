#pragma once
#include "Screen.h"

class HighScore : public IScreen
{
public:
	HighScore();
	HighScore(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window) override;
	void loadWidgets() override;
};

