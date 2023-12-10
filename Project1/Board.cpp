#include "Board.h"

Board::Board()
{
	BOARD_HEIGHT = 20;
	BOARD_WIDTH = 10;
	BLOCK_SIZE = 40;

	grid = new bool* [BOARD_HEIGHT];
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		grid[i] = new bool[BOARD_WIDTH];
		for (int j = 0; j < BOARD_WIDTH; j++)
			grid[i][j] = false;
	}
}

Board::~Board()
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
		delete[] grid[i];
	delete[] grid;
}

Board& Board::getInstance()
{
	static Board instance;
	return instance;
}

void Board::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < BOARD_HEIGHT; ++i) {
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
			block.setOutlineColor(sf::Color::Black);
			block.setOutlineThickness(1);
			block.setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);

			// Fill the cell if it's not empty
			if (grid[i][j] != 0) {
				block.setFillColor(sf::Color::Cyan);  // Change color as needed
			}
			else {
				block.setFillColor(sf::Color::White);  // Empty cell color
			}

			window->draw(block);
		}
	}
}

void Board::setValueAtPosition(int row, int col, bool newValue)
{
	if (row < 0 || row >= BOARD_HEIGHT || col < 0 || col >= BOARD_WIDTH)
		return;
	grid[row][col] = newValue;

}