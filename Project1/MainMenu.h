#pragma once
#include "Screen.h"
#include "StateManager.h"
#include <vector>
#include "Button.h"
#include "MainMenuConstants.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

//class Program;

class MainMenu : public IScreen 
{
private:
	std::vector<Button> button;
	tgui::Group::Ptr widgets;
public:
	MainMenu()
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
	void IScreen::Draw(sf::RenderWindow* window)
	{
		for (int i = 0; i < button.size(); i++)
		{
			button[i].Draw(window);
		}
	}

	tgui::Group::Ptr getWidgets()
	{
		return widgets;
	}

	void Load(tgui::Gui &gui)
	{
		widgets = tgui::Group::create();
		//widgets->setWidgetName("MainMenu");

		tgui::Theme::Ptr theme = tgui::Theme::create({ "kenney.txt" });

		tgui::Button::Ptr button1 = tgui::Button::create("Dictionary");
		button1->setPosition(dictPos.x, dictPos.y);
		button1->setSize(dictSize.x, dictSize.y);
		button1->setRenderer(theme->getRenderer("Button"));
		button1->setWidgetName("Dictionary");
		button1->onClick(&IScreen::setState, this,AppState::GAME);

		tgui::Button::Ptr button2 = tgui::Button::create();
		button2->setSize(favSize.x, favSize.y);
		button2->setPosition(favPos.x, favPos.y);
		button2->setRenderer(theme->getRenderer("Button"));
		button2->setWidgetName("Favorite List");

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

		widgets->setVisible(false);
		gui.add(widgets);
	}

	std::vector<Button> getButton()
	{
		return button;
	}
	void IScreen::Update(sf::RenderWindow* window,sf::Event ev)
	{
		// To do		
	}
	
};
