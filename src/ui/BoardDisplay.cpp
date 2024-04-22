#include "BoardDisplay.hpp"

#include "application/Event.hpp"
#include "config/Config.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>

using namespace Powder;

BoardDisplay::BoardDisplay(sf::Vector2u dimensions) : dimensions{dimensions}, boardState{dimensions} {}

std::vector<Event*> BoardDisplay::handleEvent(Event* event)
{
    if (auto check = Event::isOfType<ChangeActiveElementEvent>(event))
    {
        auto event = check.value();
        this->boardState.setActiveElement(event->element);
    }
    else if (auto checkEvent = Event::isOfType<InputEvent>(event))
    {
        auto event = checkEvent.value();

        if (event->queryMouseButton(sf::Mouse::Left, InputStatus::PRESSED))
        {
            if (auto checkPosition = this->mouseToBoardPosition(event->mousePosition))
            {
            }
        }
    }

    return {};
}

void BoardDisplay::tick() {}

std::vector<sf::Drawable*> BoardDisplay::render()
{
    std::vector<sf::Drawable*> draws{};

    for (uint x = 0; x < this->dimensions.x; x++)
    {
        for (uint y = 0; y < this->dimensions.y; y++)
        {
            sf::RectangleShape* particlePixel = new sf::RectangleShape{
                {Config::PARTICLE_PIXEL_SIZE, Config::PARTICLE_PIXEL_SIZE}
            };

            particlePixel->setPosition(static_cast<float>(x * Config::PARTICLE_PIXEL_SIZE),
                                       static_cast<float>(y * Config::PARTICLE_PIXEL_SIZE));

            if (auto check = this->boardState.at({x, y}))
            {
                Physics::Particle particle = check.value();
                particlePixel->setFillColor(particle.element->fillColor());
            }
            else
            {
                particlePixel->setFillColor(Config::VOID_COLOR);
            }

            draws.push_back(particlePixel);
        }
    }

    return draws;
}

bool BoardDisplay::contains(sf::Vector2i mousePosition)
{
    //  TODO: generalize to any board position
    const bool containedOnXAxis =
        (mousePosition.x >= 0 && mousePosition.x <= this->dimensions.x * Config::PARTICLE_PIXEL_SIZE);
    const bool containedOnYAxis =
        (mousePosition.y >= 0 && mousePosition.y <= this->dimensions.y * Config::PARTICLE_PIXEL_SIZE);

    return containedOnXAxis && containedOnYAxis;
}

std::optional<sf::Vector2u> BoardDisplay::mouseToBoardPosition(sf::Vector2i mousePosition)
{
    if (this->contains(mousePosition))
    {
        return sf::Vector2u{mousePosition.x / Config::PARTICLE_PIXEL_SIZE,
                            mousePosition.y / Config::PARTICLE_PIXEL_SIZE};
    }

    return std::nullopt;
}
