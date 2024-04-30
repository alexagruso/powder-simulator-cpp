#include "BoardController.hpp"

#include "ui/board/BoardState.hpp"

#include <SFML/System/Vector2.hpp>

using namespace Powder::UI;

BoardController::BoardController(sf::Vector2u dimensions, Physics::Element* initialActiveElement)
    : dimensions{dimensions}, initialActiveElement{initialActiveElement}, boardState{dimensions}
{
    this->activeElement = this->initialActiveElement;

    //  HACK: for some reason boolean vectors don't allow uniform initialization
    std::vector<bool> emptyBools(dimensions.x, false);
    this->physicsEvents = PhysicsEvents{dimensions.y, emptyBools};
}

BoardController::~BoardController()
{
    delete this->initialActiveElement;
}

void BoardController::processPhysics()
{
    BoardState newState{this->boardState};

    for (uint x = 0; x < this->dimensions.x; x++)
    {
        for (uint y = 0; y < this->dimensions.y; y++)
        {
            if (auto check = this->boardState.at({x, y}))
            {
                using namespace Powder::Physics;

                //  TODO: make general particle physics handler
                //
                // Particle* currentParticle = check.value();

                if (this->boardState.isValidPosition({x, y + 1}) && !this->boardState.at({x, y + 1}) &&
                    !this->physicsEvents.at(y + 1).at(x))
                {
                    newState.swapFill({x, y}, {x, y + 1});
                    this->physicsEvents.at(y + 1).at(x) = true;
                }
                else if (this->boardState.isValidPosition({x + 1, y + 1}) && !this->boardState.at({x + 1, y + 1}) &&
                         !this->physicsEvents.at(y + 1).at(x + 1))
                {
                    newState.swapFill({x, y}, {x + 1, y + 1});
                    this->physicsEvents.at(y + 1).at(x + 1) = true;
                }
                else if (this->boardState.isValidPosition({x - 1, y + 1}) && !this->boardState.at({x - 1, y + 1}) &&
                         !this->physicsEvents.at(y + 1).at(x - 1))
                {
                    newState.swapFill({x, y}, {x - 1, y + 1});
                    this->physicsEvents.at(y + 1).at(x - 1) = true;
                }
            }
        }
    }

    this->boardState = BoardState{newState};

    // reset physics event states
    for (uint x = 0; x < this->dimensions.x; x++)
    {
        for (uint y = 0; y < this->dimensions.y; y++)
        {
            this->physicsEvents.at(y).at(x) = false;
        }
    }
}
