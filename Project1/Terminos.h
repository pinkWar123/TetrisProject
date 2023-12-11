#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Block.h"

const int gridWidth = 12;
const int gridHeight = 20;
class Terminos
{
private:
    std::vector<Block> minos;

    void SetUpTerminos(int type);
    void RotateClockwise();
    bool IsRotationValid(std::vector<Block>& temp, std::vector<std::vector<unsigned char>>& grid);
    static bool isValidPosition(sf::Vector2i position);
    bool canMoveDown(std::vector<std::vector<unsigned char>>& grid);
public:
    Terminos();
    void Randomize();
    void Drop(std::vector<std::vector<unsigned char>>& grid);
    bool Move_Down(std::vector<std::vector<unsigned char>>& grid);
    void Move_Right(std::vector<std::vector<unsigned char>>& grid);
    void Move_Left(std::vector<std::vector<unsigned char>>& grid);
    void Update(std::vector<std::vector<unsigned char>>& grid);
    void Rotate(std::vector<std::vector<unsigned char>>& grid);
};