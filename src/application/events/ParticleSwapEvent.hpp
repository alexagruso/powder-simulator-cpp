#ifndef POWDER_EVENT_PARTICLE_SWAP
#define POWDER_EVENT_PARTICLE_SWAP

#include "application/events/Event.hpp"

#include <SFML/System/Vector2.hpp>

namespace Powder
{

struct ParticleSwapEvent : Event
{
    ParticleSwapEvent(sf::Vector2u origin, sf::Vector2u target) : origin{origin}, target{target} {}

    uint staticPriority() override;

    sf::Vector2u origin;
    sf::Vector2u target;

  protected:
    static const uint priority = 5;
};

} // namespace Powder

#endif // POWDER_EVENT_PARTICLE_SWAP
