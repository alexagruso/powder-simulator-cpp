#include "Board.hpp"

#include "Config.hpp"

using namespace Powder;

bool Board::at(uint x, uint y) const
{
    return this->board.at(y).at(x);
}

bool Board::set(uint x, uint y, bool value)
{
    if (x >= this->width || y >= this->height)
    {
        return false;
    }

    this->board.at(y).at(x) = value;
    return true;
}

std::optional<std::pair<uint, uint>> Board::mouseToBoardPosition(int mouseX, int mouseY) const
{
    int xPosition = mouseX / Config::PARTICLE_PIXEL_SIZE;
    int yPosition = mouseY / Config::PARTICLE_PIXEL_SIZE;

    if (this->isValidBoardPosition(xPosition, yPosition))
    {
        return {
            {static_cast<uint>(xPosition), static_cast<uint>(yPosition)}
        };
    }

    return std::nullopt;
}

bool Board::isValidBoardPosition(int x, int y) const
{
    return x >= 0 && x < static_cast<int>(this->width) && y >= 0 && y < static_cast<int>(this->height);
}
