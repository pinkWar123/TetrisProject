#pragma once
#include "Screen.h"

class Setting : public IScreen
{
private:
	tgui::Slider::Ptr volume;
	tgui::SpinControl::Ptr difficulty;
public:
	Setting();
	Setting(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window) override;
	void loadWidgets() override;
};

