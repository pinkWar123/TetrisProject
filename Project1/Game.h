
#ifndef GAME
#define GAME
#include <iostream>
#include <vector>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include "Terminos.h"
#include "Color.h"
#include "I_Terminos.h"
#include "J_Terminos.h"
#include "L_Terminos.h"
#include "O_Terminos.h"
#include "S_Terminos.h"
#include "T_Terminos.h"
#include "Z_Terminos.h"

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
    const int NumberOfTerminos = 3;
    const sf::Vector2f offset = sf::Vector2f(50, 0);
    //-- //----------------------------------------------------------------Manager values --------------------------------
    const float FPS = 120;
    sf::Time timeToUpdate;
    sf::RectangleShape rectangle;
    int TotalScore;
    sf::RenderWindow window;
    std::vector<std::vector<Color>> Grid;
    std::vector<Terminos *> terminos;

    void RenderOnScreen();
    void HandleFullCollum();
    void RandomTerminos();

public:
    Game();
    void PlayGame();
    void drawGameBoard(sf::RenderWindow* window);
    void Draw(sf::RenderWindow* window) override;
    void Update(sf::RenderWindow* window, sf::Event ev) override;
    void Update(sf::RenderWindow* window);
};
#endif