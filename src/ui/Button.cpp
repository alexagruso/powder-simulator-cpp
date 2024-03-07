#include "Button.hpp"
#include "config/Config.hpp"
#include "event/Event.hpp"
#include "ui/Board.hpp"
#include "util/Overloaded.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>
#include <variant>

using namespace Powder;

Button::Button(sf::Vector2u size, sf::Vector2i position, Positioning positioning = Positioning::LEFT)
    : size{static_cast<float>(size.x), static_cast<float>(size.y)},
      position{static_cast<float>(position.x), static_cast<float>(position.y)}
{
    this->body.setSize(this->size);
    this->body.setFillColor(sf::Color::Red);

    // positioning logic

    if (this->positioning == Positioning::RIGHT)
    {
        this->position.x += (Config::WINDOW_WIDTH - size.x);
    }

    this->body.setPosition(this->position);
}

bool Button::contains(sf::Vector2i mousePosition) const
{
    bool isContainedOnXAxis =
        (mousePosition.x >= this->position.x && mousePosition.x <= this->position.x + this->size.x);
    bool isContainedOnYAxis =
        (mousePosition.y >= this->position.y && mousePosition.y <= this->position.y + this->size.y);

    return isContainedOnXAxis && isContainedOnYAxis;
}

void Button::setColor(sf::Color color)
{
    this->body.setFillColor(color);
}

// TODO: board parameter is for demo only
void Button::handleEvent(const Event& event, Board& board)
{
    std::visit(
        Util::Overloaded{
            [this, &board](const MouseEvent& event)
            {
                if (this->contains(event.position) && event.query(sf::Mouse::Left, InputStatus::PRESSED))
                {
                    board.setActiveElement(this->element);
                }
            },
            [](auto _) {},
        },
        event);
}

void Button::tick(sf::RenderWindow& window)
{
    this->body.setSize(this->size);
    this->body.setPosition(this->position);

    window.draw(this->body);
}