#include "Application.hpp"

#include "BoardDisplay.hpp"
#include "ConfigManager.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace Powder;

Application::Application(const std::string& configFilePath) : config(configFilePath)
{
    this->window = new sf::RenderWindow{sf::VideoMode{{config.getWindowWidth(), config.getWindowHeight()}},
                                        config.getWindowTitle(), sf::Style::Default};

    this->window->setFramerateLimit(config.getFramerateLimit());
    this->board = new BoardDisplay{config.getBoardWidth(), config.getBoardHeight(), config};
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
    while (const std::optional systemEvent = this->window->pollEvent())
    {
        // General application events
        if (systemEvent->is<sf::Event::Closed>())
        {
            this->window->close();
            continue;
        }

        this->board->handleEvent(systemEvent);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        this->window->close();
    }

    this->board->tick(this->window);

    this->window->clear(config.getWindowClearColor());

    this->board->render(this->window);
    this->window->display();
}
