#include "BoardState.hpp"

#include "config/Config.hpp"
#include "physics/Element.hpp"
#include "physics/Particle.hpp"

#include <SFML/System/Vector2.hpp>

#include <vector>

using namespace Powder;

BoardState::BoardState(sf::Vector2u dimensions) : dimensions{dimensions}
{
    this->initialActiveElement = new Physics::Fire{};

    // initialize empty row
    //  INFO: element is temporary, just to test board display, should be std::nullopt
    std::vector<OptParticle> emptyRow = std::vector<OptParticle>{dimensions.x, std::nullopt};

    // push a copy of the empty row to each column
    this->particles = BoardArray{dimensions.y, emptyRow};
}

BoardState::~BoardState()
{
    delete this->initialActiveElement;
}

OptParticle BoardState::at(sf::Vector2u position) const
{
    //  TODO: bounds check this
    return this->particles.at(position.y).at(position.x);
}

void BoardState::setActiveElement(Physics::Element* element)
{
    this->activeElement = element;
}
