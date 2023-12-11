//#include "Game.h"
//
//Game::Game()
//{
//
//}
//
//Game::~Game()
//{
//
//}
//
//void Game::Draw(sf::RenderWindow* window)
//{
//	Board::getInstance().Draw(window);
//}
//
//void Game::Update(sf::RenderWindow* window, sf::Event ev)
//{
//
//}

#include "Game.h"
std::vector<sf::Color> Color1 = { sf::Color::Black,
                                 sf::Color::Red,
                                 sf::Color::Green,
                                 sf::Color::Blue,
                                 sf::Color::Yellow,
                                 sf::Color::Cyan,
                                 sf::Color::White,
                                 sf::Color::Magenta };
void SetGrid(std::vector<std::vector<unsigned char>>& grid, int Width, int Height)
{
    for (int i = 0; i < Width; i++)
    {
        std::vector<unsigned char> temp;
        for (int j = 0; j < Height; j++)
        {
            temp.push_back('0');
        }
        grid.push_back(temp);
    }
}
Game::Game()
{
    SetGrid(Grid, Width, Height);
    TotalScore = 0;
}
void Game::RenderOnScreen()
{
    sf::RectangleShape cell(sf::Vector2f(CellSize - 2, CellSize - 2));
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if(Grid[i][j] == '0') 
                cell.setPosition(sf::Vector2f(CellSize * i, CellSize * j + timeToUpdate.asSeconds() / 0.25 * j));
            else cell.setPosition(sf::Vector2f(CellSize * i, CellSize * j));
            cell.setFillColor(Color1[Grid[i][j] - '0']);
            window.draw(cell);
        }
    }
}
void Game::HandleFullCollum()
{
    for (int y = Height - 1; y >= 0; --y)
    {
        bool isFullRow = true;
        for (int x = 0; x < Width; ++x)
        {
            if (Grid[x][y] == '0')
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

            TotalScore += 100;

            std::cout << "Score: " << TotalScore << std::endl;
        }
    }
}
void Game::PlayGame()
{
    window.create(sf::VideoMode(ScreenWidth, ScreenHeight), "Tetris game", sf::Style::Titlebar | sf::Style::Close);

    sf::Clock clock;
    sf::Time maxFrameTime = sf::seconds(1.f/ FPS); // 7 FPS
    sf::Time deltaTime;
    while (window.isOpen())
    {
        sf::Event event;
        bool flag = true;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                {
                    terminos.Move_Left(Grid);
                    flag = false;
                }
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                {
                    terminos.Move_Right(Grid);
                    flag = false;
                }
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    terminos.Rotate(Grid);
                    flag = false;
                }
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    terminos.Drop(Grid);
                    flag = false;
                }
            }
        }

            deltaTime = clock.restart();
        // Update here with deltaTime
        /*if (flag)
        {
            terminos.Update(Grid);

        }*/
        
        timeToUpdate += deltaTime;
        if (flag && timeToUpdate.asSeconds() >= 0.25)
        {
            terminos.Update(Grid);
            timeToUpdate = sf::Time::Zero;
        }
        HandleFullCollum();

        // Handle full collum event

        

        // Limit frame rate
        if (deltaTime >= maxFrameTime)
        {
            deltaTime = maxFrameTime;
        }
        
        window.clear();
        RenderOnScreen();
        window.display();

        sf::sleep(maxFrameTime - deltaTime);
    }
}