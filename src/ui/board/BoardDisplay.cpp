#include "BoardDisplay.hpp"

#include "application/events/ChangeActiveElementEvent.hpp"
#include "application/events/Event.hpp"
#include "application/events/InputEvent.hpp"
#include "application/events/ParticleCreationEvent.hpp"
#include "application/events/ParticleDeletionEvent.hpp"
#include "application/events/ParticleSwapEvent.hpp"
#include "config/Config.hpp"
#include "physics/Element.hpp"
#include "physics/Particle.hpp"
#include "util/documentation.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstdlib>
#include <optional>
#include <random>
#include <sys/types.h>
#include <vector>

using namespace Powder::UI;

BoardDisplay::BoardDisplay(sf::Vector2u dimensions, Physics::Element* initialActiveElement)
    : activeElement{initialActiveElement}, initialActiveElement{initialActiveElement}, particles{dimensions}
{
    std::vector<bool> emptyBoolRow(dimensions.x, false);
    this->particleReservations = std::vector<std::vector<bool>>{dimensions.y, emptyBoolRow};
    this->brush = std::vector<std::vector<bool>>{dimensions.y, emptyBoolRow};

    //  TODO: properly seed this
    this->randomEngine = std::mt19937{123};
}

BoardDisplay::~BoardDisplay()
{
    delete this->initialActiveElement;
}

std::vector<Powder::Event*> BoardDisplay::handleEvent(Event* event)
{
    std::vector<Powder::Event*> newEvents{};

    if (auto checkEvent = Event::isOfType<InputEvent>(event))
    {
        auto input = checkEvent.value();

        if (auto checkPosition = this->mouseToBoardPosition(input->getMousePosition()))
        {
            auto position = checkPosition.value();

            for (int brushX = -static_cast<int>(Config::BRUSH_RADIUS); brushX <= static_cast<int>(Config::BRUSH_RADIUS);
                 brushX++)
            {
                for (int brushY = -static_cast<int>(Config::BRUSH_RADIUS);
                     brushY <= static_cast<int>(Config::BRUSH_RADIUS); brushY++)
                {
                    if (isValidBoardPosition(
                            {static_cast<int>(position.x) + brushX, static_cast<int>(position.y) + brushY}))
                    {
                        this->brush.at(position.y + brushY).at(position.x + brushX) = true;
                    }
                }
            }
        }

        if (input->queryMouseButton(sf::Mouse::Left, InputStatus::HELD))
        {
            if (auto checkPosition = this->mouseToBoardPosition(input->getMousePosition()))
            {
                auto position = checkPosition.value();

                for (int brushX = -static_cast<int>(Config::BRUSH_RADIUS);
                     brushX <= static_cast<int>(Config::BRUSH_RADIUS); brushX++)
                {
                    for (int brushY = -static_cast<int>(Config::BRUSH_RADIUS);
                         brushY <= static_cast<int>(Config::BRUSH_RADIUS); brushY++)
                    {
                        if (isValidBoardPosition(
                                {static_cast<int>(position.x) + brushX, static_cast<int>(position.y) + brushY}))
                        {
                            newEvents.push_back(new ParticleCreationEvent{
                                {position.x + brushX, position.y + brushY},
                                this->activeElement
                            });
                        }
                    }
                }
            }
        }
    }
    else if (auto checkEvent = Event::isOfType<ChangeActiveElementEvent>(event))
    {
        this->activeElement = checkEvent.value()->element;
    }
    else if (auto checkEvent = Event::isOfType<ParticleCreationEvent>(event))
    {
        auto particleCreation = checkEvent.value();

        if (isValidBoardPosition(
                {static_cast<int>(particleCreation->position.x), static_cast<int>(particleCreation->position.y)}))
        {
            this->particles.set(particleCreation->position, Physics::Particle{particleCreation->element});
        }
    }
    else if (auto checkEvent = Event::isOfType<ParticleSwapEvent>(event))
    {
        auto particleSwap = checkEvent.value();

        if (isValidBoardPosition(
                {static_cast<int>(particleSwap->origin.x), static_cast<int>(particleSwap->origin.y)}) &&
            isValidBoardPosition({static_cast<int>(particleSwap->target.x), static_cast<int>(particleSwap->target.y)}))
        {
            if (!this->particles.at(particleSwap->target))
            {
                this->particles.set(particleSwap->target,
                                    Physics::Particle{this->particles.at(particleSwap->origin).value().element});
                this->particles.reset(particleSwap->origin);
            }
            else
            {
                Physics::Particle temp = this->particles.at(particleSwap->target).value();
                this->particles.set(particleSwap->target, this->particles.at(particleSwap->origin).value());
                this->particles.set(particleSwap->origin, temp);
            }
        }
    }
    else if (auto checkEvent = Event::isOfType<ParticleDeletionEvent>(event))
    {
        auto particleDeletion = checkEvent.value();
        this->particles.reset(particleDeletion->position);
    }

    return newEvents;
}

