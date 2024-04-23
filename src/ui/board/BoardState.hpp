#ifndef POWDER_BOARD_STATE
#define POWDER_BOARD_STATE

#include "physics/Particle.hpp"

#include <SFML/System/Vector2.hpp>

#include <optional>
#include <sys/types.h>
#include <vector>

using namespace Powder;

namespace Powder::UI
{

using BoardParticle = std::optional<Physics::Particle*>;
using BoardArray = std::vector<std::vector<BoardParticle>>;

// board model
struct BoardState
{
    // { row length, column length } for dimensions
    BoardState(sf::Vector2u dimensions);
    BoardState(const BoardState& boardState);
    ~BoardState();

    BoardParticle at(sf::Vector2u position) const;

    // replaces board particle at position with particle
    void replace(sf::Vector2u position, Physics::Particle* particle);

    // replaces board particle at position with particle if position is void
    void fill(sf::Vector2u position, Physics::Particle* particle);

    // swaps board particles at positionOne and positionTwo
    void swapReplace(sf::Vector2u positionOne, sf::Vector2u positionTwo);

    void swapFill(sf::Vector2u positionOne, sf::Vector2u positionTwo);

    // replaces board particle at position with void
    void reset(sf::Vector2u position);

    // checks if position is a valid board array index
    bool isValidPosition(sf::Vector2u position);

  private:
    sf::Vector2u dimensions;

    BoardArray particles;
};

} // namespace Powder::UI

#endif // BOARD_BOARD_STATE
