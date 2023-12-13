#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class BlockTexture
{
public:
    BlockTexture();
    static BlockTexture& GetInstance();
    std::vector<sf::Texture *> textture;
};

enum class Color
{
    BLACK,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PINK,
    WHITE,
    GRAY
};

