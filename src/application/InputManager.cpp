#include "InputManager.hpp"

#include "application/Event.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace Powder;

InputManager::InputManager()
{
    this->inputStatus = new InputEvent;
}

InputManager::~InputManager()
{
    //  TODO: rethink how this should work

    // ensures this->reset() does not cause a double free
    // if (this->inputStatus)
    // {
    //     delete this->inputStatus;
    // }
}

void InputManager::processKeyPress(sf::Keyboard::Key keyCode)
{
    this->inputStatus->keys.set(keyCode * 3 + static_cast<int>(InputStatus::PRESSED));
    this->inputStatus->keys.set(keyCode * 3 + static_cast<int>(InputStatus::HELD));
}

void InputManager::processKeyRelease(sf::Keyboard::Key keyCode)
{
    this->inputStatus->keys.set(keyCode * 3 + static_cast<int>(InputStatus::RELEASED));
    this->inputStatus->keys.reset(keyCode * 3 + static_cast<int>(InputStatus::HELD));
}

void InputManager::processMousePress(sf::Mouse::Button mouseButtonCode, sf::Vector2i mousePosition)
{
    this->inputStatus->buttons.set(mouseButtonCode * 3 + static_cast<int>(InputStatus::PRESSED));
    this->inputStatus->buttons.set(mouseButtonCode * 3 + static_cast<int>(InputStatus::HELD));

    if (!this->inputStatus->mouseIsMoving)
    {
        this->inputStatus->mousePosition = mousePosition;
    }
}

void InputManager::processMouseRelease(sf::Mouse::Button mouseButtonCode, sf::Vector2i mousePosition)
{
    this->inputStatus->buttons.set(mouseButtonCode * 3 + static_cast<int>(InputStatus::RELEASED));
    this->inputStatus->buttons.reset(mouseButtonCode * 3 + static_cast<int>(InputStatus::HELD));

    if (!this->inputStatus->mouseIsMoving)
    {
        this->inputStatus->mousePosition = mousePosition;
    }
}

void InputManager::processMouseMovement(sf::Vector2i mousePosition)
{
    this->inputStatus->mouseIsMoving = true;
    this->inputStatus->mousePosition = mousePosition;
}

void InputManager::reset()
{
    // old data has been moved by this point
    InputEvent* clone = this->inputStatus->cloneIntoNew();
    this->inputStatus = clone;

    for (int i = 0; i < sf::Keyboard::KeyCount; i++)
    {
        this->inputStatus->keys.reset(i * 3 + static_cast<int>(InputStatus::PRESSED));
        this->inputStatus->keys.reset(i * 3 + static_cast<int>(InputStatus::RELEASED));
    }

    for (int i = 0; i < sf::Mouse::ButtonCount; i++)
    {
        this->inputStatus->buttons.reset(i * 3 + static_cast<int>(InputStatus::PRESSED));
        this->inputStatus->buttons.reset(i * 3 + static_cast<int>(InputStatus::RELEASED));
    }

    this->inputStatus->mouseIsMoving = false;
}
