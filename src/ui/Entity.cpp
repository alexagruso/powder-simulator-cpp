#include "Entity.hpp"

#include "application/Event.hpp"

#include <SFML/Graphics/Drawable.hpp>

#include <vector>

using namespace Powder;

std::vector<Event*> Entity::handleEvent(Event* event)
{
    return {};
}

void Entity::tick() {}

std::vector<sf::Drawable*> Entity::render()
{
    return {};
}
