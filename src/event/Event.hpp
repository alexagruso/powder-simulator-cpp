#ifndef EVENT
#define EVENT

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <bitset>
#include <variant>

namespace Powder
{

enum class InputStatus
{
    ACTIVE,
    PRESSED,
    RELEASED,
    IDLE,
};

struct ApplicationExitEvent
{
};

struct KeyboardEvent
{
    std::bitset<sf::Keyboard::KeyCount * 3> keys;

    bool query(sf::Keyboard::Key key, InputStatus status) const;
};

struct MouseEvent
{
    bool moving;
    sf::Vector2i position;
    std::bitset<sf::Mouse::ButtonCount * 3> buttons;

    bool query(sf::Mouse::Button button, InputStatus status) const;
};

using Event = std::variant<ApplicationExitEvent, KeyboardEvent, MouseEvent>;

} // namespace Powder

#endif // EVENT