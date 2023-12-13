#include "I_Terminos.h"

I_Terminos::I_Terminos()
{
    std::vector<Block> blocks;
    for (int i = 0; i < 4; i++)
    {
        Block temp(Color::RED);
        blocks.push_back(temp);
    }

    blocks[0].setPosition(sf::Vector2i(6, 0));
    blocks[1].setPosition(sf::Vector2i(6, -1));
    blocks[2].setPosition(sf::Vector2i(6, -2));
    blocks[3].setPosition(sf::Vector2i(6, -3));

    I_Terminos::SetUpTerminos(blocks);
}