std::vector<Powder::Event*> BoardDisplay::tick()
{
    std::vector<Powder::Event*> newEvents{};

    for (uint row = 0; row < this->particles.dimensions.y; row++)
    {
        for (uint column = 0; column < this->particles.dimensions.x; column++)
        {
            if (auto checkParticle = this->particles.at({column, row}))
            {
                if (auto checkFire = Physics::Element::isOfType<Physics::Fire>(checkParticle.value().element))
                {
                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}},
                            checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }
                }
                else if (auto checkWater = Physics::Element::isOfType<Physics::Stone>(checkParticle.value().element))
                {
                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{0, 1}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }

                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{1, 1}, {-1, 1}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }
                }
                else if (auto checkWater = Physics::Element::isOfType<Physics::Water>(checkParticle.value().element))
                {
                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{0, 1}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }

                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{1, 1}, {-1, 1}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }

                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{0, 0}, {1, 0}, {-1, 0}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }
                }
                else if (auto checkOil = Physics::Element::isOfType<Physics::Oil>(checkParticle.value().element))
                {
                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{0, 1}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }

                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{1, 1}, {-1, 1}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }

                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{0, 0}, {1, 0}, {-1, 0}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }
                }
                else if (auto checkAcid = Physics::Element::isOfType<Physics::Acid>(checkParticle.value().element))
                {
                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{0, 1}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }

                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{1, 1}, {-1, 1}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }

                    if (auto checkEvents = attemptDirections(
                            {
                                column, row
                    },
                            {{0, 0}, {1, 0}, {-1, 0}}, checkParticle.value().element))
                    {
                        newEvents.insert(newEvents.end(), checkEvents.value().begin(), checkEvents.value().end());
                        continue;
                    }
                }
            }
        }
    }

    for (uint row = 0; row < this->particles.dimensions.y; row++)
    {
        for (uint column = 0; column < this->particles.dimensions.x; column++)
        {
            this->particleReservations.at(column).at(row) = false;
        }
    }

    return newEvents;
}

void BoardDisplay::render(sf::RenderWindow* window)
{
    sf::RectangleShape border{
        {static_cast<float>(this->particles.dimensions.x * Config::PARTICLE_PIXEL_SIZE + Config::BORDER_WIDTH),
         static_cast<float>(this->particles.dimensions.y * Config::PARTICLE_PIXEL_SIZE + Config::BORDER_WIDTH)}
    };

    border.setFillColor(sf::Color::White);
    window->draw(border);

    for (uint row = 0; row < this->particles.dimensions.y; row++)
    {
        for (uint column = 0; column < this->particles.dimensions.x; column++)
        {
            sf::RectangleShape particlePixel{
                {static_cast<float>(Config::PARTICLE_PIXEL_SIZE), static_cast<float>(Config::PARTICLE_PIXEL_SIZE)}
            };

            particlePixel.setPosition({static_cast<float>(column * Config::PARTICLE_PIXEL_SIZE),
                                       static_cast<float>(row * Config::PARTICLE_PIXEL_SIZE)});

            if (this->brush.at(row).at(column))
            {
                particlePixel.setFillColor(Config::BRUSH_COLOR);
                this->brush.at(row).at(column) = false;
            }
            else if (auto checkParticle = this->particles.at({column, row}))
            {
                particlePixel.setFillColor(checkParticle.value().element->fillColor());
            }
            else
            {
                particlePixel.setFillColor(Config::VOID_COLOR);
            }

            window->draw(particlePixel);
        }
    }
}

bool BoardDisplay::isValidBoardPosition(sf::Vector2i boardPosition) const
{
    return boardPosition.x >= 0 && boardPosition.x < static_cast<int>(this->particles.dimensions.x) &&
           boardPosition.y >= 0 && boardPosition.y < static_cast<int>(this->particles.dimensions.y);
}

std::optional<sf::Vector2u> BoardDisplay::mouseToBoardPosition(sf::Vector2i mousePosition) const
{
    int xPosition = mousePosition.x / Powder::Config::PARTICLE_PIXEL_SIZE;
    int yPosition = mousePosition.y / Powder::Config::PARTICLE_PIXEL_SIZE;

    if (this->isValidBoardPosition({xPosition, yPosition}))
    {
        return {
            {static_cast<uint>(xPosition), static_cast<uint>(yPosition)}
        };
    }

    return std::nullopt;
}

bool BoardDisplay::canSwap(sf::Vector2u origin, sf::Vector2i target) const
{
    if (this->isValidBoardPosition(target))
    {
        if (this->particles.at({static_cast<uint>(target.x), static_cast<uint>(target.y)}) == std::nullopt &&
            !this->particleReservations.at(target.y).at(target.x))
        {
            return true;
        }
        else
        {
            uint originWeight;
            uint targetWeight;

            if (auto checkOrigin = this->particles.at(origin))
            {
                originWeight = checkOrigin.value().element->staticWeight();
            }
            else
            {
                return false;
            }

            if (auto checkTarget = this->particles.at({static_cast<uint>(target.x), static_cast<uint>(target.y)}))
            {
                targetWeight = checkTarget.value().element->staticWeight();
            }
            else
            {
                return false;
            }

            return originWeight > targetWeight;
        }
    }

    return false;
}

std::optional<std::vector<Powder::Event*>>
BoardDisplay::attemptDirections(sf::Vector2u origin, std::vector<sf::Vector2i> directions, Physics::Element* element)
{
    UNUSED(element)

    std::vector<Powder::Event*> newEvents{};
    std::vector<sf::Vector2u> movementCandidates{};

    for (const sf::Vector2i& direction : directions)
    {
        if (this->canSwap(origin, {static_cast<int>(origin.x) + direction.x, static_cast<int>(origin.y) + direction.y}))
        {
            movementCandidates.push_back(
                {static_cast<uint>(origin.x + direction.x), static_cast<uint>(origin.y + direction.y)});
        }
    }

    int candidateCount = movementCandidates.size();

    if (movementCandidates.size() > 0)
    {
        std::uniform_int_distribution<int> direction{0, candidateCount - 1};
        int result = direction(this->randomEngine);

        newEvents.push_back(new ParticleSwapEvent{origin, movementCandidates.at(result)});
        // newEvents.push_back(new ParticleDeletionEvent{origin});
        // newEvents.push_back(new ParticleCreationEvent{movementCandidates.at(result), element});
        this->particleReservations.at(movementCandidates.at(result).y).at(movementCandidates.at(result).x) = true;

        return newEvents;
    }

    return std::nullopt;
}
