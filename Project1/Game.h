#pragma once

//#include <TGUI/Backend/SFML-Graphics.hpp>
//#include <TGUI/TGUI.hpp>
//#include "Button.h"
//#include "Board.h"
//#include "Terminos.h"
//#include "Screen.h"
//
//class Game : public IScreen
//{
//private:
//	tgui::Button::Ptr backButton;
//	const int cellSize = 45;
//	const int width = 12;
//	const int height = 20;
//	const int screenWidth = cellSize * width;
//	const int screenHeight = cellSize * height;
//
//	const float FPS = 7;
//	int totalScore;
//	//sf::RenderWindow window;
//	std::vector<std::vector<unsigned char>> grid;
//	Terminos terminos;
//
//	void handleFullColumn();
//public:
//	Game();
//	~Game();
//	void Draw(sf::RenderWindow* window) override;
//	void Update(sf::RenderWindow* window, sf::Event ev) override;
//
//};

#ifndef GAME
#define GAME
#include <iostream>
#include <vector>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include "Terminos.h"

// 0 = black, 1 = red, 2 = green, 3 = blue, 4 = yellow, 5 = dark blue,6 = pink, 7 = dark green

class Game
{
private:
    //-------------------------------------------------------------- Screen values --------------------------------
    const int CellSize = 45;
    const int Width = 12;
    const int Height = 20;
    const int ScreenWidth = CellSize * Width;
    const int ScreenHeight = CellSize * Height;
    //-- //----------------------------------------------------------------Manager values --------------------------------
    const float FPS = 120;
    sf::Time timeToUpdate;

    int TotalScore;
    sf::RenderWindow window;
    std::vector<std::vector<unsigned char>> Grid;
    Terminos terminos;

    void RenderOnScreen();
    void HandleFullCollum();

public:
    Game();
    void PlayGame();
};
#endif