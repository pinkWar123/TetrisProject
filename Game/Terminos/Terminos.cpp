#include "Terminos.h"

Terminos::Terminos()
{
}

TERMINOS Terminos::Randomize()
{
    //std::srand(static_cast<unsigned int>(std::time(0)));

    int randomNumber = std::rand() % 7;

    switch (randomNumber)
    {
    case 0:
        return TERMINOS::I;
    case 1:
        return TERMINOS::J;
    case 2:
        return TERMINOS::L;
    case 3:
        return TERMINOS::O;
    case 4:
        return TERMINOS::S;
    case 5:
        return TERMINOS::T;
    case 6:
        return TERMINOS::Z;
    default:
        std::cout << "Error: Invalid randomNumber" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
Color Terminos::GetColor()
{
    return minos[0].getColor();
}
std::vector<Block> Terminos::GetMinos()
{
    return minos;
}
void Terminos::SetUpTerminos(std::vector<Block> &temp)
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

void Terminos::Drop(std::vector<std::vector<Color>> &grid)
{
    while (Terminos::Move_Down(grid))
        ;
}

bool Terminos::Move_Down(std::vector<std::vector<Color>> &grid)
{
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (p.y < 0)
            continue;
        if (Terminos::isValidPosition(sf::Vector2i(p.x, p.y + 1)) && (grid[p.x][p.y + 1] != Color::BLACK && check(minos, sf::Vector2i(p.x, p.y + 1))) || p.y + 1 >= gridHeight)
            return false;
    }

    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Terminos::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = Color::BLACK;
        }
        minos[i].setPosition(sf::Vector2i(p.x, p.y + 1));
    }
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Terminos::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = minos[i].getColor();
        }
    }
    return true;
}

bool Terminos::Update(std::vector<std::vector<Color>> &grid)
{
    if (StateManager::getInstance().getState() == AppState::GAME_OVER) return false;
    bool canMoveDown = Move_Down(grid);
    return canMoveDown;
}

void Terminos::Move_Right(std::vector<std::vector<Color>> &grid)
{
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (p.x + 1 >= gridWidth)
            return;
        if (Terminos::isValidPosition(sf::Vector2i(p.x + 1, p.y)) && (grid[p.x + 1][p.y] != Color::BLACK && check(minos, sf::Vector2i(p.x + 1, p.y))))
            return;
    }

    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Terminos::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = Color::BLACK;
        }
        minos[i].setPosition(sf::Vector2i(p.x + 1, p.y));
    }
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Terminos::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = minos[i].getColor();
        }
    }
}

void Terminos::Move_Left(std::vector<std::vector<Color>> &grid)
{
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (p.x - 1 < 0)
            return;
        if (Terminos::isValidPosition(sf::Vector2i(p.x - 1, p.y)) && (grid[p.x - 1][p.y] != Color::BLACK && check(minos, sf::Vector2i(p.x - 1, p.y))))
            return;
    }

    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Terminos::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = Color::BLACK;
        }
        minos[i].setPosition(sf::Vector2i(p.x - 1, p.y));
    }
    for (int i = 0; i < minos.size(); i++)
    {
        sf::Vector2i p = minos[i].getPosition();
        if (Terminos::isValidPosition(sf::Vector2i(p.x, p.y)))
        {
            grid[p.x][p.y] = minos[i].getColor();
        }
    }
}
void Terminos::Rotate(std::vector<std::vector<Color>> &grid)
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
    { // Bước 3
        for (int i = 0; i < minos.size(); i++)
        {
            sf::Vector2i p = minos[i].getPosition();
            if (Terminos::isValidPosition(sf::Vector2i(p.x, p.y)))
            {
                grid[p.x][p.y] = Color::BLACK;
            }
        }
        for (int i = 0; i < minos.size(); i++)
        {
            sf::Vector2i p = temp[i].getPosition();
            if (Terminos::isValidPosition(sf::Vector2i(p.x, p.y)))
            {
                grid[p.x][p.y] = temp[i].getColor();
            }
            minos[i] = temp[i];
        }
    }
}

bool Terminos::IsRotationValid(std::vector<Block> &temp, std::vector<std::vector<Color>> &grid)
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

bool Terminos::isValidPosition(sf::Vector2i position)
{
    return position.x >= 0 && position.x < gridWidth && position.y >= 0 && position.y < gridHeight;
}