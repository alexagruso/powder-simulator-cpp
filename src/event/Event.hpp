#ifndef EVENT
#define EVENT

#include "physics/Element.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <bitset>

namespace Powder
{

// PRESSED:  input was pressed this frame
// HELD:     input is currently active
// RELEASED: input was released this frame
// IDLE:     input is not currently active
enum class InputStatus
{
    PRESSED,
    HELD,
    RELEASED,
    IDLE,
};

struct Event
{
    // Default priority for all events, higher value means higher priority
    static const uint priority = 0;

    template <typename EventType>
    static bool isOfType(const Event& event);

    virtual ~Event() {} // This forces the type to be considered polymorphic
};

// This event will trigger the application to close
struct ApplicationExitEvent : Event
{
};

struct ChangeActiveElementEvent : Event
{
    Physics::Element element;
};

struct InputEvent : Event
{
    std::bitset<sf::Keyboard::KeyCount * 3> keys;

    bool mouseIsMoving;
    sf::Vector2i mousePosition;
    std::bitset<sf::Mouse::ButtonCount * 3> buttons;

    bool queryKey(sf::Keyboard::Key key, InputStatus status) const;
    bool queryMouseButton(sf::Mouse::Button mouseButton, InputStatus status) const;
};

} // namespace Powder

#endif // EVENT
