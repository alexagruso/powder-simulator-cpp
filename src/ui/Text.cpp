#include "ui/Text.hpp"

#include "ui/Positioning.hpp"
#include "util/documentation.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <string>

using namespace Powder;

Text::Text(sf::Vector2i position, std::string value, Positioning positioning = Positioning::LEFT)
    : position{static_cast<float>(position.x), static_cast<float>(position.y)}
{
    UNUSED(positioning)

    this->text.setFillColor(sf::Color::White);
    this->text.setString(value);
    this->text.setCharacterSize(24);

    if (!font.loadFromFile("queensidesmedium.ttf"))
    {
        // Error
    }

    this->text.setFont(font);

    // positioning logic

    if (this->positioning == Positioning::RIGHT)
    {
        this->text.setPosition(this->position);
    }
}

void Text::setColor(sf::Color color)
{
    this->text.setFillColor(color);
}

void Text::setText(std::string name)
{
    this->text.setString(name);
}

void Text::render(sf::RenderWindow* window)
{
    this->text.setPosition(this->position);
    this->text.setCharacterSize(24);

    window->draw(this->text);
}
