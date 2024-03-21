#include "Board.hpp"

#include "config/Config.hpp"
#include "event/Event.hpp"
#include "physics/Element.hpp"
#include "physics/Particle.hpp"
#include "util/Overloaded.hpp"

#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <chrono>
#include <optional>
#include <random>
#include <stack>
#include <variant>
#include <vector>

using namespace Powder;

const unsigned int PARTICLE_SIZE = 5;

Board::Board(sf::Vector2u dimensions) : dimensions{dimensions}
{
    this->particles.resize(dimensions.y);
    this->particleCreations.resize(dimensions.y);
    this->pointerPixels.resize(dimensions.y);

    for (int y = 0; y < this->dimensions.y; y++)
    {
        this->particles.at(y).resize(dimensions.x);
        this->particleCreations.at(y).resize(dimensions.x);
        this->pointerPixels.at(y).resize(dimensions.x);
    }

    for (int y = 0; y < this->dimensions.y; y++)
    {
        for (int x = 0; x < this->dimensions.x; x++)
        {
            this->set({x, y}, std::nullopt);
            this->particleCreations.at(y).at(x) = false;
            this->pointerPixels.at(y).at(x) = false;
        }
    }

    this->randomEngine = std::mt19937{
        static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())};
}

sf::Vector2i Board::mouseToBoardPosition(sf::Vector2i mousePosition)
{
    return {mousePosition.x / static_cast<int>(PARTICLE_SIZE), mousePosition.y / static_cast<int>(PARTICLE_SIZE)};
}

bool Board::canSwap(sf::Vector2i origin, sf::Vector2i offset)
{
    sf::Vector2i checkPosition = origin + offset;

    return this->contains(checkPosition) && this->at(checkPosition) == std::nullopt &&
           !this->particleCreations.at(checkPosition.y).at(checkPosition.x);
}

void Board::setActiveElement(Physics::Element element)
{
    this->activeElement = element;
}

const OptionalParticle Board::at(sf::Vector2i position) const
{
    return this->particles.at(position.y).at(position.x);
}

void Board::set(sf::Vector2i position, OptionalParticle particle)
{
    this->particles.at(position.y).at(position.x) = particle;
}

bool Board::contains(sf::Vector2i position) const
{
    return position.x >= 0 && position.x < this->dimensions.x && position.y >= 0 && position.y < this->dimensions.y;
}

void Board::resetBoardState()
{
    for (int y = 0; y < this->dimensions.y; y++)
    {
        for (int x = 0; x < this->dimensions.x; x++)
        {
            this->particleCreations.at(y).at(x) = false;
            this->pointerPixels.at(y).at(x) = false;
        }
    }
}

void Board::handleEvent(const Event& event, std::stack<Event>& events)
{
    using namespace Powder::Physics;
    using namespace Powder::Util;

    std::visit(
        Overloaded{
            [this, &events](const MouseEvent& event)
            {
                sf::Vector2i position = this->mouseToBoardPosition(event.position);

                for (int i = -Config::BRUSH_RADIUS; i <= Config::BRUSH_RADIUS; i++)
                {
                    for (int j = -Config::BRUSH_RADIUS; j <= Config::BRUSH_RADIUS; j++)
                    {
                        sf::Vector2i currentPosition = {position.x + i, position.y + j};

                        if (this->contains(currentPosition))
                        {
                            this->pointerPixels.at(currentPosition.y).at(currentPosition.x) = true;

                            if (event.query(sf::Mouse::Left, InputStatus::ACTIVE))
                            {
                                events.push(ParticleCreationEvent{currentPosition, this->activeElement});
                            }

                            if (event.query(sf::Mouse::Right, InputStatus::ACTIVE))
                            {
                                events.push(ParticleDeletionEvent{currentPosition});
                            }
                        }
                    }
                }
            },
            [this](const Powder::ChangeActiveElementEvent& event)
            {
                this->setActiveElement(event.element);
            },
            [this](const Powder::ParticleCreationEvent& event)
            {
                this->set(event.position, Particle{event.element});
            },
            [this](const Powder::ParticleDeletionEvent& event)
            {
                this->set(event.position, std::nullopt);
            },
            [](auto _) {},
        },
        event);
}

