
#ifndef POWDER_EVENT_PARTICLE_DELETION
#define POWDER_EVENT_PARTICLE_DELETION

#include "application/events/Event.hpp"

#include <SFML/System/Vector2.hpp>

namespace Powder
{

struct ParticleDeletionEvent : Event
{
    ParticleDeletionEvent(sf::Vector2u position) : position{position} {}

    uint staticPriority() override;

    sf::Vector2u position;

  protected:
    static const uint priority = 5;
};

} // namespace Powder

#endif // POWDER_EVENT_PARTICLE_DELETION
