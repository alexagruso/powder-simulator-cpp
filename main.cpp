#include "config/Config.hpp"
#include "event/Event.hpp"
#include "physics/Element.hpp"
#include "ui/Board.hpp"
#include "ui/Button.hpp"
#include "util/Overloaded.hpp"
#include "ui/Positioning.hpp"
#include "ui/Text.hpp"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <stack>
#include <variant>

int main()
{
    using namespace Powder;

    Powder::Board board{
        {100, 100},
    };

    Powder::Text elementSelect{
        {600, 10},
        Positioning::RIGHT,
    };

    Powder::Button woodButton{
        {50, 50},
        {0,  50},
        Positioning::RIGHT,
    };

    Powder::Text woodLabel{
        {575, 60},
        Positioning::RIGHT,
    };


    Powder::Button stoneButton{
        {50, 50},
        {0,  100},
        Positioning::RIGHT,
    };

    Powder::Text stoneLabel{
        {575, 110},
        Positioning::LEFT,
    };

    Powder::Button plantButton{
        {50, 50 },
        {0,  150},
        Positioning::RIGHT,
    };

    Powder::Text plantLabel{
        {575, 160},
        Positioning::LEFT,
    };

    Powder::Button fireButton{
        {50, 50 },
        {0,  200},
        Positioning::RIGHT,
    };

    Powder::Text fireLabel{
        {575, 210},
        Positioning::LEFT,
    };

    Powder::Button waterButton{
        {50, 50 },
        {0,  250},
        Positioning::RIGHT,
    };

    Powder::Text waterLabel{
        {575, 260},
        Positioning::LEFT,
    };

    woodButton.element = Powder::Physics::Wood{};
    woodButton.setColor(sf::Color::Yellow);
    stoneButton.element = Powder::Physics::Stone{};
    stoneButton.setColor(sf::Color::White);
    plantButton.element = Powder::Physics::Plant{};
    plantButton.setColor(sf::Color::Green);
    fireButton.element = Powder::Physics::Fire{};
    fireButton.setColor(sf::Color::Red);
    waterButton.element = Powder::Physics::Water{};
    waterButton.setColor(sf::Color::Blue);


    elementSelect.setText("Select Element");
    woodLabel.setText("Wood");
    stoneLabel.setText("Stone");
    plantLabel.setText("Plant");
    fireLabel.setText("Fire");
    waterLabel.setText("Water");

    sf::RenderWindow window{
        sf::VideoMode{Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT},
        Config::WINDOW_TITLE, sf::Style::Default
    };

    window.setFramerateLimit(Config::FRAMERATE_LIMIT);

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

            //! Each branch of this switch statement is a different SFML event that can occur,
            //? I opted to not put this functionality into a member function because I don't intend for the
            //? std::bitset instances to be accessed directly from external objects.
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

                    if (!mouseEvent.moving)
                    {
                        mouseEvent.position = {systemEvent.mouseButton.x, systemEvent.mouseButton.y};
                    }

                    break;
                }
                case sf::Event::MouseButtonReleased:
                {
                    mouseEvent.buttons.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::RELEASED));
                    mouseEvent.buttons.reset(systemEvent.key.code * 3 + static_cast<int>(InputStatus::ACTIVE));

                    if (!mouseEvent.moving)
                    {
                        mouseEvent.position = {systemEvent.mouseButton.x, systemEvent.mouseButton.y};
                    }

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

            const Powder::Event currentEvent = events.top();
            events.pop();

            board.handleEvent(currentEvent, events);

            woodButton.handleEvent(currentEvent, events);
            stoneButton.handleEvent(currentEvent, events);
            plantButton.handleEvent(currentEvent, events);
            fireButton.handleEvent(currentEvent, events);
            waterButton.handleEvent(currentEvent, events);

            std::visit(Overloaded{[&window](const Powder::ApplicationExitEvent& _)
                                  {
                                      window.close();
                                  },
                                  [&window](const Powder::KeyboardEvent& event)
                                  {
                                      if (event.query(sf::Keyboard::Escape, InputStatus::PRESSED))
                                      {
                                          window.close();
                                      }
                                  },
                                  [](auto _) {}},
                       currentEvent);
        }

        // Done with events

        // Reset input states

        for (int i = 0; i < sf::Keyboard::KeyCount; i++)
        {
            // <keyCode * 3 + status>
            keyboardEvent.keys.reset(i * 3 + static_cast<int>(InputStatus::PRESSED));
            keyboardEvent.keys.reset(i * 3 + static_cast<int>(InputStatus::RELEASED));
        }

        for (int i = 0; i < sf::Mouse::ButtonCount; i++)
        {
            // <keyCode * 3 + status>
            mouseEvent.buttons.reset(i * 3 + static_cast<int>(InputStatus::PRESSED));
            mouseEvent.buttons.reset(i * 3 + static_cast<int>(InputStatus::RELEASED));
        }

        // We want to recheck if the mouse is moving each frame
        mouseEvent.moving = false;

        // Drawing to window

        window.clear(sf::Color::Black);

        // board border
        sf::RectangleShape border{};
        border.setFillColor(sf::Color{127, 127, 127});
        border.setSize({515, 515});
        border.setPosition({0, 0});
        window.draw(border);

        board.tick(window, events);

        woodButton.tick(window);
        stoneButton.tick(window);
        plantButton.tick(window);
        fireButton.tick(window);
        waterButton.tick(window);

        elementSelect.tick(window);
        woodLabel.tick(window);
        stoneLabel.tick(window);
        plantLabel.tick(window);
        fireLabel.tick(window);
        waterLabel.tick(window);

        board.resetBoardState();

        window.display();
    }

    return 0;
}
