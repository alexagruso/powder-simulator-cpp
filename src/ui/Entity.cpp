#include "Entity.hpp"

#include "util/documentation.hpp"

#include <SFML/Graphics/Drawable.hpp>

#include <vector>

using namespace Powder;

std::vector<Event*> UIEntity::handleEvent(Event* event)
{
    UNUSED(event)

    return {};
}

std::vector<Event*> UIEntity::tick()
{
    return {};
}

void UIEntity::render(sf::RenderWindow* window)
{
    UNUSED(window)
}
