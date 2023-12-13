#pragma once
#include "Screen.h"
#include "../Sound/SoundManager.h"
#include "../Game/Game.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class Setting : public IScreen
{
private:
	tgui::Slider::Ptr volume;
	tgui::RadioButtonGroup::Ptr difficulty;
	tgui::RadioButton::Ptr easyRadioButton;
	tgui::RadioButton::Ptr hardRadioButton;
	tgui::RadioButton::Ptr veryHardRadioButton;
	tgui::Button::Ptr BackButton;

	sf::Font font;
	sf::Text SettingText;
	sf::Text VolumeText;
	sf::Text DifficultyText;

public:
	Setting();
	Setting(sf::RenderWindow *window);
	void Update(sf::RenderWindow *window, bool HasExitGame) override;
	void loadWidgets() override;
};
