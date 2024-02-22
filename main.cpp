#include "Button.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <random>
#include <vector>

using namespace Powder;

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const std::string WINDOW_TITLE = "Powder Simulator";

const sf::Color WINDOW_FILL_COLOR = sf::Color::Black;

int main()
{
    std::random_device device;
    std::mt19937 engine{device()};
    std::uniform_int_distribution<std::mt19937::result_type> randomXPosition(0, WINDOW_WIDTH);
    std::uniform_int_distribution<std::mt19937::result_type> randomYPosition(0, WINDOW_HEIGHT);

    sf::RenderWindow window{
        sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT},
        WINDOW_TITLE, sf::Style::Default
    };

    std::vector<UI::Button> buttons;

    for (int i = 0; i < 10; i++)
    {
        buttons.push_back(UI::Button({50, 50}, {(int) randomXPosition(engine), (int) randomYPosition(engine)}));
    }

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
            else if (event.type == sf::Event::MouseMoved)
            {
                for (UI::Button& button : buttons)
                {
                    if (button.contains({event.mouseMove.x, event.mouseMove.y}))
                    {
                        button.setColor(sf::Color::Blue); // Hovering
                    }
                    else
                    {
                        button.setColor(sf::Color::Green); // Not Hovering
                    }
                }
            }
        }

        window.clear(WINDOW_FILL_COLOR);

        for (const UI::Button& button : buttons)
        {
            button.drawTo(&window);
        }

        window.display();
    }

    return 0;
}