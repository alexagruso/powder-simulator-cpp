#include "Application.hpp"

#include "application/Event.hpp"
#include "config/Config.hpp"
#include "physics/Element.hpp"
#include "ui/BoardDisplay.hpp"
#include "ui/ElementButton.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>

using namespace Powder;

Application::Application()
{
    this->window = new sf::RenderWindow{
        sf::VideoMode{Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT},
        Config::WINDOW_TITLE, sf::Style::Default
    };

    this->window->setFramerateLimit(Config::FRAMERATE_LIMIT);

    this->events = std::stack<Event*>{};

    EntityPositioning positioning;
    positioning.horizontal = HorizontalPositioning::LEFT;
    positioning.vertical = VerticalPositioning::TOP;

    //  TODO: this is temporary, make separate UI handler
    ElementButton* fireButton = new ElementButton{
        {50, 50},
        {300, 0},
        positioning, new Physics::Fire{}
    };

    ElementButton* plantButton = new ElementButton{
        {50, 50},
        {300, 50},
        positioning, new Physics::Plant{}
    };

    BoardDisplay* board = new BoardDisplay{
        {Config::BOARD_WIDTH, Config::BOARD_HEIGHT}
    };

    this->entities.push_back(fireButton);
    this->entities.push_back(plantButton);
    this->entities.push_back(board);
}

Application::~Application()
{
    delete this->window;

    for (Entity* entity : this->entities)
    {
        delete entity;
    }
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
        switch (systemEvent.type)
        {
            case sf::Event::Closed:
            {
                this->events.push(new ApplicationExitEvent{});
                break;
            }
            case sf::Event::KeyPressed:
            {
                this->inputManager.processKeyPress(systemEvent.key.code);
                break;
            }
            case sf::Event::KeyReleased:
            {
                this->inputManager.processKeyRelease(systemEvent.key.code);
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                this->inputManager.processMousePress(systemEvent.mouseButton.button,
                                                     {systemEvent.mouseButton.x, systemEvent.mouseButton.y});
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                this->inputManager.processMouseRelease(systemEvent.mouseButton.button,
                                                       {systemEvent.mouseButton.x, systemEvent.mouseButton.y});
                break;
            }
            case sf::Event::MouseMoved:
            {
                this->inputManager.processMouseMovement({systemEvent.mouseMove.x, systemEvent.mouseMove.y});
                break;
            }
            default: break;
        }
    }

    this->events.push(this->inputManager.inputStatus);

    // the old input event pointer is moved into the event stack, then deleted when the events are processed.
    // before this happens, the input manager copies into a new input event instance
    this->inputManager.reset();

    while (!this->events.empty())
    {
        Event* currentEvent = this->events.top();
        this->events.pop();

        // Global application events are handled first
        if (Event::isOfType<ApplicationExitEvent>(currentEvent))
        {
            this->window->close();
            this->exiting = true;
        }
        else if (auto check = Event::isOfType<InputEvent>(currentEvent))
        {
            auto event = check.value();

            if (event->queryKey(sf::Keyboard::Escape, InputStatus::PRESSED))
            {
                this->window->close();
                this->exiting = true;
            }
        }

        // Handle events for each entity
        for (Entity* entity : this->entities)
        {
            auto newEvents = entity->handleEvent(currentEvent);

            for (Event* event : newEvents)
            {
                this->events.push(event);
            }
        }

        delete currentEvent;
    }

    // compute logic for each entity
    for (Entity* entity : entities)
    {
        entity->tick();
    }

    this->window->clear(Config::WINDOW_CLEAR_COLOR);
    std::vector<sf::Drawable*> draws;

    // render all entities
    for (Entity* entity : entities)
    {
        auto entityDraws = entity->render();
        draws.insert(draws.end(), entityDraws.begin(), entityDraws.end());
    }

    for (auto draw : draws)
    {
        this->window->draw(*draw);
    }

    this->window->display();
}
