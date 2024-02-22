#include "Button.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

using namespace Powder;

UI::Button::Button(sf::Vector2u size, sf::Vector2i position)
    : width{size.x}, height{size.y}, xPosition{position.x}, yPosition{position.y}
{
    this->body = sf::RectangleShape({static_cast<float>(width), static_cast<float>(height)});
    this->body.setPosition(static_cast<float>(this->xPosition), static_cast<float>(this->yPosition));
    this->body.setFillColor(sf::Color::Green);
}

bool UI::Button::contains(sf::Vector2i mousePosition) const
{
    bool isContainedOnXAxis = (mousePosition.x >= this->xPosition && mousePosition.x <= this->xPosition + this->width);
    bool isContainedOnYAxis = (mousePosition.y >= this->yPosition && mousePosition.y <= this->yPosition + this->height);

    return isContainedOnXAxis && isContainedOnYAxis;
}

bool UI::Button::isActive() const
{
    return true;
}

void UI::Button::drawTo(sf::RenderWindow* window) const
{
    window->draw(this->body);
}

void UI::Button::setColor(sf::Color color)
{
    this->body.setFillColor(color);
}