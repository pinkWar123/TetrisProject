#include "Game.h"

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
void Game::RandomTerminos()
{
    for(int i = 0; i < NumberOfTerminos; i++)
    {
        TERMINOS type = Terminos::Randomize();
        Terminos *ter;
        
        if(type == TERMINOS::I)
            ter = static_cast<Terminos *>(new I_Terminos());
        else if(type == TERMINOS::J)
            ter = static_cast<Terminos *>(new J_Terminos());
        else if(type == TERMINOS::L)
            ter = static_cast<Terminos *>(new L_Terminos());
        else if(type == TERMINOS::O)
            ter = static_cast<Terminos*>(new O_Terminos());
        else if(type == TERMINOS::S)
            ter = static_cast<Terminos *>(new S_Terminos());
        else if(type == TERMINOS::T)
            ter = static_cast<Terminos *>(new T_Terminos());
        else if(type == TERMINOS::Z)
            ter = static_cast<Terminos*>(new Z_Terminos());
        
        terminos.push_back(ter);
    }
}
Game::Game()
{
    SetGrid(Grid, Width, Height);
    rectangle = sf::RectangleShape(sf::Vector2f(CellSize * Width, CellSize * Height));
    rectangle.setPosition(offset);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(6);
    rectangle.setFillColor(sf::Color::Black);
    TotalScore = 0;
    RandomTerminos();
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

void Game::Draw(sf::RenderWindow* window)
{
    //drawGameBoard(window);
    window->draw(rectangle);
    sf::RectangleShape cell(sf::Vector2f(CellSize - 2, CellSize - 2));
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            if (Grid[i][j] == Color::BLACK)
                cell.setPosition(sf::Vector2f(CellSize * i, CellSize * j + timeToUpdate.asSeconds() / 0.25 * j));
            else
                cell.setPosition(sf::Vector2f(CellSize * i, CellSize * j));
            cell.setFillColor(Color1[static_cast<std::size_t>(Grid[i][j])]);
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

            TotalScore += 100;

            std::cout << "Score: " << TotalScore << std::endl;
        }
    }
}

void Game::Update(sf::RenderWindow* window, sf::Event ev) {}

void Game::Update(sf::RenderWindow* window)
{
    //window.create(sf::VideoMode(ScreenWidth, ScreenHeight), "Tetris game", sf::Style::Titlebar | sf::Style::Close);

    sf::Clock clock;
    sf::Time maxFrameTime = sf::seconds(1.f / FPS); // 7 FPS
    sf::Time deltaTime;

    sf::Event event;
    bool flag = true;
    while (window->isOpen()) {
        while (window->pollEvent(event))
        {
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
                    flag = false;
                }
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                {
                    terminos[0]->Move_Right(Grid);
                    flag = false;
                }
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    terminos[0]->Rotate(Grid);
                    flag = false;
                }
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    for(int i= 0; i < 2; i++) terminos.Move_Down(Grid);
                    flag = false;
                }
                if (event.key.code == sf::Keyboard::Space)
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

            window->clear();
            //RenderOnScreen();
            Draw(window);
            window->display();

            sf::sleep(maxFrameTime - deltaTime);
        
    }
}
//}