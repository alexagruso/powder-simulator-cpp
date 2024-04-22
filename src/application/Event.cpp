#include "Event.hpp"

using namespace Powder;

//  TODO: put this in separate file
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

//  HACK: should find a better way to do this but it works for now
//  this essentially deep copies the data so that input can be tracked across multiple frames
InputEvent* InputEvent::cloneIntoNew()
{
    InputEvent* clone = new InputEvent{};

    clone->keys = this->keys;
    clone->buttons = this->buttons;
    clone->mousePosition = this->mousePosition;

    return clone;
}
