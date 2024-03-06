#include "Button.hpp"
#include "event/Event.hpp"
#include "util/Overload.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <variant>

using namespace Powder;

Button::Button(sf::Vector2u size, sf::Vector2i position)
    : width{size.x}, height{size.y}, xPosition{position.x}, yPosition{position.y}
{
    this->body = sf::RectangleShape({static_cast<float>(width), static_cast<float>(height)});
    this->body.setPosition(static_cast<float>(this->xPosition), static_cast<float>(this->yPosition));
    this->body.setFillColor(sf::Color::Red);
}

bool Button::contains(sf::Vector2i mousePosition) const
{
    bool isContainedOnXAxis = (mousePosition.x >= this->xPosition && mousePosition.x <= this->xPosition + this->width);
    bool isContainedOnYAxis = (mousePosition.y >= this->yPosition && mousePosition.y <= this->yPosition + this->height);

    return isContainedOnXAxis && isContainedOnYAxis;
}

bool Button::isActive() const
{
    return this->active;
}

void Button::drawTo(sf::RenderWindow* window) const
{
    window->draw(this->body);
}

void Button::setColor(sf::Color color)
{
    this->body.setFillColor(color);
}

void Button::earlyUpdate(Event event)
{
    std::visit(
        Util::Overloaded{
            [this](MouseEvent value)
            {
                if (this->contains({value.x, value.y}))
                {
                    this->setColor(sf::Color::Green);

                    if (value.button)
                    {
                        this->setColor(sf::Color::Blue);
                    }
                }
                else
                {
                    this->setColor(sf::Color::Red);
                }
            },
            [](auto value) {},
        },
        event);
}