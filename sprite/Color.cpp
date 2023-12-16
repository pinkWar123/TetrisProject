#include "Color.h"

BlockTexture::BlockTexture()
{
    sf::Texture *RedBlock = new sf::Texture();
    RedBlock->loadFromFile("image/Red.png");

    sf::Texture *GreenBlock = new sf::Texture();
    GreenBlock->loadFromFile("image/Green.png");

    sf::Texture *BlueBlock = new sf::Texture();
    BlueBlock->loadFromFile("image/Blue.png");

    sf::Texture *YellowBlock = new sf::Texture();
    YellowBlock->loadFromFile("image/Yellow.png");

    sf::Texture *PinkBlock = new sf::Texture();
    PinkBlock->loadFromFile("image/Pink.png");

    sf::Texture *WhiteBlock = new sf::Texture();
    WhiteBlock->loadFromFile("image/White.png");

    sf::Texture *GrayBlock = new sf::Texture();
    GrayBlock->loadFromFile("image/Gray.png");

    textture.push_back(RedBlock);
    textture.push_back(GreenBlock);
    textture.push_back(BlueBlock);
    textture.push_back(YellowBlock);
    textture.push_back(PinkBlock);
    textture.push_back(WhiteBlock);
    textture.push_back(GrayBlock);
}

BlockTexture &BlockTexture::GetInstance()
{
    static BlockTexture instance;
    return instance;
}
void BlockTexture::deleteData()
{
    for(int i = 0; i < textture.size(); i++)
        delete textture[i];
}