#include "InputManager.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace Powder;

InputManager::InputManager()
{
    this->inputStatus = new InputEvent;
}

InputManager::~InputManager()
{
    delete this->inputStatus;
}

void InputManager::processKeyPress(sf::Keyboard::Key keyCode)
{
    this->inputStatus->keySet(keyCode, InputStatus::PRESSED);
    this->inputStatus->keySet(keyCode, InputStatus::HELD);
}

void InputManager::processKeyRelease(sf::Keyboard::Key keyCode)
{
    this->inputStatus->keySet(keyCode, InputStatus::RELEASED);
    this->inputStatus->keyReset(keyCode, InputStatus::HELD);
}

void InputManager::processMousePress(sf::Mouse::Button mouseButtonCode, sf::Vector2i mousePosition)
{
    this->inputStatus->mouseButtonSet(mouseButtonCode, InputStatus::PRESSED);
    this->inputStatus->mouseButtonSet(mouseButtonCode, InputStatus::HELD);

    if (!this->inputStatus->getMouseIsMoving())
    {
        this->inputStatus->setMousePosition(mousePosition);
    }
}

void InputManager::processMouseRelease(sf::Mouse::Button mouseButtonCode, sf::Vector2i mousePosition)
{
    this->inputStatus->mouseButtonSet(mouseButtonCode, InputStatus::RELEASED);
    this->inputStatus->mouseButtonReset(mouseButtonCode, InputStatus::HELD);

    if (!this->inputStatus->getMouseIsMoving())
    {
        this->inputStatus->setMousePosition(mousePosition);
    }
}

void InputManager::processMouseMovement(sf::Vector2i mousePosition)
{
    this->inputStatus->setMouseIsMoving(true);
    this->inputStatus->setMousePosition(mousePosition);
}

void InputManager::reset()
{
    for (int key = 0; key < sf::Keyboard::KeyCount; key++)
    {
        this->inputStatus->keyReset(static_cast<sf::Keyboard::Key>(key), InputStatus::PRESSED);
        this->inputStatus->keyReset(static_cast<sf::Keyboard::Key>(key), InputStatus::RELEASED);
    }

    for (int mouseButton = 0; mouseButton < sf::Mouse::ButtonCount; mouseButton++)
    {
        this->inputStatus->mouseButtonReset(static_cast<sf::Mouse::Button>(mouseButton), InputStatus::PRESSED);
        this->inputStatus->mouseButtonReset(static_cast<sf::Mouse::Button>(mouseButton), InputStatus::RELEASED);
    }

    this->inputStatus->setMouseIsMoving(false);
}
