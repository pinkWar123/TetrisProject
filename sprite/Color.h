#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class BlockTexture
{
private:
    BlockTexture();
public:
    void deleteData();
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

