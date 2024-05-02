#ifndef POWDER_EVENT_PARTICLE_CREATION
#define POWDER_EVENT_PARTICLE_CREATION

#include "application/events/Event.hpp"
#include "physics/Element.hpp"

#include <SFML/System/Vector2.hpp>

namespace Powder
{

struct ParticleCreationEvent : Event
{
    ParticleCreationEvent(sf::Vector2u position, Physics::Element* element) : position{position}, element{element} {}

    uint staticPriority() override;

    sf::Vector2u position;
    Physics::Element* element;

  protected:
    static const uint priority = 5;
};

} // namespace Powder

#endif // POWDER_EVENT_PARTICLE_CREATION
