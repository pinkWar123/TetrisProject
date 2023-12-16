#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <limits>
#include "Block.h"
#include "../../sprite/Color.h"
#include "../../Manager/StateManager.h"

const int gridWidth = 10;
const int gridHeight = 20;

enum class TETROMINO
{
    I,
    J,
    L,
    O,
    S,
    T,
    Z,
};
class Tetromino
{
private:
    std::vector<Block> minos;

    // virtual void SetUpTerminos() = 0;
    bool IsRotationValid(std::vector<Block> &temp, std::vector<std::vector<Color>> &grid);
    static bool isValidPosition(sf::Vector2i position);

public:
    Tetromino();
    static TETROMINO Randomize();
    Color GetColor();
    std::vector<Block> GetMinos();
    void SetUpTetromino(std::vector<Block> &temp);
    void Drop(std::vector<std::vector<Color>> &grid);
    bool Move_Down(std::vector<std::vector<Color>> &grid);
    void Move_Right(std::vector<std::vector<Color>> &grid);
    void Move_Left(std::vector<std::vector<Color>> &grid);
    bool Update(std::vector<std::vector<Color>> &grid);
    void Rotate(std::vector<std::vector<Color>> &grid);
};


