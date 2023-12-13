#include "Z_Terminos.h"

Z_Terminos::Z_Terminos()
{
    std::vector<Block> blocks;
    for (int i = 0; i < 4; i++)
    {
        Block temp(Color::GRAY);
        blocks.push_back(temp);
    }

    blocks[0].setPosition(sf::Vector2i(6, 0));
    blocks[1].setPosition(sf::Vector2i(7, 0));
    blocks[2].setPosition(sf::Vector2i(7, -1));
    blocks[3].setPosition(sf::Vector2i(8, -1));

    Z_Terminos::SetUpTerminos(blocks);
}