#include "config.hpp"
#include "event.hpp"
#include "eventHandler.hpp"
#include "window.hpp"

#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>
#include <stack>

using namespace ps;

int main()
{
    Window* window = new Window(ps::config::WINDOW_WIDTH, ps::config::WINDOW_HEIGHT);

    // while (window.isOpen())
    // {
    //     sf::Event event;

    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //         {
    //             window.close();
    //         }
    //     }
    // }

    return 0;
}