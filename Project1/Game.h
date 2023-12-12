
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
#include "Screen.h"
#include "ScoreManager.h"
#include "SoundManager.h"
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
    const int NumberOfTerminos = 2;
    const sf::Vector2f offset = sf::Vector2f(50, 0);
    //-- //----------------------------------------------------------------Manager values --------------------------------
    const float FPS = 60;
    sf::Time timeToUpdate;
    sf::RectangleShape rectangle;
    int TotalScore = 0;
    sf::RenderWindow window;
    std::vector<std::vector<Color>> Grid;
    std::vector<Terminos *> terminos;
    tgui::MessageBox::Ptr messageBox;
    void DrawClearedRow(int row, float alpha);
    void HandleFullCollum();
    bool HandleGameOver();
    Terminos* RandomTerminos();
    void RenderNextTermitos(sf::RenderWindow* window);
    tgui::Gui gui;

public:
    Game();
    Game(sf::RenderWindow* window);
    void ResetGame();
    void loadWidgets() override;
    void drawGameBoard(sf::RenderWindow* window);
    void Draw(sf::RenderWindow* window) override;
    void Update(sf::RenderWindow* window) override;
    
};
#endif