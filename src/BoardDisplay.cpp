#include "BoardDisplay.hpp"

#include "Particle.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include <chrono>
#include <optional>
#include <random>
#include <sys/types.h>

using namespace Powder;

BoardDisplay::BoardDisplay(uint xSize, uint ySize, const ConfigManager& config)
    : config(config), width{xSize}, height{ySize}, particles{xSize, ySize}
{
    this->randomEngine = std::mt19937{
        static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())};
    this->leftRightDistribution = std::uniform_int_distribution<int>{0, 1};
    this->colorDistribution = std::uniform_int_distribution<int>{0, 255};
}

void BoardDisplay::handleEvent(std::optional<sf::Event> event)
{
    if (event->is<sf::Event::MouseButtonPressed>())
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            this->isLeftHeld = true;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            this->isRightHeld = true;
        }
    }
    else if (event->is<sf::Event::MouseButtonReleased>())
    {
        if (this->isLeftHeld && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            this->isLeftHeld = false;
        }

        if (this->isRightHeld && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            this->isRightHeld = false;
        }
    }
}

void BoardDisplay::tick(sf::RenderWindow* window)
{
    this->mouseX = sf::Mouse::getPosition(*window).x;
    this->mouseY = sf::Mouse::getPosition(*window).y;

    for (int row = this->particles.height - 1; row >= 0; row--)
    {
        for (int column = this->particles.width - 1; column >= 0; column--)
        {
            // Skip if current cell is on the bottom of the board
            if (static_cast<uint>(row) + 1 >= this->particles.height)
                continue;

            // Skip if current cell is empty
            OptParticle currentParticle = this->particles.at(column, row);
            if (!currentParticle)
                continue;

            // Try to fall directly down
            if (!this->particles.at(column, row + 1))
            {
                this->particles.set(column, row, std::nullopt);
                this->particles.set(column, row + 1, currentParticle);
                continue;
            }

            // 50/50 chance to go left or right
            bool goLeft = this->leftRightDistribution(this->randomEngine) == 0;

            // Try left diagonal first if goLeft is true, otherwise try right diagonal first
            int leftCol = column - 1;
            int rightCol = column + 1;

            // Check boundaries
            bool canFallLeft = leftCol >= 0 && !this->particles.at(leftCol, row + 1);
            bool canFallRight =
                rightCol < static_cast<int>(this->particles.width) && !this->particles.at(rightCol, row + 1);

            if (goLeft && canFallLeft)
            {
                this->particles.set(column, row, std::nullopt);
                this->particles.set(leftCol, row + 1, currentParticle);
            }
            else if (!goLeft && canFallRight)
            {
                this->particles.set(column, row, std::nullopt);
                this->particles.set(rightCol, row + 1, currentParticle);
            }
            else if (canFallLeft) // If preferred direction isn't available, try the other
            {
                this->particles.set(column, row, std::nullopt);
                this->particles.set(leftCol, row + 1, currentParticle);
            }
            else if (canFallRight)
            {
                this->particles.set(column, row, std::nullopt);
                this->particles.set(rightCol, row + 1, currentParticle);
            }
        }
    }

    // Handle new particles after physics
    if (auto boardPosition = this->mouseToBoardPosition(mouseX, mouseY))
    {
        if (this->isLeftHeld)
        {
            sf::Color randomColor = sf::Color{
                static_cast<uint8_t>(this->colorDistribution(this->randomEngine)),
                static_cast<uint8_t>(this->colorDistribution(this->randomEngine)),
                static_cast<uint8_t>(this->colorDistribution(this->randomEngine)),
            };
            OptParticle newParticle = Particle{randomColor};

            this->particles.set(boardPosition->first, boardPosition->second, newParticle);
        }
        else if (this->isRightHeld)
        {
            this->particles.set(boardPosition->first, boardPosition->second, std::nullopt);
        }
    }
}

void BoardDisplay::render(sf::RenderWindow* window)
{
    sf::RectangleShape particlePixel{
        {static_cast<float>(config.getParticlePixelSize()), static_cast<float>(config.getParticlePixelSize())}
    };

    for (uint row = 0; row < this->particles.height; row++)
    {
        for (uint column = 0; column < this->particles.width; column++)
        {
            OptParticle currentParticle = this->particles.at(column, row);
            if (!currentParticle)
                continue;

            particlePixel.setPosition({static_cast<float>(column * this->config.getParticlePixelSize()),
                                       static_cast<float>(row * this->config.getParticlePixelSize())});
            particlePixel.setFillColor(currentParticle->color);

            window->draw(particlePixel);
        }
    }
}

std::optional<std::pair<uint, uint>> BoardDisplay::mouseToBoardPosition(int mouseX, int mouseY) const
{
    int xPosition = mouseX / config.getParticlePixelSize();
    int yPosition = mouseY / config.getParticlePixelSize();

    if (this->particles.isValidBoardPosition(xPosition, yPosition))
    {
        return {
            {static_cast<uint>(xPosition), static_cast<uint>(yPosition)}
        };
    }

    return std::nullopt;
}
