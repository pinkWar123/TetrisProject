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
			bool HasExitInStateScreen = false;
			if (ev.type == sf::Event::Closed)
				window->close();
			
			AppState currentState = StateManager::getInstance().getState();
			if (currentState == AppState::LOGIN)
			{
				login->Update(window, HasExitInStateScreen);
			}
			else if (currentState == AppState::MAIN_MENU)
			{
				mainMenu->Update(window, HasExitInStateScreen);
			}
			else if(currentState == AppState::IN_GAME)
			{
				game->Update(window, HasExitInStateScreen);
			}
			else if (currentState == AppState::SETTINGS)
			{
				setting->Update(window, HasExitInStateScreen);
			}
			if(currentState != AppState::IN_GAME) window->display();
		
			if(HasExitInStateScreen)
			{
				window->close();
				return;
			}
		}
		
	}
}

Program::Program()
{
	// Initialize window and gui object
	window = new sf::RenderWindow(sf::VideoMode(1440, 1024), "Tetris Game", sf::Style::Titlebar | sf::Style::Close);
	gui.setWindow(*window);

	// Set texture and sprite and font
	texture = new sf::Texture();
	std::string src = "image/background3.jpg";
	texture->loadFromFile(src);
	texture->setSmooth(true);
	sprite = new sf::Sprite();
	sprite->setTexture(*texture);
	sprite->setScale(1440.f / texture->getSize().x, 1024.f / texture->getSize().y);
	

	// Load screens
	login = new Login(window);

	mainMenu = new MainMenu(window);
	setting = new Setting(window);
	
	game = std::make_shared<Game>(window);
}

Program::~Program()
{
	delete window;
	delete mainMenu;
	delete login;
	delete setting;

	delete texture;
	delete sprite;
}


