#include "Game.h"

void SetGrid(std::vector<std::vector<Color>>& grid, int Width, int Height)
{
	for (int i = 0; i < Width; i++)
	{
		std::vector<Color> temp;
		for (int j = 0; j < Height; j++)
		{
			temp.push_back(Color::BLACK);
		}
		grid.push_back(temp);
	}
}
Terminos* Game::RandomTerminos()
{

	TERMINOS type = Terminos::Randomize();
	Terminos* ter = NULL;

	if (type == TERMINOS::I)
		ter = static_cast<Terminos*>(new I_Terminos());
	else if (type == TERMINOS::J)
		ter = static_cast<Terminos*>(new J_Terminos());
	else if (type == TERMINOS::L)
		ter = static_cast<Terminos*>(new L_Terminos());
	else if (type == TERMINOS::O)
		ter = static_cast<Terminos*>(new O_Terminos());
	else if (type == TERMINOS::S)
		ter = static_cast<Terminos*>(new S_Terminos());
	else if (type == TERMINOS::T)
		ter = static_cast<Terminos*>(new T_Terminos());
	else if (type == TERMINOS::Z)
		ter = static_cast<Terminos*>(new Z_Terminos());
	return ter;

}
Game::Game() : IScreen()
{

	SetGrid(Grid, Width, Height);
	rectangle = sf::RectangleShape(sf::Vector2f(CellSize * Width, CellSize * Height));
	rectangle.setPosition(offset);
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(6);
	rectangle.setFillColor(sf::Color::Black);
	ScoreManager::getInstance().resetScore();
	for (int i = 0; i < NumberOfTerminos; i++)
		terminos.push_back(RandomTerminos());
}

Game::Game(sf::RenderWindow* window) : IScreen(window)
{
	SetGrid(Grid, Width, Height);
	rectangle = sf::RectangleShape(sf::Vector2f(CellSize * Width, CellSize * Height));
	rectangle.setPosition(offset);
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(6);
	rectangle.setFillColor(sf::Color::Black);
	ScoreManager::getInstance().resetScore();
	for (int i = 0; i < NumberOfTerminos; i++)
		terminos.push_back(RandomTerminos());

	gui.setWindow(*window);
	loadWidgets();
}


void Game::drawGameBoard(sf::RenderWindow* window)
{
	sf::RectangleShape rectangle(sf::Vector2f(CellSize * Width, CellSize * Height));
	rectangle.setPosition(offset);
	rectangle.setOutlineColor(sf::Color::Red);
	//rectangle.setOutlineThickness(5.f);
	rectangle.setFillColor(sf::Color::Black);
	window->draw(rectangle);
}
void Game::loadWidgets()
{
	messageBox = tgui::MessageBox::create("GAME OVER!", "DO YOU WANT TO RESTART THE GAME?");
	messageBox->addButton("Restart");
	messageBox->addButton("Exit");
	messageBox->setTextSize(20);
	
	messageBox->setPosition(200, 200);
	messageBox->setClientSize(tgui::Layout2d(500, 200));
	messageBox->setButtonAlignment(tgui::MessageBox::Alignment::Center);
	messageBox->setLabelAlignment(tgui::MessageBox::Alignment::Center);
	messageBox->onButtonPress([msgBox = messageBox.get(), game = this](const tgui::String& button) {
		
		if (button == "Restart")
		{
			StateManager::getInstance().setState(AppState::IN_GAME);
			msgBox->setVisible(false);
			game->ResetGame();
		}
		else if (button == "Exit")
		{
			msgBox->setVisible(false);
			game->ResetGame();
			StateManager::getInstance().setState(AppState::MAIN_MENU);
		}
		
		});
	messageBox->setVisible(false);
	widgets->add(messageBox);
	widgets->setVisible(true);
	//widgets->setPosition()
	gui.add(widgets);
}
void Game::Draw(sf::RenderWindow* window)
{
	//drawGameBoard(window);
	window->draw(rectangle);
	sf::RectangleShape cell(sf::Vector2f(CellSize - 2, CellSize - 2));
	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Height; j++)
		{
			cell.setPosition(sf::Vector2f(CellSize * i + offset.x, CellSize * j + offset.y));
			cell.setFillColor(Color1[static_cast<std::size_t>(Grid[i][j])]);
			window->draw(cell);
		}
	}
	sf::Font font;
	font.loadFromFile("Serpentine-yw3n3.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(600, 100));
	text.setString(sf::String(std::to_string(ScoreManager::getInstance().getScore())));
	window->draw(text);
}

