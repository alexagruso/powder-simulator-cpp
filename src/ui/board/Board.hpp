#ifndef POWDER_BOARD
#define POWDER_BOARD

#include <SFML/System/Vector2.hpp>

#include <optional>
#include <vector>

namespace Powder::UI
{

template <typename CellType>
struct Board
{
    Board(sf::Vector2u dimensions) : dimensions{dimensions}
    {
        std::vector<std::optional<CellType*>> emptyRow{std::nullopt, dimensions.x};
        this->board = std::vector< std::vector<std::optional<CellType*>>>{emptyRow, dimensions.y};
    }

    std::optional<CellType*> at(sf::Vector2u position) const
    {
        return this->board.at(position.y).at(position.x);
    }

    void set(sf::Vector2u position, CellType* value)
    {
        this->board.at(position.y).at(position.x) = value;
    }

    sf::Vector2u dimensions;

  private:
    std::vector<std::vector<std::optional<CellType*>>> board;
};

} // namespace Powder::UI

#endif // POWDER_BOARD
