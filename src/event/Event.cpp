#include "Event.hpp"

#include <SFML/Window/Keyboard.hpp>

// Interface for querying key/button status without directly
// interacting with std::bitset instances
// TODO: combine these into a cleaner interface

bool Powder::KeyboardEvent::query(sf::Keyboard::Key key, InputStatus status) const
{
    if (status == InputStatus::IDLE)
    {
        return !this->keys.test(key * 3 + static_cast<int>(InputStatus::ACTIVE));
    }

    return this->keys.test(key * 3 + static_cast<int>(status));
}

bool Powder::MouseEvent::query(sf::Mouse::Button button, InputStatus status) const
{
    if (status == InputStatus::IDLE)
    {
        return !this->buttons.test(button * 3 + static_cast<int>(InputStatus::ACTIVE));
    }

    return this->buttons.test(button * 3 + static_cast<int>(status));
}