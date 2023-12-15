#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class BackGround
{
private:
    sf::Texture *BackGroundTexture;
    sf::Texture *LogoTexture;

    sf::Sprite *BackGroundSprite;
    sf::Sprite *LogoSprite;

    BackGround();
public:
    void DeleteData();
    void DrawBackGround(sf::RenderWindow *window);
    void DrawLogo(sf::RenderWindow *window);

    static BackGround &getinstance();
};