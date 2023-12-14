#ifndef GAME
#define GAME
#include <iostream>
#include <vector>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include "Terminos/Terminos.h"
#include "../sprite/Color.h"
#include "Terminos/I_Terminos.h"
#include "Terminos/J_Terminos.h"
#include "Terminos/L_Terminos.h"
#include "Terminos/O_Terminos.h"
#include "Terminos/S_Terminos.h"
#include "Terminos/T_Terminos.h"
#include "Terminos/Z_Terminos.h"
#include "../Manager/Screen.h"
#include "Score/ScoreManager.h"
#include "../Sound/SoundManager.h"
#include <string.h>

// 0 = black, 1 = red, 2 = green, 3 = blue, 4 = yellow, 5 = dark blue,6 = pink, 7 = dark green

class Game : public IScreen
{
private:
    //-------------------------------------------------------------- Screen values --------------------------------
    const int CellSize = 45;
    const int Width = 12;
    const int Height = 20;
    const int ScreenWidth = CellSize * Width;
    const int ScreenHeight = CellSize * Height;
    const sf::Vector2f BoardGameOffset = sf::Vector2f(100, 20);
    const sf::Vector2f NextTerminosBoardOffset = sf::Vector2f(700, 100);
    const sf::Vector2f NextTerminosOffset = sf::Vector2f(520, 250);
    const sf::Vector2f TextOffset = sf::Vector2f(700, 400);
    //-- //----------------------------------------------------------------Manager variable --------------------------------

    sf::RenderWindow window;
    std::vector<Terminos *> terminos;
    tgui::MessageBox::Ptr messageBox;
    sf::Sprite GameBoard;
    sf::RectangleShape NextTerminosBoard;
    sf::Time timeToUpdate;
    sf::Font font;
    sf::Text ScoreText;
    sf::Text HighestScoreText;
    //-- //----------------------------------------------------------------Game variable --------------------------------
    std::vector<std::vector<Color>> Grid;
    int TotalScore = 0;
    const int NumberOfTerminos = 2;

    void HandleFullCollum();
    bool HandleGameOver();
    Terminos *RandomTerminos();
    void RenderNextTermitos(sf::RenderWindow *window);
    tgui::Gui gui;

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