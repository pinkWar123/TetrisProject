#include "Program.h"


void Program::Run()
{
	window->setKeyRepeatEnabled(false);

	while (window->isOpen())
	{
		while (window->pollEvent(ev))
		{
			window->clear();
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
	BlockTexture::GetInstance().deleteData();
	BackGround::getinstance().DeleteData();
}


