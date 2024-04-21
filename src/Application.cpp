#include "Application.hpp"

#include "config/Config.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

using namespace Powder;

Application::Application()
{
    this->window = new sf::RenderWindow{
        sf::VideoMode{Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT},
        Config::WINDOW_TITLE, sf::Style::Default
    };

    this->window->setFramerateLimit(Config::FRAMERATE_LIMIT);

    this->events = new std::stack<Event*>{};
}

Application::~Application()
{
    delete this->window;
    delete this->events;
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
    InputEvent* input = new InputEvent{}; //  TODO: extract into input handler

    while (this->window->pollEvent(systemEvent))
    {
        switch (systemEvent.type)
        {
            case sf::Event::Closed:
            {
                this->events->push(new ApplicationExitEvent{});
                break;
            }
            //  TODO: put these cases in separate input handler
            case sf::Event::KeyPressed:
            {
                input->keys.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::PRESSED));
                input->keys.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::HELD));
                break;
            }
            case sf::Event::KeyReleased:
            {
                input->keys.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::RELEASED));
                input->keys.reset(systemEvent.key.code * 3 + static_cast<int>(InputStatus::HELD));
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                input->buttons.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::PRESSED));
                input->buttons.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::HELD));

                if (!input->mouseIsMoving)
                {
                    input->mousePosition = {systemEvent.mouseButton.x, systemEvent.mouseButton.y};
                }

                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                input->buttons.set(systemEvent.key.code * 3 + static_cast<int>(InputStatus::RELEASED));
                input->buttons.reset(systemEvent.key.code * 3 + static_cast<int>(InputStatus::HELD));

                if (!input->mouseIsMoving)
                {
                    input->mousePosition = {systemEvent.mouseButton.x, systemEvent.mouseButton.y};
                }

                break;
            }
            case sf::Event::MouseMoved:
            {
                input->mouseIsMoving = true;
                input->mousePosition = {systemEvent.mouseMove.x, systemEvent.mouseMove.y};
                break;
            }
            default: break;
        }
    }

    this->events->push(input);

    while (!this->events->empty())
    {
        Event* currentEvent = this->events->top();
        this->events->pop();

        if (Event::isOfType<ApplicationExitEvent>(currentEvent))
        {
            this->window->close();
        }
        else if (auto event = Event::isOfType<InputEvent>(currentEvent).value())
        {
            if (event->queryKey(sf::Keyboard::Escape, InputStatus::PRESSED))
            {
                this->window->close();
            }
        }

        delete currentEvent;
    }

    //  TODO: put this code in separate input handler
    // for (int i = 0; i < sf::Keyboard::KeyCount; i++)
    // {
    //     input.keys.reset(i * 3 + static_cast<int>(InputStatus::PRESSED));
    //     input.keys.reset(i * 3 + static_cast<int>(InputStatus::RELEASED));
    // }
    //
    // for (int i = 0; i < sf::Mouse::ButtonCount; i++)
    // {
    //     input.buttons.reset(i * 3 + static_cast<int>(InputStatus::PRESSED));
    //     input.buttons.reset(i * 3 + static_cast<int>(InputStatus::RELEASED));
    // }
    //
    // // We want to recheck if the mouse is moving each frame
    // input.mouseIsMoving = false;

    this->window->clear(Config::WINDOW_CLEAR_COLOR);
    this->window->display();
}
