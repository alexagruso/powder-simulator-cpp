#ifndef POWDER_BOARD_DISPLAY
#define POWDER_BOARD_DISPLAY

#include "application/events/Event.hpp"
#include "physics/Element.hpp"
#include "physics/Particle.hpp"
#include "ui/Entity.hpp"
#include "ui/board/Board.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <optional>
#include <random>
#include <vector>

namespace Powder::UI
{

struct BoardDisplay : UIEntity
{
    BoardDisplay(sf::Vector2u dimensions, Physics::Element* initialActiveElement);
    ~BoardDisplay() override;

    std::vector<Event*> handleEvent(Event* event) override;
    std::vector<Event*> tick() override;
    void render(sf::RenderWindow* window) override;

  private:
    Physics::Element* activeElement;
    Physics::Element* initialActiveElement;
    Board<Physics::Particle> particles;
    std::vector<std::vector<bool>> particleReservations;
    std::vector<std::vector<bool>> brush;
    std::mt19937 randomEngine;

    bool isValidBoardPosition(sf::Vector2i position) const;
    std::optional<sf::Vector2u> mouseToBoardPosition(sf::Vector2i mousePosition) const;
    bool canSwap(sf::Vector2u target) const;
    std::optional<std::vector<Event*>> attemptDirections(sf::Vector2u origin, std::vector<sf::Vector2i> directions,
                                                         Physics::Element* element);
};

} // namespace Powder::UI

#endif // POWDER_BOARD_DISPLAY
