#include "Game.h"

float Game::FPS = 50;
void SetGrid(std::vector<std::vector<Color>> &grid, int Width, int Height)
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
Terminos *Game::RandomTerminos()
{

	TERMINOS type = Terminos::Randomize();
	Terminos *ter = NULL;

	if (type == TERMINOS::I)
		ter = static_cast<Terminos *>(new I_Terminos());
	else if (type == TERMINOS::J)
		ter = static_cast<Terminos *>(new J_Terminos());
	else if (type == TERMINOS::L)
		ter = static_cast<Terminos *>(new L_Terminos());
	else if (type == TERMINOS::O)
		ter = static_cast<Terminos *>(new O_Terminos());
	else if (type == TERMINOS::S)
		ter = static_cast<Terminos *>(new S_Terminos());
	else if (type == TERMINOS::T)
		ter = static_cast<Terminos *>(new T_Terminos());
	else if (type == TERMINOS::Z)
		ter = static_cast<Terminos *>(new Z_Terminos());
	return ter;
}
Game::Game() : IScreen()
{
	FPS = 50;
	SetGrid(Grid, Width, Height);
	sf::Texture *gameboardTexture = new sf::Texture();
	gameboardTexture->loadFromFile("image/BoardGame.png");

	GameBoard.setTexture(*gameboardTexture);
	GameBoard.setPosition(offset);
	GameBoard.setScale(CellSize * Width * 1.0f / GameBoard.getLocalBounds().width, CellSize * Height * 1.0f / GameBoard.getLocalBounds().height);

	NextTerminosBoard = sf::RectangleShape(sf::Vector2f(200, 200));
	NextTerminosBoard.setPosition(sf::Vector2f(700, 150));
	NextTerminosBoard.setOutlineColor(sf::Color::Red);
	NextTerminosBoard.setOutlineThickness(6);
	NextTerminosBoard.setFillColor(sf::Color::Black);
	ScoreManager::getInstance().resetScore();
	for (int i = 0; i < NumberOfTerminos; i++)
		terminos.push_back(RandomTerminos());
}

