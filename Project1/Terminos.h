#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Block.h"
#include "Color.h"

const int gridWidth = 12;
const int gridHeight = 20;

enum class TERMINOS
{
    I,
    J,
    L,
    O,
    S,
    T,
    Z,
};
class Terminos
{
private:
    std::vector<Block> minos;

    // virtual void SetUpTerminos() = 0;
    bool IsRotationValid(std::vector<Block> &temp, std::vector<std::vector<Color>> &grid);
    static bool isValidPosition(sf::Vector2i position);

public:
    Terminos();
    static TERMINOS Randomize();
    void SetUpTerminos(std::vector<Block> &temp);
    void Drop(std::vector<std::vector<Color>> &grid);
    bool Move_Down(std::vector<std::vector<Color>> &grid);
    void Move_Right(std::vector<std::vector<Color>> &grid);
    void Move_Left(std::vector<std::vector<Color>> &grid);
    bool Update(std::vector<std::vector<Color>> &grid);
    void Rotate(std::vector<std::vector<Color>> &grid);
};