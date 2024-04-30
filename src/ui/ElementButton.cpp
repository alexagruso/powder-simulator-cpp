#include "ElementButton.hpp"

#include "EntityPositioning.hpp"
#include "application/events/ChangeActiveElementEvent.hpp"
#include "application/events/InputEvent.hpp"
#include "physics/Element.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Mouse.hpp>

#include <vector>

using namespace Powder;

ElementButton::ElementButton(sf::Vector2u size, sf::Vector2i position, EntityPositioning positioning,
                             Physics::Element* element)
    : size{static_cast<float>(size.x), static_cast<float>(size.y)},
      position{static_cast<float>(position.x), static_cast<float>(position.y)}, positioning{positioning},
      element{element}
{
    this->body = new sf::RectangleShape{};

    this->body->setFillColor(this->element->fillColor());
    this->body->setPosition(this->position);
    this->body->setSize(this->size);
}

ElementButton::~ElementButton()
{
    delete this->element;
    delete this->body;
}

std::vector<Event*> ElementButton::handleEvent(Event* currentEvent)
{
    if (auto check = Event::isOfType<InputEvent>(currentEvent))
    {
        auto event = check.value();

        if (this->contains(event->getMousePosition()) && event->queryMouseButton(sf::Mouse::Left, InputStatus::PRESSED))
        {
            return {new ChangeActiveElementEvent{this->element}};
        }
    }

    return {};
}

// std::vector<Event*> ElementButton::tick()
// {
//     return {};
// }

std::vector<sf::Drawable*> ElementButton::render()
{
    return {this->body};
}

bool ElementButton::contains(sf::Vector2i mousePosition) const
{
    bool isContainedOnXAxis =
        (mousePosition.x >= this->position.x && mousePosition.x <= this->position.x + this->size.x);
    bool isContainedOnYAxis =
        (mousePosition.y >= this->position.y && mousePosition.y <= this->position.y + this->size.y);

    return isContainedOnXAxis && isContainedOnYAxis;
}
