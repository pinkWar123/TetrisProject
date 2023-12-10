#include "Program.h"



void Program::Run()
{
	window->setKeyRepeatEnabled(false);

	while (window->isOpen())
	{
		while (window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window->close();
			window->clear();
			window->draw(*sprite);
			gui.handleEvent(ev);
			AppState currentState = StateManager::getInstance().getState();
			if (currentState == AppState::LOGIN)
			{
				login->getWidgets()->setVisible(true);
				
			}
			else if (currentState == AppState::MAIN_MENU)
			{
				mainMenu->getWidgets()->setVisible(true);
			}
			else if(currentState == AppState::GAME)
			{
				game.Draw(window);
				
			}
			
			gui.draw();
			window->display();
		}
		
	}
}

Program::Program()
{
	// Initialize window and gui object
	window = new sf::RenderWindow(sf::VideoMode(1440, 1024), "Dictionary app", sf::Style::Titlebar | sf::Style::Close);
	gui.setWindow(*window);

	// Set texture and sprite and font
	texture = new sf::Texture();
	texture->loadFromFile("background3.jpg");
	texture->setSmooth(true);
	sprite = new sf::Sprite();
	sprite->setTexture(*texture);
	sprite->setScale(1440.f / texture->getSize().x, 1024.f / texture->getSize().y);
	sf::Font* font = new sf::Font();
	font->loadFromFile("arial.ttf");

	// Load screens
	login = new Login();
	login->Load(gui);

	mainMenu = new MainMenu();
	mainMenu->Load(gui);
}


