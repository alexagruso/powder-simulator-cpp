#ifndef POWDER_ENTITY
#define POWDER_ENTITY

#include "application/Event.hpp"

#include <SFML/Graphics/Drawable.hpp>

#include <vector>

namespace Powder
{

struct Entity
{
    virtual std::vector<Event*> handleEvent(Event* event);

    virtual void tick();
    virtual std::vector<sf::Drawable*> render();
};

} // namespace Powder

#endif // POWDER_ENTITY
