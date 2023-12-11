#include "S_Terminos.h"

S_Terminos::S_Terminos()
{
    std::vector<Block> blocks;
    for (int i = 0; i < 4; i++)
    {
        Block temp(Color::CYAN);
        blocks.push_back(temp);
    }

    blocks[0].setPosition(sf::Vector2i(6, 0));
    blocks[1].setPosition(sf::Vector2i(7, 0));
    blocks[2].setPosition(sf::Vector2i(6, -1));
    blocks[3].setPosition(sf::Vector2i(5, -1));

    S_Terminos::SetUpTerminos(blocks);
}