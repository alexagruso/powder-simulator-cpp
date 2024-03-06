#ifndef EVENT
#define EVENT

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <stack>
#include <variant>

namespace Powder
{

struct KeyboardEvent
{
    sf::Keyboard::Key key;
};

struct MouseEvent
{
    int x;
    int y;
    sf::Mouse::Button button;
};

using Event = std::variant<KeyboardEvent, MouseEvent>;

} // namespace Powder

#endif // EVENT