Game::Game(sf::RenderWindow *window) : IScreen(window)
{
	FPS = 50;
	SetGrid(Grid, Width, Height);
	sf::Texture *gameboardTexture = new sf::Texture();
	gameboardTexture->loadFromFile("image/BoardGame.jpg");

	GameBoard.setTexture(*gameboardTexture);
	GameBoard.setPosition(offset);
	GameBoard.setScale((CellSize * Width * 1.0f + 3) * 1.0f / GameBoard.getLocalBounds().width, (CellSize * Height + 3) * 1.0f / GameBoard.getLocalBounds().height);

	NextTerminosBoard = sf::RectangleShape(sf::Vector2f(250, 250));
	NextTerminosBoard.setPosition(sf::Vector2f(700, 100));
	NextTerminosBoard.setOutlineColor(sf::Color::Red);
	NextTerminosBoard.setOutlineThickness(6);
	NextTerminosBoard.setFillColor(sf::Color::Black);

	if (!font.loadFromFile("Font/GameFont.ttf"))
	{
		std::cerr << "unable to load file GameFont.ttf\n";
	}

	ScoreText.setFont(font);
	ScoreText.setCharacterSize(65);
	ScoreText.setFillColor(sf::Color::White);
	ScoreText.setPosition(sf::Vector2f(620, 400));
	ScoreText.setString(sf::String("Score: " + std::to_string(ScoreManager::getInstance().getScore())));

	HighestScoreText.setFont(font);
	HighestScoreText.setCharacterSize(45);
	HighestScoreText.setFillColor(sf::Color::White);
	HighestScoreText.setPosition(sf::Vector2f(620, 500));
	HighestScoreText.setString(sf::String("Highest Score: " + std::to_string(ScoreManager::getInstance().getHighestScores())));

	ScoreManager::getInstance().resetScore();
	for (int i = 0; i < NumberOfTerminos; i++)
		terminos.push_back(RandomTerminos());

	gui.setWindow(*window);
	loadWidgets();
}
void Game::loadWidgets()
{
	messageBox = tgui::MessageBox::create("GAME OVER!", "DO YOU WANT TO RESTART THE GAME?\nYour Score:");
	messageBox->addButton("Restart");
	messageBox->addButton("Exit");
	messageBox->setTextSize(20);

	messageBox->setPosition(200, 200);
	messageBox->setClientSize(tgui::Layout2d(500, 200));
	messageBox->setButtonAlignment(tgui::MessageBox::Alignment::Center);
	messageBox->setLabelAlignment(tgui::MessageBox::Alignment::Center);
	messageBox->onButtonPress([msgBox = messageBox.get(), game = this](const tgui::String &button)
							  {
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
								  } });
	messageBox->setVisible(false);

	widgets->add(messageBox);
	widgets->setVisible(true);
	gui.add(widgets);
}
void Game::Draw(sf::RenderWindow *window)
{
	window->draw(GameBoard);
	window->draw(NextTerminosBoard);
	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Height; j++)
		{
			if (Grid[i][j] == Color::BLACK)
				continue;
			sf::Sprite cell(*BlockTexture::GetInstance().textture[static_cast<size_t>(Grid[i][j]) - 1]);
			cell.setScale(CellSize / cell.getLocalBounds().width, CellSize / cell.getLocalBounds().height);
			cell.setPosition(CellSize * i + offset.x, CellSize * j + offset.y);
			window->draw(cell);
		}
	}
	ScoreText.setString(sf::String("Score: " + std::to_string(ScoreManager::getInstance().getScore())));
	HighestScoreText.setString(sf::String("Highest Score: " + std::to_string(ScoreManager::getInstance().getScore())));
	window->draw(ScoreText);
	window->draw(HighestScoreText);
	RenderNextTermitos(window);
}
void Game::RenderNextTermitos(sf::RenderWindow *window)
{
	std::vector<Block> nextTerminos = terminos[1]->GetMinos();
	for (int i = 0; i < nextTerminos.size(); i++)
	{
		sf::Vector2i temp = nextTerminos[i].getPosition();
		sf::Sprite cell(*BlockTexture::GetInstance().textture[static_cast<size_t>(nextTerminos[0].getColor()) - 1]);
		cell.setScale(CellSize / cell.getLocalBounds().width, CellSize / cell.getLocalBounds().height);
		cell.setPosition(temp.x * CellSize + 520, temp.y * CellSize + 250);
		window->draw(cell);
	}
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
			++y;

			ScoreManager::getInstance().increaseScore(100);
			SoundManager::getInstance().playSound(SoundEvent::CLEAR);
		}
	}
	sf::sleep(sf::seconds(0.12));
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

void Game::Update(sf::RenderWindow *window, bool HasExitGame)
{
	sf::Clock clock;
	sf::Time maxFrameTime = sf::seconds(1.f / FPS);
	sf::Time deltaTime;

	sf::Event event;
	bool flag = true;
	while (window->isOpen())
	{
		if (StateManager::getInstance().getState() == AppState::MAIN_MENU)
			break;
		// int state = StateManager::getInstance().getState();
		std::cout << "Current state: " << static_cast<int>(StateManager::getInstance().getState()) << std::endl;
		while (window->pollEvent(event))
		{
			gui.handleEvent(event);
			std::cout << "New loop\n";
			bool flag = true;
			if (event.type == sf::Event::Closed)
			{
				HasExitGame = true;
				return;
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
					for (int i = 0; i < 2; i++)
						terminos[0]->Move_Down(Grid);
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
						StateManager::getInstance().setState(AppState::GAME_OVER);
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

		window->clear(sf::Color(55, 119, 162));
		Draw(window);
		gui.draw();
		window->display();

		sf::sleep(maxFrameTime - deltaTime);
	}
}

Game::~Game()
{
	for (int i = 0; i < terminos.size(); ++i)
	{
		delete terminos[i];
	}
}
//}