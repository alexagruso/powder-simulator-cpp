#ifndef POWDER_BOARD_CONTROLLER
#define POWDER_BOARD_CONTROLLER

#include "physics/Element.hpp"
#include "ui/board/BoardState.hpp"

#include <SFML/System/Vector2.hpp>

namespace Powder::UI
{

using PhysicsEvents = std::vector<std::vector<bool>>;

struct BoardController
{
    BoardController(sf::Vector2u dimensions, Physics::Element* initialActiveElement);
    ~BoardController();

    void processPhysics();

    Physics::Element* activeElement;

  private:
    sf::Vector2u dimensions;
    Physics::Element* initialActiveElement;
    BoardState boardState;

    PhysicsEvents physicsEvents;
};

} // namespace Powder::UI

#endif // BOARD_BOARD_CONTROLLER
