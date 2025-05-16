#include "BoardDisplay.hpp"

#include "Config.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include <cassert>
#include <chrono>
#include <random>
#include <sys/types.h>

using namespace Powder;

BoardDisplay::BoardDisplay(uint xSize, uint ySize)
    : width{xSize}, height{ySize}, particles{xSize, ySize}, particleReservations{xSize, ySize}
{
    this->randomEngine = std::mt19937{
        static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())};
}

void BoardDisplay::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        this->isHeld = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        this->isHeld = false;
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        this->mouseX = event.mouseMove.x;
        this->mouseY = event.mouseMove.y;
    }
}

void BoardDisplay::tick()
{
    for (int row = this->particles.height - 1; row >= 0; row--)
    {
        for (int column = this->particles.width - 1; column >= 0; column--)
        {
            // Skip if current cell is empty
            if (!this->particles.at(column, row))
                continue;

            // Skip if current cell is on the bottom of the board
            if (static_cast<uint>(row) + 1 >= this->particles.height)
                continue;

            // Skip if the cell below is filled
            if (this->particles.at(column, row + 1))
                continue;

            this->particles.set(column, row, false);
            this->particles.set(column, row + 1, true);
        }
    }

    // Reset particle reservations
    for (uint row = 0; row < this->particles.height; row++)
    {
        for (uint column = 0; column < this->particles.width; column++)
        {
            this->particleReservations.set(column, row, false);
        }
    }

    // Handle new particles after physics
    if (!isHeld)
        return;

    if (auto boardPosition = this->particles.mouseToBoardPosition(mouseX, mouseY))
    {
        this->particles.set(boardPosition->first, boardPosition->second, true);
    }
}

void BoardDisplay::render(sf::RenderWindow* window)
{
    sf::RectangleShape particlePixel{
        {static_cast<float>(Config::PARTICLE_PIXEL_SIZE), static_cast<float>(Config::PARTICLE_PIXEL_SIZE)}
    };

    for (uint row = 0; row < this->particles.height; row++)
    {
        for (uint column = 0; column < this->particles.width; column++)
        {
            if (!this->particles.at(column, row))
                continue;

            particlePixel.setPosition({static_cast<float>(column * Config::PARTICLE_PIXEL_SIZE),
                                       static_cast<float>(row * Config::PARTICLE_PIXEL_SIZE)});
            particlePixel.setFillColor(Config::POWDER_COLOR);

            window->draw(particlePixel);
        }
    }
}
