#ifndef POWDER_BOARD
#define POWDER_BOARD

#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <optional>
#include <sys/types.h>
#include <vector>

namespace Powder::UI
{

template <typename CellType>
struct Board
{
    Board(sf::Vector2u dimensions) : dimensions{dimensions}
    {
        std::vector<std::optional<CellType>> emptyRow{dimensions.x, std::nullopt};
        this->board = std::vector<std::vector<std::optional<CellType>>>{dimensions.y, emptyRow};
    }

    std::optional<CellType> at(sf::Vector2u position) const
    {
        return this->board.at(position.y).at(position.x);
    }

    void set(sf::Vector2u position, CellType value)
    {
        this->board.at(position.y).at(position.x) = value;
    }

    void reset(sf::Vector2u position)
    {
        this->board.at(position.y).at(position.x) = std::nullopt;
    }

    sf::Vector2u dimensions;

  private:
    std::vector<std::vector<std::optional<CellType>>> board;
};

} // namespace Powder::UI

#endif // POWDER_BOARD
