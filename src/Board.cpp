#include "Board.hpp"

#include "Particle.hpp"

#include <optional>

using namespace Powder;

Board::Board(uint xSize, uint ySize) : width{xSize}, height{ySize}
{
    std::vector<OptParticle> emptyRow{width, std::nullopt};
    this->board = std::vector<std::vector<OptParticle>>{height, emptyRow};
}

OptParticle Board::at(uint x, uint y) const
{
    return this->board.at(y).at(x);
}

bool Board::set(uint x, uint y, OptParticle value)
{
    if (x >= this->width || y >= this->height)
    {
        return false;
    }

    this->board.at(y).at(x) = value;
    return true;
}

bool Board::isValidBoardPosition(int x, int y) const
{
    return x >= 0 && x < static_cast<int>(this->width) && y >= 0 && y < static_cast<int>(this->height);
}
