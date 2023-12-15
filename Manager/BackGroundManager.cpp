#include "BackGroundManager.h"

BackGround::BackGround()
{
    BackGroundTexture = new sf::Texture();
    LogoTexture = new sf::Texture();
    BackGroundSprite = new sf::Sprite();
    LogoSprite = new sf::Sprite();

    if (!BackGroundTexture->loadFromFile("image/Purple_BackGround.jpg"))
    {
        std::cout << "unable to load backGround texture" << std::endl;
        return;
    }
    if (!LogoTexture->loadFromFile("image/Logo.png"))
    {
        std::cout << "unable to load logo texture" << std::endl;
        return;
    }

    BackGroundSprite->setTexture(*BackGroundTexture);
    LogoSprite->setTexture(*LogoTexture);

    BackGroundSprite->setScale(1440 * 1.0f / BackGroundSprite->getLocalBounds().width, 1024 * 1.0f / BackGroundSprite->getLocalBounds().height);
    BackGroundSprite->setPosition(0, 0);

    LogoSprite->setScale(0.35, 0.35);
    LogoSprite->setPosition(550, 30);
}

void BackGround::DeleteData()
{
    delete LogoTexture;
    delete BackGroundSprite;
    delete BackGroundTexture;
    delete LogoSprite;
}

void BackGround::DrawBackGround(sf::RenderWindow *window)
{
    window->draw(*BackGroundSprite);
}
void BackGround::DrawLogo(sf::RenderWindow *window)
{
    window->draw(*LogoSprite);
}

BackGround& BackGround::getinstance()
{
    static BackGround instance;
    return instance;
}