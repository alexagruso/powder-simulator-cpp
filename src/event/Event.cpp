#include "Event.hpp"

#include <SFML/Window/Keyboard.hpp>

bool Powder::KeyboardEvent::query(sf::Keyboard::Key key, InputStatus status) const
{
    if (status == InputStatus::IDLE)
    {
        return ((this->keys >> key * 3).to_ulong() & 0b111) == 0;
    }

    return this->keys.test(key * 3 + static_cast<int>(status));
}

bool Powder::MouseEvent::query(sf::Mouse::Button button, InputStatus status) const
{
    if (status == InputStatus::IDLE)
    {
        return ((this->buttons >> button * 3).to_ulong() & 0b111) == 0;
    }

    return this->buttons.test(button * 3 + static_cast<int>(status));
}