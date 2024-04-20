#include "Event.hpp"

using namespace Powder;

template <typename EventType>
bool Event::isOfType(const Event& event)
{
    return dynamic_cast<EventType*>(event) != nullptr;
}

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
    //
    if (status == InputStatus::IDLE)
    {
        return !this->buttons.test(button * 3 + static_cast<int>(InputStatus::HELD));
    }

    return this->buttons.test(button * 3 + static_cast<int>(status));
}
