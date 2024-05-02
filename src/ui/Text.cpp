#include "ui/Text.hpp"
#include "Button.hpp"
#include "config/Config.hpp"
#include "event/Event.hpp"
#include "util/Overloaded.hpp"
#include "ui/Positioning.hpp"
#include <iostream>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>

#include <stack>
#include <variant>
#include <SFML/Graphics/Text.hpp>

namespace Powder
{
    Text::Text(sf::Vector2i position, Positioning positioning = Positioning::LEFT)
        :position{static_cast<float>(position.x), static_cast<float>(position.y)}
    {
        this->text.setFillColor(sf::Color::White);
        this->text.setString("Hello World.");
        this->text.setCharacterSize(24);

        if(!font.loadFromFile("queensidesmedium.ttf")){
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

    void Text::setText(string name)
    {
        this->text.setString(name);
    }

    void Text::tick(sf::RenderWindow& window)
    {
        this->text.setPosition(this->position);
        this->text.setCharacterSize(24);

        window.draw(this->text);
    }
}