void Board::tick(sf::RenderWindow& window, std::stack<Event>& events)
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

            if (this->pointerPixels.at(y).at(x))
            {
                particleRect.setFillColor(sf::Color::White);
            }
            else if (currentParticle == std::nullopt)
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

    for (int y = 0; y < this->dimensions.y; y++)
    {
        for (int x = 0; x < this->dimensions.x; x++)
        {
            using namespace Powder::Util;

            if (this->at({x, y}) == std::nullopt)
            {
                continue;
            }

            Element currentElement = this->at({x, y})->element;

            std::visit(
                Overloaded{
                    [this, x, y, &events](const Stone& element)
                    {
                        if (y < this->dimensions.y - 1)
                        {
                            if (canSwap({x, y}, {0, 1}))
                            {
                                events.push(ParticleCreationEvent{
                                    {x, y + 1},
                                    element
                                });
                                this->particleCreations.at(y + 1).at(x) = true;

                                events.push(ParticleDeletionEvent{
                                    {x, y},
                                });
                            }
                            else
                            {
                                sf::Vector2i bottomLeft = {-1, 1};
                                sf::Vector2i bottomRight = {1, 1};

                                std::vector<sf::Vector2i> movementCandidates{};

                                if (canSwap({x, y}, bottomLeft))
                                {
                                    movementCandidates.push_back(bottomLeft);
                                }

                                if (canSwap({x, y}, bottomRight))
                                {
                                    movementCandidates.push_back(bottomRight);
                                }

                                if (movementCandidates.size() != 0)
                                {
                                    std::uniform_int_distribution<int> direction{
                                        0, static_cast<int>(movementCandidates.size() - 1)};

                                    sf::Vector2i swapPosition =
                                        sf::Vector2i{x, y} + movementCandidates.at(direction(this->randomEngine));

                                    events.push(ParticleCreationEvent{swapPosition, element});
                                    this->particleCreations.at(swapPosition.y).at(swapPosition.x) = true;

                                    events.push(ParticleDeletionEvent{
                                        {x, y},
                                    });
                                }
                            }
                        }
                    },
                    [this, x, y, &events](const Water& element)
                    {
                        if (canSwap({x, y}, {0, 1}))
                        {
                            events.push(ParticleCreationEvent{
                                {x, y + 1},
                                element
                            });
                            this->particleCreations.at(y + 1).at(x) = true;

                            events.push(ParticleDeletionEvent{
                                {x, y},
                            });

                            return;
                        }

                        sf::Vector2i bottomLeft = {-1, 1};
                        sf::Vector2i bottomRight = {1, 1};

                        std::vector<sf::Vector2i> movementCandidates{};

                        if (canSwap({x, y}, bottomLeft))
                        {
                            movementCandidates.push_back(bottomLeft);
                        }

                        if (canSwap({x, y}, bottomRight))
                        {
                            movementCandidates.push_back(bottomRight);
                        }

                        if (movementCandidates.size() != 0)
                        {
                            std::uniform_int_distribution<int> direction{
                                0, static_cast<int>(movementCandidates.size() - 1)};

                            sf::Vector2i swapPosition =
                                sf::Vector2i{x, y} + movementCandidates.at(direction(this->randomEngine));

                            events.push(ParticleCreationEvent{swapPosition, element});
                            this->particleCreations.at(swapPosition.y).at(swapPosition.x) = true;

                            events.push(ParticleDeletionEvent{
                                {x, y},
                            });

                            return;
                        }

                        sf::Vector2i left = {-1, 0};
                        sf::Vector2i right = {1, 0};

                        if (canSwap({x, y}, left))
                        {
                            movementCandidates.push_back(left);
                        }

                        if (canSwap({x, y}, right))
                        {
                            movementCandidates.push_back(right);
                        }

                        if (movementCandidates.size() != 0)
                        {
                            std::uniform_int_distribution<int> direction{
                                0, static_cast<int>(movementCandidates.size() - 1)};

                            int swapDirection = direction(this->randomEngine);

                            sf::Vector2i swapPosition = sf::Vector2i{x, y} + movementCandidates.at(swapDirection);

                            events.push(ParticleCreationEvent{swapPosition, element});
                            this->particleCreations.at(swapPosition.y).at(swapPosition.x) = true;

                            events.push(ParticleDeletionEvent{
                                {x, y},
                            });

                            return;
                        }
                    },
                    [](auto _) {},
                },
                currentElement);
        }
    }
}
