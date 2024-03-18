#include "Board.hpp"

#include "event/Event.hpp"
#include "physics/Element.hpp"
#include "physics/Particle.hpp"
#include "util/Overloaded.hpp"

#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <optional>
#include <variant>

using namespace Powder;

const unsigned int PARTICLE_SIZE = 5;

Board::Board(sf::Vector2u dimensions) : dimensions{dimensions}
{
    this->particles.resize(dimensions.y);

    for (int y = 0; y < this->dimensions.y; y++)
    {
        this->particles.at(y).resize(dimensions.x);
    }

    for (int y = 0; y < this->dimensions.y; y++)
    {
        for (int x = 0; x < this->dimensions.x; x++)
        {
            // this->at({x, y}) = std::nullopt;
        }
    }
}

sf::Vector2u Board::mouseToBoardPosition(sf::Vector2i mousePosition)
{
    return {mousePosition.x / PARTICLE_SIZE, mousePosition.y / PARTICLE_SIZE};
}

void Board::setActiveElement(Physics::Element element)
{
    this->activeElement = element;
}

const OptionalParticle Board::at(sf::Vector2i position) const
{
    return this->particles.at(position.y).at(position.x);
}

void Board::set(sf::Vector2i position, Physics::Element element)
{
    this->particles.at(position.y).at(position.x) = Physics::Particle{element};
}

void Board::handleEvent(const Event& event)
{
    using namespace Powder::Physics;
    using namespace Powder::Util;

    std::visit(
        Overloaded{
            [this](const MouseEvent& event)
            {
                sf::Vector2u position = this->mouseToBoardPosition(event.position);

                if (event.query(sf::Mouse::Left, InputStatus::ACTIVE))
                {
                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            if (position.x + i >= this->dimensions.x || position.x + i < 0 ||
                                position.y + j >= this->dimensions.y || position.y + j < 0)
                            {
                                continue;
                            }

                            this->particles.at(position.y + j).at(position.x + i) = Particle{this->activeElement};
                        }
                    }
                }
            },
            [](auto _) {},
        },
        event);
}

void Board::tick(sf::RenderWindow& window)
{
    using namespace Powder::Physics;

    sf::RectangleShape particleRect;
    particleRect.setSize({PARTICLE_SIZE, PARTICLE_SIZE});

    for (int y = 0; y < this->dimensions.y; y++)
    {
        for (int x = 0; x < this->dimensions.x; x++)
        {
            std::optional<Particle> currentParticle = this->particles.at(y).at(x);

            particleRect.setPosition({x * static_cast<float>(PARTICLE_SIZE), y * static_cast<float>(PARTICLE_SIZE)});

            if (currentParticle == std::nullopt)
            {
                particleRect.setFillColor(sf::Color::Black);
            }
            else
            {
                using namespace Powder::Util;

                std::visit(Overloaded{[&particleRect](const auto& element)
                                      {
                                          // HACK: fillColor exists on all ElementVariant variants
                                          particleRect.setFillColor(element.fillColor);
                                      }},
                           currentParticle->element);
            }

            window.draw(particleRect);
        }
    }
}
