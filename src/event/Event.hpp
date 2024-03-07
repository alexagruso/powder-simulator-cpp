#ifndef EVENT
#define EVENT

#include "physics/Particle.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <bitset>
#include <variant>

namespace Powder
{

// Enum classes enforce type checking
enum class InputStatus
{
    ACTIVE,
    PRESSED,
    RELEASED,
    IDLE,
};

// Empty event for closing the application, useful for signaling events that never change
struct ApplicationExitEvent
{
};

struct ChangeActiveElementEvent
{
    Physics::Element element;
};

// std::bitset holds the flags for each key, more efficient than using a bool array
// Each key has four flags, PRESSED, ACTIVE, RELEASED, and IDLE
struct KeyboardEvent
{
    std::bitset<sf::Keyboard::KeyCount * 3> keys;

    bool query(sf::Keyboard::Key key, InputStatus status) const;
};

// std::bitset is used similarly here
// Each button also has the same flags as each keys
struct MouseEvent
{
    bool moving;
    sf::Vector2i position;
    std::bitset<sf::Mouse::ButtonCount * 3> buttons;

    bool query(sf::Mouse::Button button, InputStatus status) const;
};

//! Events will be defined as structs, maybe a general interface will be made but
//! for now this will be fine.
using Event = std::variant<ApplicationExitEvent, ChangeActiveElementEvent, KeyboardEvent, MouseEvent>;

} // namespace Powder

#endif // EVENT