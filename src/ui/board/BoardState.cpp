#include "BoardState.hpp"

#include "physics/Element.hpp"
#include "physics/Particle.hpp"

#include <SFML/System/Vector2.hpp>

#include <optional>
#include <vector>

using namespace Powder::UI;

BoardState::BoardState(sf::Vector2u dimensions) : dimensions{dimensions}
{
    std::vector<BoardParticle> emptyRow{dimensions.x, std::nullopt};
    this->particles = BoardArray{dimensions.y, emptyRow};
}

BoardState::BoardState(const BoardState& boardState) : dimensions{boardState.dimensions}
{
    std::vector<BoardParticle> emptyRow{dimensions.x, std::nullopt};
    this->particles = BoardArray{dimensions.y, emptyRow};

    for (uint row = 0; row < this->dimensions.x; row++)
    {
        for (uint column = 0; column < this->dimensions.y; column++)
        {
            if (auto checkParticle = boardState.particles.at(row).at(column))
            {
                Physics::Element* element = checkParticle.value()->element;
                this->particles.at(row).at(column) = new Physics::Particle{element};
            }
        }
    }
}

BoardState::~BoardState()
{
    for (std::vector<BoardParticle> row : this->particles)
    {
        for (BoardParticle particle : row)
        {
            if (particle)
            {
                delete particle.value();
            }
        }
    }
}

BoardParticle BoardState::at(sf::Vector2u position) const
{
    if (position.x >= this->dimensions.x || position.y >= this->dimensions.y)
    {
        return std::nullopt;
    }

    return this->particles.at(position.y).at(position.x);
}

void BoardState::replace(sf::Vector2u position, Physics::Particle* particle)
{
    this->particles.at(position.y).at(position.x) = particle;
}

void BoardState::fill(sf::Vector2u position, Physics::Particle* particle)
{
    if (!this->at(position))
    {
        this->particles.at(position.y).at(position.x) = particle;
    }
}

void BoardState::swapFill(sf::Vector2u positionOne, sf::Vector2u positionTwo)
{
    if (!this->at(positionTwo))
    {
        this->particles.at(positionTwo.y).at(positionTwo.x) = this->at(positionOne);
        this->particles.at(positionOne.y).at(positionOne.x) = std::nullopt;
    }
}

void BoardState::reset(sf::Vector2u position)
{
    this->particles.at(position.y).at(position.x) = std::nullopt;
}

bool BoardState::isValidPosition(sf::Vector2u position)
{
    return position.x >= 0 && position.x < this->dimensions.x && position.y >= 0 && position.y < this->dimensions.y;
}
