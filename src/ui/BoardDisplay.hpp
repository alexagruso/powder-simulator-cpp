#ifndef POWDER_BOARD_DISPLAY
#define POWDER_BOARD_DISPLAY

#include "Entity.hpp"
#include "ui/BoardState.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

namespace Powder
{

struct BoardDisplay : Entity
{
    // { row length, column length } for dimensions
    BoardDisplay(sf::Vector2u dimensions);
    ~BoardDisplay();

    std::vector<Event*> handleEvent(Event* event) override;

    void tick() override;
    std::vector<sf::Drawable*> render() override;

  private:
    sf::Vector2u dimensions;
    BoardState boardState;

    bool contains(sf::Vector2i mousePosition);
    std::optional<sf::Vector2u> mouseToBoardPosition(sf::Vector2i mousePosition);
};

} // namespace Powder

#endif // BOARD_BOARD_DISPLAY
