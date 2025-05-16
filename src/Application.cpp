#include "Application.hpp"

#include "BoardDisplay.hpp"
#include "Config.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace Powder;

Application::Application()
{
    this->window = new sf::RenderWindow{
        sf::VideoMode{Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT},
        Config::WINDOW_TITLE, sf::Style::Default
    };

    this->window->setFramerateLimit(Config::FRAMERATE_LIMIT);
    this->board = new BoardDisplay{Config::BOARD_WIDTH, Config::BOARD_HEIGHT};
}

Application::~Application()
{
    delete this->window;
    delete this->board;
}

void Application::start()
{
    while (this->window->isOpen())
    {
        this->tick();
    }
}
void Application::tick()
{
    sf::Event systemEvent;

    while (this->window->pollEvent(systemEvent))
    {
        // General application events
        switch (systemEvent.type)
        {
            case sf::Event::Closed:
            {
                this->window->close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (systemEvent.key.code == sf::Keyboard::Escape)
                {
                    this->window->close();
                }

                break;
            }
            default: break;
        }

        this->board->handleEvent(systemEvent);
    }

    this->board->tick();

    this->window->clear(Config::WINDOW_CLEAR_COLOR);

    this->board->render(this->window);
    this->window->display();
}
