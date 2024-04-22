#ifndef POWDER_BOARD_STATE
#define POWDER_BOARD_STATE

#include "application/Event.hpp"
#include "physics/Element.hpp"
#include "physics/Particle.hpp"

#include <SFML/System/Vector2.hpp>

#include <optional>
#include <sys/types.h>
#include <vector>

using namespace Powder;

namespace Powder
{

// type alias for optional particle instances
using OptParticle = std::optional<Physics::Particle>;

// type alias for a grid of OptParticle instances
using BoardArray = std::vector<std::vector<OptParticle>>;

// board model
struct BoardState
{
    // { row length, column length } for dimensions
    BoardState(sf::Vector2u dimensions);
    ~BoardState();

    OptParticle at(sf::Vector2u position) const;
    void setActiveElement(Physics::Element* element);

    std::vector<Event*> processPhysics();

  private:
    sf::Vector2u dimensions;

    BoardArray particles;
    Physics::Element* activeElement;
    Physics::Element* initialActiveElement;
};

} // namespace Powder

#endif // BOARD_BOARD_STATE
