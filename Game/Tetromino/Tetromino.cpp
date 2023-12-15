#include "Tetromino.h"

Tetromino::Tetromino()
{
}

TETROMINO Tetromino::Randomize()
{
    //std::srand(static_cast<unsigned int>(std::time(0)));

    int randomNumber = std::rand() % 7;

    switch (randomNumber)
    {
    case 0:
        return TETROMINO::I;
    case 1:
        return TETROMINO::J;
    case 2:
        return TETROMINO::L;
    case 3:
        return TETROMINO::O;
    case 4:
        return TETROMINO::S;
    case 5:
        return TETROMINO::T;
    case 6:
        return TETROMINO::Z;
    default:
        std::cout << "Error: Invalid randomNumber" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
Color Tetromino::GetColor()
{
    return minos[0].getColor();
}
std::vector<Block> Tetromino::GetMinos()
{
    return minos;
}
void Tetromino::SetUpTetromino(std::vector<Block> &temp)
{
    minos = temp;
}

bool check(std::vector<Block> &minos, sf::Vector2i pos)
{
    for (int i = 0; i < minos.size(); i++)
        if (minos[i].getPosition() == pos)
            return false;
    return true;
}

void Tetromino::Drop(std::vector<std::vector<Color>> &grid)
{
    while (Tetromino::Move_Down(grid))
        ;
}

bool Tetromino::Move_Down(std::vector<std::vector<Color>> &grid)
{
    // check  before moving
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (p.y < 0)
            continue;
        if (Tetromino::isValidPosition(sf::Vector2i(p.x, p.y + 1)) && (grid[p.x][p.y + 1] != Color::BLACK && check(minos, sf::Vector2i(p.x, p.y + 1))) || p.y + 1 >= gridHeight)
            return false;
    }

    //delete old grid position
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Tetromino::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = Color::BLACK;
        }
        // update new position on minos
        minos[i].setPosition(sf::Vector2i(p.x, p.y + 1));
    }
    //update new position on grid
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Tetromino::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = minos[i].getColor();
        }
    }
    return true;
}

bool Tetromino::Update(std::vector<std::vector<Color>> &grid)
{
    if (StateManager::getInstance().getState() == AppState::GAME_OVER) return false;
    bool canMoveDown = Move_Down(grid);
    return canMoveDown;
}

void Tetromino::Move_Right(std::vector<std::vector<Color>> &grid)
{
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (p.x + 1 >= gridWidth)
            return;
        if (Tetromino::isValidPosition(sf::Vector2i(p.x + 1, p.y)) && (grid[p.x + 1][p.y] != Color::BLACK && check(minos, sf::Vector2i(p.x + 1, p.y))))
            return;
    }

    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Tetromino::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = Color::BLACK;
        }
        minos[i].setPosition(sf::Vector2i(p.x + 1, p.y));
    }
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Tetromino::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = minos[i].getColor();
        }
    }
}

void Tetromino::Move_Left(std::vector<std::vector<Color>> &grid)
{
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (p.x - 1 < 0)
            return;
        if (Tetromino::isValidPosition(sf::Vector2i(p.x - 1, p.y)) && (grid[p.x - 1][p.y] != Color::BLACK && check(minos, sf::Vector2i(p.x - 1, p.y))))
            return;
    }

    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Tetromino::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = Color::BLACK;
        }
        minos[i].setPosition(sf::Vector2i(p.x - 1, p.y));
    }
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Tetromino::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = minos[i].getColor();
        }
    }
}
void Tetromino::Rotate(std::vector<std::vector<Color>> &grid)
{
    std::vector<Block> temp = minos; // Bước 1
    // Tính toán vị trí trung tâm xoay
    sf::Vector2i center = temp[1].getPosition();
    for (int i = 0; i < temp.size(); i++)
    {
        sf::Vector2i pos = temp[i].getPosition();
        int relativeX = pos.x - center.x;
        int relativeY = pos.y - center.y;

        // Xoay theo chiều kim đồng hồ 90 độ
        int newX = center.x - relativeY;
        int newY = center.y + relativeX;

        temp[i].setPosition(sf::Vector2i(newX, newY));
    }

    if (IsRotationValid(temp, grid))
    {
        for (int i = 0; i < minos.size(); i++)
        {
            sf::Vector2i p = minos[i].getPosition();
            if (Tetromino::isValidPosition(sf::Vector2i(p.x, p.y)))
            {
                grid[p.x][p.y] = Color::BLACK;
            }
        }
        for (int i = 0; i < minos.size(); i++)
        {
            sf::Vector2i p = temp[i].getPosition();
            if (Tetromino::isValidPosition(sf::Vector2i(p.x, p.y)))
            {
                grid[p.x][p.y] = temp[i].getColor();
            }
            minos[i] = temp[i];
        }
    }
}

bool Tetromino::IsRotationValid(std::vector<Block> &temp, std::vector<std::vector<Color>> &grid)
{
    // Kiểm tra xem tất cả các điểm mới có hợp lệ không
    for (int i = 0; i < temp.size(); i++)
    {
        sf::Vector2i pos = temp[i].getPosition();
        if (pos.x < 0 || pos.y < 0 || pos.x >= gridWidth || pos.y >= gridHeight ||
            (grid[pos.x][pos.y] != Color::BLACK && check(minos, pos)))
        {
            return false;
        }
    }
    return true;
}

bool Tetromino::isValidPosition(sf::Vector2i position)
{
    return position.x >= 0 && position.x < gridWidth && position.y >= 0 && position.y < gridHeight;
}