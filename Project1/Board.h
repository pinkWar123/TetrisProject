#pragma once
#include <SFML/Graphics.hpp>


class Board
{
private:
	Board();
	~Board();
	int BOARD_HEIGHT;
	int BOARD_WIDTH;
	 int BLOCK_SIZE;
	bool** grid;
public:
	static Board& getInstance();
	int getBoardHeight() const;
	int getBoardWidth() const;
	int getBlockSize() const;
	void Draw(sf::RenderWindow* window);
	void setValueAtPosition(int row, int col, bool newValue);
};