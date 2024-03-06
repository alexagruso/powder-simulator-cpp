#include "event/Event.hpp"
#include "ui/Button.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <random>
#include <stack>
#include <variant>
#include <vector>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const std::string WINDOW_TITLE = "Powder Simulator";

const sf::Color WINDOW_FILL_COLOR = sf::Color::Black;

Powder::Button button{
    {50, 50},
    {50, 50}
};

int main()
{
    sf::RenderWindow window{
        sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT},
        WINDOW_TITLE, sf::Style::Default
    };

    std::stack<Powder::Event> events;

    while (window.isOpen())
    {
        sf::Event systemEvent;

        while (window.pollEvent(systemEvent))
        {
            switch (systemEvent.type)
            {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                events.push(Powder::KeyboardEvent{systemEvent.key.code});
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                events.push(Powder::MouseEvent{systemEvent.mouseMove.x, systemEvent.mouseMove.y,
                                               systemEvent.mouseButton.button});
            }
            case sf::Event::MouseMoved:
            {
                events.push(Powder::MouseEvent{systemEvent.mouseMove.x, systemEvent.mouseMove.y,
                                               systemEvent.mouseButton.button});
                break;
            }
            default: break;
            }
        }

        window.clear(WINDOW_FILL_COLOR);

        while (!events.empty())
        {
            const Powder::Event& currentEvent = events.top();

            button.earlyUpdate(events.top());
            events.pop();
        }

        button.drawTo(&window);

        window.display();
    }

    return 0;
}