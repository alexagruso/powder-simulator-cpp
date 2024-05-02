#include "InputEvent.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace Powder;

InputEvent::InputEvent() {}

InputEvent* InputEvent::clone()
{
    InputEvent* clone = new InputEvent{};

    clone->keys = this->keys;
    clone->buttons = this->buttons;
    clone->mousePosition = this->mousePosition;

    return clone;
}

bool InputEvent::queryKey(sf::Keyboard::Key key, InputStatus status) const
{
    if (status == InputStatus::IDLE)
    {
        return !this->keys.test(key * 3 + static_cast<int>(InputStatus::HELD));
    }

    return this->keys.test(key * 3 + static_cast<int>(status));
}

bool InputEvent::queryMouseButton(sf::Mouse::Button button, InputStatus status) const
{
    if (status == InputStatus::IDLE)
    {
        return !this->buttons.test(button * 3 + static_cast<int>(InputStatus::HELD));
    }

    return this->buttons.test(button * 3 + static_cast<int>(status));
}

bool InputEvent::getMouseIsMoving() const
{
    return this->mouseIsMoving;
}

void InputEvent::setMouseIsMoving(bool status)
{
    this->mouseIsMoving = status;
}

sf::Vector2i InputEvent::getMousePosition() const
{
    return this->mousePosition;
}

void InputEvent::setMousePosition(sf::Vector2i mousePosition)
{
    this->mousePosition = mousePosition;
}

void InputEvent::keySet(sf::Keyboard::Key key, InputStatus inputStatus)
{
    this->keys.set(static_cast<int>(key) * 3 + static_cast<int>(inputStatus));
}

void InputEvent::keyReset(sf::Keyboard::Key key, InputStatus inputStatus)
{
    this->keys.reset(static_cast<int>(key) * 3 + static_cast<int>(inputStatus));
}

void InputEvent::mouseButtonSet(sf::Mouse::Button mouseButton, InputStatus inputStatus)
{
    this->buttons.set(static_cast<int>(mouseButton) * 3 + static_cast<int>(inputStatus));
}

void InputEvent::mouseButtonReset(sf::Mouse::Button mouseButton, InputStatus inputStatus)
{
    this->buttons.reset(static_cast<int>(mouseButton) * 3 + static_cast<int>(inputStatus));
}
