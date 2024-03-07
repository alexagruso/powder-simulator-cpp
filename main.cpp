#include "event/Event.hpp"
#include "ui/Button.hpp"
#include "util/Overloaded.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <iostream>
#include <optional>
#include <random>
#include <stack>
#include <variant>
#include <vector>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const std::string WINDOW_TITLE = "Powder Simulator";

const sf::Color WINDOW_FILL_COLOR = sf::Color::Black;

const unsigned int FRAMERATE_LIMIT = 60;

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

    window.setFramerateLimit(FRAMERATE_LIMIT);

    std::stack<Powder::Event> events;

    Powder::KeyboardEvent keyboardEvent;
    Powder::MouseEvent mouseEvent;

    while (window.isOpen())
    {
        using Powder::InputStatus;

        sf::Event systemEvent;

        while (window.pollEvent(systemEvent))
        {
            using Powder::InputStatus;

            switch (systemEvent.type)
            {
                case sf::Event::Closed:
                {
                    events.push(Powder::ApplicationExitEvent{});
                }
                case sf::Event::KeyPressed:
                {
                    keyboardEvent.keys.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::PRESSED));
                    keyboardEvent.keys.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::ACTIVE));
                    break;
                }
                case sf::Event::KeyReleased:
                {
                    keyboardEvent.keys.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::RELEASED));
                    keyboardEvent.keys.reset(systemEvent.key.code * 3 + static_cast<int>(InputStatus::ACTIVE));
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    mouseEvent.buttons.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::PRESSED));
                    mouseEvent.buttons.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::ACTIVE));
                    break;
                }
                case sf::Event::MouseButtonReleased:
                {
                    mouseEvent.buttons.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::RELEASED));
                    mouseEvent.buttons.reset(systemEvent.key.code * 3 + static_cast<int>(InputStatus::ACTIVE));
                    break;
                }
                case sf::Event::MouseMoved:
                {
                    mouseEvent.moving = true;
                    mouseEvent.position = {systemEvent.mouseMove.x, systemEvent.mouseMove.y};
                    break;
                }
                default: break;
            }
        }

        events.push(keyboardEvent);
        events.push(mouseEvent);

        while (!events.empty())
        {
            using namespace Powder::Util;

            const Powder::Event& currentEvent = events.top();

            button.handleEvent(currentEvent);

            std::visit(Overloaded{[&window](const Powder::ApplicationExitEvent& _) { window.close(); },
                                  [&window](const Powder::KeyboardEvent& event)
                                  {
                                      if (event.query(sf::Keyboard::Escape, InputStatus::PRESSED))
                                      {
                                          window.close();
                                      }
                                  },
                                  [](auto _) {}},
                       currentEvent);

            events.pop();
        }

        // done with events

        // reset input states

        for (int i = 0; i < sf::Keyboard::KeyCount; i++)
        {
            keyboardEvent.keys.reset(i * 3 + static_cast<int>(InputStatus::PRESSED));
            keyboardEvent.keys.reset(i * 3 + static_cast<int>(InputStatus::RELEASED));
        }

        for (int i = 0; i < sf::Mouse::ButtonCount; i++)
        {
            mouseEvent.buttons.reset(i * 3 + static_cast<int>(InputStatus::PRESSED));
            mouseEvent.buttons.reset(i * 3 + static_cast<int>(InputStatus::RELEASED));
        }

        mouseEvent.moving = false;

        // drawing to window

        window.clear(WINDOW_FILL_COLOR);

        button.tick(window);

        window.display();
    }

    return 0;
}