void Game::DrawClearedRow(int row, float alpha)
{
	sf::RectangleShape rowRect(sf::Vector2f(CellSize * Width, CellSize));
	rowRect.setPosition(offset.x, offset.y + row * CellSize);

	rowRect.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * alpha))); // Set alpha value

	window.draw(rowRect);
}
void Game::HandleFullCollum()
{
	for (int y = Height - 1; y >= 0; --y)
	{
		bool isFullRow = true;
		for (int x = 0; x < Width; ++x)
		{
			if (Grid[x][y] == Color::BLACK)
			{
				isFullRow = false;
				break;
			}
		}

		if (isFullRow)
		{

			for (int i = y; i > 0; --i)
			{
				for (int x = 0; x < Width; ++x)
				{
					Grid[x][i] = Grid[x][i - 1];
				}
			}

			ScoreManager::getInstance().increaseScore(100);
			SoundManager::getInstance().playSound(SoundEvent::CLEAR);
		}
	}
	sf::sleep(sf::seconds(0.2));
}

bool Game::HandleGameOver()
{
	std::vector<Block> temp = terminos[0]->GetMinos();
	for (int i = 0; i < temp.size(); i++)
	{
		sf::Vector2i pos = temp[i].getPosition();
		if (pos.y < 0)
		{
			ScoreManager::getInstance().saveScore();
			SoundManager::getInstance().playSound(SoundEvent::GAME_OVER);
			return true;
		}
	}
	return false;
}
void Game::ResetGame()
{

	std::cout << "New game\n";
	ScoreManager::getInstance().resetScore();
	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Height; j++)
		{
			Grid[i][j] = Color::BLACK;
		}
	}
	terminos.clear();
	for (int i = 0; i < 3; i++)
		terminos.push_back(RandomTerminos());
	timeToUpdate = sf::Time::Zero;
}
void Game::RenderNextTermitos(sf::RenderWindow* window)
{
	std::vector<Block> nextTerminos = terminos[1]->GetMinos();
	sf::RectangleShape cell(sf::Vector2f(CellSize - 2, CellSize - 2));
	for (int i = 0; i < nextTerminos.size(); i++)
	{
		sf::Vector2i temp = nextTerminos[i].getPosition();
		cell.setPosition(temp.x * CellSize + 500, temp.y * CellSize + 500);

		cell.setFillColor(Color1[static_cast<std::size_t>(nextTerminos[0].getColor())]);
		window->draw(cell);
	}
}
void Game::Update(sf::RenderWindow* window)
{
	//window.create(sf::VideoMode(ScreenWidth, ScreenHeight), "Tetris game", sf::Style::Titlebar | sf::Style::Close);

	sf::Clock clock;
	sf::Time maxFrameTime = sf::seconds(1.f / FPS); // 7 FPS
	sf::Time deltaTime;

	sf::Event event;
	bool flag = true;
	while (window->isOpen()) {
		if (StateManager::getInstance().getState() == AppState::MAIN_MENU) break;
		//int state = StateManager::getInstance().getState();
		std::cout << "Current state: " << static_cast<int>(StateManager::getInstance().getState()) << std::endl;
		while (window->pollEvent(event))
		{
			gui.handleEvent(event);
			std::cout << "New loop\n";
			bool flag = true;
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
				{
					terminos[0]->Move_Left(Grid);
					SoundManager::getInstance().playSound(SoundEvent::MOVE);
					flag = false;
				}
				if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
				{
					terminos[0]->Move_Right(Grid);
					SoundManager::getInstance().playSound(SoundEvent::MOVE);
					flag = false;
				}
				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
				{
					terminos[0]->Rotate(Grid);
					SoundManager::getInstance().playSound(SoundEvent::ROTATE);
					flag = false;
				}
				if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
				{
					for (int i = 0; i < 2; i++) terminos[0]->Move_Down(Grid);
					SoundManager::getInstance().playSound(SoundEvent::MOVE);
					flag = false;
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					terminos[0]->Drop(Grid);
					SoundManager::getInstance().playSound(SoundEvent::DROP);
					flag = false;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{

			}
		}

		if (StateManager::getInstance().getState() == AppState::GAME_OVER)
			messageBox->setVisible(true);
		else
		{
			deltaTime = clock.restart();

			timeToUpdate += deltaTime;
			if (timeToUpdate.asSeconds() >= 0.25)
			{
				bool isUpdateNeeded = terminos[0]->Update(Grid);
				if (!isUpdateNeeded)
				{
					HandleFullCollum();
					if (HandleGameOver())
					{
						//if(StateManager::getInstance().getState() != AppState::GAME_OVER)
						StateManager::getInstance().setState(AppState::GAME_OVER);
						//widgets->setVisible(true);
					}
					delete terminos[0];
					terminos.erase(terminos.begin());
					terminos.push_back(RandomTerminos());
				}
				timeToUpdate = sf::Time::Zero;
		if (deltaTime >= maxFrameTime)
		{
			deltaTime = maxFrameTime;
		}
			}

		}

		window->clear();
		Draw(window);
		gui.draw();
		RenderNextTermitos(window);
		window->display();

		sf::sleep(maxFrameTime - deltaTime);

		// Limit frame rate
	}

}

//}