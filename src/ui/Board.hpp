#ifndef BOARD
#define BOARD

#include "event/Event.hpp"
#include "physics/Element.hpp"
#include "physics/Particle.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <optional>
#include <random>
#include <stack>
#include <vector>

namespace Powder
{

using OptionalParticle = std::optional<Physics::Particle>;

class Board
{
  private:
    sf::Vector2u dimensions;

    std::vector< std::vector<OptionalParticle> > particles;
    //  HACK: find better way to avoid createParticle conflicts
    //  TODO: create ephemeral oldParticle buffer
    std::vector< std::vector<bool> > particleCreations;
    std::vector< std::vector<bool> > pointerPixels;

    sf::Vector2i mouseToBoardPosition(sf::Vector2i mousePosition);

    bool canSwap(sf::Vector2i origin, sf::Vector2i destination);

    Physics::Element activeElement;

    std::mt19937 randomEngine;

  public:
    Board(sf::Vector2u dimensions);

    void setActiveElement(Physics::Element element);

    const OptionalParticle at(sf::Vector2i position) const;
    void set(sf::Vector2i position, OptionalParticle particle);
    bool contains(sf::Vector2i position) const;

    void resetBoardState();

    void handleEvent(const Event& event, std::stack<Event>& events);
    void tick(sf::RenderWindow& window, std::stack<Event>& events);
};

} // namespace Powder

#endif // BOARD
