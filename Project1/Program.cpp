#include "Program.h"



void Program::Run()
{
	window->setKeyRepeatEnabled(false);

	while (window->isOpen())
	{
		while (window->pollEvent(ev))
		{
			window->clear();
			window->draw(*sprite);
			gui.draw();
			gui.handleEvent(ev);
			if (ev.type == sf::Event::Closed)
				window->close();
			
			AppState currentState = StateManager::getInstance().getState();
			if (currentState == AppState::LOGIN)
			{
				//login->toggleVisible(true);
				login->Update(window);
			}
			else if (currentState == AppState::MAIN_MENU)
			{
				//mainMenu->toggleVisible(true);/*
				//mainMenu->getWidgets()->showWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(1000));*/
				mainMenu->Update(window);
			}
			else if(currentState == AppState::IN_GAME)
			{
				//mainMenu->getWidgets()->hideWithEffect(tgui::ShowEffectType::Fade, std::chrono::milliseconds(1000));
				//gui.removeAllWidgets();
				game->Update(window);
				//game.toggleVisible(true);
			}
			else if (currentState == AppState::SETTINGS)
			{
				setting->Update(window);
			}

			/*if (currentState == AppState::IN_GAME) 
			{
				Game game;
				game.Draw(window);
			}*/
			if(currentState != AppState::IN_GAME) window->display();
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
	

	// Load screens
	login = new Login(window);

	mainMenu = new MainMenu(window);
	setting = new Setting(window);
	
	game = std::make_shared<Game>(window);
	
	//game->Load(window);
}


