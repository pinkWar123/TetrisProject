#pragma once
#include "Screen.h"
#include "StateManager.h"
#include <vector>
#include "Button.h"
#include "MainMenuConstants.h"
#include "SoundManager.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

//class Program;

class MainMenu : public IScreen 
{
private:
	std::vector<Button> button;
public:
	MainMenu() : IScreen()
	{
		sf::Font* font = new sf::Font();
		sf::Texture* tex = new sf::Texture();
		font->loadFromFile(fontPath);
		tex->loadFromFile(texturePath);
		/*button.push_back(Button(titlePos, titleSize, font, "Dictionary", textColor, tex));
		button.push_back(Button(dictPos, dictSize, font, "Dictionary", textColor, tex));
		button.push_back(Button(favPos, favSize, font, "Favorite List", textColor, tex));
		button.push_back(Button(quizPos, quizSize, font, "Quiz", textColor, tex));
		button.push_back(Button(aboutPos, aboutSize, font, "About us", textColor, tex));*/
		
		

	}
	MainMenu(sf::RenderWindow* window) : IScreen(window)
	{
		sf::Font* font = new sf::Font();
		sf::Texture* tex = new sf::Texture();
		font->loadFromFile(fontPath);
		tex->loadFromFile(texturePath);

		loadWidgets();

	}

	void loadWidgets() override
	{
		tgui::Theme::Ptr theme = tgui::Theme::create({ "kenney.txt" });

		tgui::Button::Ptr button1 = tgui::Button::create("PLAY");
		button1->setPosition(dictPos.x, dictPos.y);
		button1->setSize(dictSize.x, dictSize.y);
		button1->setRenderer(theme->getRenderer("Button"));
		button1->setWidgetName("PLAY");
		button1->onClick(&IScreen::setState, this, AppState::IN_GAME);
		//button1->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(500));
		//button1->hideWithEffect(tgui::ShowEffectType::SlideToBottom, std::chrono::milliseconds(500));

		tgui::Button::Ptr button2 = tgui::Button::create("SETTINGS");
		button2->setSize(favSize.x, favSize.y);
		button2->setPosition(favPos.x, favPos.y);
		button2->setRenderer(theme->getRenderer("Button"));
		button2->setWidgetName("SETTINGS");
		button2->onClick(&IScreen::setState, this, AppState::SETTINGS);

		tgui::Button::Ptr button3 = tgui::Button::create();
		button3->setSize(quizSize.x, quizSize.y);
		button3->setPosition(quizPos.x, quizPos.y);
		button3->setRenderer(theme->getRenderer("Button"));
		button3->setWidgetName("Quiz");

		tgui::Button::Ptr button4 = tgui::Button::create();
		button4->setSize(aboutSize.x, aboutSize.y);
		button4->setPosition(aboutPos.x, aboutPos.y);
		button4->setRenderer(theme->getRenderer("Button"));
		button4->setWidgetName("About Us");

		widgets->add(button1);
		widgets->add(button2);
		widgets->add(button3);
		widgets->add(button4);

		widgets->setVisible(true);
		gui.add(widgets);
	}


	tgui::Group::Ptr getWidgets()
	{
		return widgets;
	}

	void Load(tgui::Gui &gui)
	{
		

		tgui::Theme::Ptr theme = tgui::Theme::create({ "kenney.txt" });

		tgui::Button::Ptr button1 = tgui::Button::create("PLAY");
		button1->setPosition(dictPos.x, dictPos.y);
		button1->setSize(dictSize.x, dictSize.y);
		button1->setRenderer(theme->getRenderer("Button"));
		button1->setWidgetName("PLAY");
		button1->onClick(&IScreen::setState, this,AppState::IN_GAME);
		//button1->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(500));
		//button1->hideWithEffect(tgui::ShowEffectType::SlideToBottom, std::chrono::milliseconds(500));
		
		tgui::Button::Ptr button2 = tgui::Button::create("SETTINGS");
		button2->setSize(favSize.x, favSize.y);
		button2->setPosition(favPos.x, favPos.y);
		button2->setRenderer(theme->getRenderer("Button"));
		button2->setWidgetName("SETTINGS");
		button2->onClick(&IScreen::setState, this, AppState::SETTINGS);
		
		tgui::Button::Ptr button3 = tgui::Button::create();
		button3->setSize(quizSize.x, quizSize.y);
		button3->setPosition(quizPos.x, quizPos.y);
		button3->setRenderer(theme->getRenderer("Button"));
		button3->setWidgetName("Quiz");

		tgui::Button::Ptr button4 = tgui::Button::create();
		button4->setSize(aboutSize.x, aboutSize.y);
		button4->setPosition(aboutPos.x, aboutPos.y);
		button4->setRenderer(theme->getRenderer("Button"));
		button4->setWidgetName("About Us");

		widgets->add(button1);
		widgets->add(button2);
		widgets->add(button3);
		widgets->add(button4);

		widgets->setVisible(true);
		gui.add(widgets);
	}

	std::vector<Button> getButton()
	{
		return button;
	}

	void Update(sf::RenderWindow* window)
	{
		widgets->setVisible(true);
		SoundManager::getInstance().setMusicState(MusicState::PLAY);
		while (window->isOpen())
		{
			if (StateManager::getInstance().getState() != AppState::MAIN_MENU)
			{
				SoundManager::getInstance().setMusicState(MusicState::STOP);
				break;
			}
			sf::Event event;
			while (window->pollEvent(event))
			{
				window->clear();
				Draw(window);
				gui.handleEvent(event);
			}
		}
	}
	
};
