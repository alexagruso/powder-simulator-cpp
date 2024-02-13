#include "event.hpp"

#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>
#include <stack>

using namespace ps;

int main()
{
    sf::Window window(sf::VideoMode(800, 600), "Hello, World!", sf::Style::Default);

    std::stack<sys::Event*> events;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                sys::KeyboardEvent keyEvent{
                    event.key.code,
                    true,
                    true,
                };

                sys::Event* newEvent = new sys::Event(keyEvent);

                events.push(newEvent);
            }
        }

        while (!events.empty())
        {
            events.top()->perform("Hello, World!");
            events.pop();
        }
    }

    return 0;
}