#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Draw(sf::RenderWindow* window)
{
	Board::getInstance().Draw(window);
}

void Game::Update(sf::RenderWindow* window, sf::Event ev)
{

}