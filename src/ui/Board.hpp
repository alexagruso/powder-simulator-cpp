#ifndef BOARD
#define BOARD

#include "event/Event.hpp"
#include "physics/Element.hpp"
#include "physics/Particle.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <optional>
#include <vector>

namespace Powder
{

using OptionalParticle = std::optional<Physics::Particle>;

class Board
{
  private:
    sf::Vector2u dimensions;

    std::vector< std::vector<OptionalParticle> > particles;

    sf::Vector2u mouseToBoardPosition(sf::Vector2i mousePosition);

    Physics::Element activeElement;

  public:
    Board(sf::Vector2u dimensions);

    void setActiveElement(Physics::Element element);

    const OptionalParticle at(sf::Vector2i position) const;
    void set(sf::Vector2i position, Physics::Element element);

    void handleEvent(const Event& event);
    void tick(sf::RenderWindow& window);
};

} // namespace Powder

#endif // BOARD
