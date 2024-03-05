#include "Button.hpp"
#include "event/Event.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <random>
#include <variant>
#include <vector>

using namespace Powder;

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const std::string WINDOW_TITLE = "Powder Simulator";

const sf::Color WINDOW_FILL_COLOR = sf::Color::Black;

int main()
{
    sf::RenderWindow window{
        sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT},
        WINDOW_TITLE, sf::Style::Default
    };

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }

        window.clear(WINDOW_FILL_COLOR);

        window.display();
    }

    return 0;
}