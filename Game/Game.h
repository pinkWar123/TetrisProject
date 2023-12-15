#ifndef GAME
#define GAME
#include <iostream>
#include <vector>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include "Tetromino/Tetromino.h"
#include "../sprite/Color.h"
#include "Tetromino/I_Tetromino.h"
#include "Tetromino/J_Tetromino.h"
#include "Tetromino/L_Tetromino.h"
#include "Tetromino/O_Tetromino.h"
#include "Tetromino/S_Tetromino.h"
#include "Tetromino/T_Tetromino.h"
#include "Tetromino/Z_Tetromino.h"
#include "../Manager/Screen.h"
#include "Score/ScoreManager.h"
#include "../Sound/SoundManager.h"
#include <string.h>

// 0 = black, 1 = red, 2 = green, 3 = blue, 4 = yellow, 5 = dark blue,6 = pink, 7 = dark green

class Game : public IScreen
{
private:
    //-------------------------------------------------------------- Screen values --------------------------------
    const int CellSize = 42;
    const int Width = 10;
    const int Height = 20;
    const int ScreenWidth = CellSize * Width;
    const int ScreenHeight = CellSize * Height;
    const sf::Vector2f BoardGameOffset = sf::Vector2f(100, 20);
    const sf::Vector2f AreaPlayerOffset = sf::Vector2f(BoardGameOffset.x + CellSize, BoardGameOffset.y + CellSize);
    const sf::Vector2f NextTerminosBoardOffset = sf::Vector2f(700, 100);
    const sf::Vector2f NextTerminosOffset = sf::Vector2f(520, 250);
    const sf::Vector2f TextOffset = sf::Vector2f(700, 400);
    //-- //----------------------------------------------------------------Manager variable --------------------------------
    sf::RenderWindow window;
    sf::Time timeToUpdate;
    sf::Font font;
    tgui::Gui gui;
    const int NumberOfTerminos = 2;
    //-- //----------------------------------------------------------------Draw variable --------------------------------
    std::vector<Tetromino *> terminos;
    tgui::MessageBox::Ptr messageBox;
    sf::Sprite GameBoard;
    sf::RectangleShape NextTerminosBoard;
    sf::Text ScoreText;
    sf::Text HighestScoreText;
    std::vector<std::vector<Color>> Grid;
    //-- //----------------------------------------------------------------Game function --------------------------------

    void HandleFullRow();
    bool HandleGameOver();
    Tetromino *RandomTerminos();
    void RenderNextTermitos(sf::RenderWindow *window);

public:
    static float FPS;
    static float Speed;
    Game();
    Game(sf::RenderWindow *window);
    void ResetGame();
    void loadWidgets() override;
    void Draw(sf::RenderWindow *window) override;
    void Update(sf::RenderWindow *window, bool HasExitGame) override;
    ~Game();
};
#endif