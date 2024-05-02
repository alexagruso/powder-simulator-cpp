
#ifndef POWDER_INPUT_EVENT
#define POWDER_INPUT_EVENT

#include "application/events/Event.hpp"

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

struct InputEvent : Event
{
    InputEvent();

    InputEvent* clone();

    bool queryKey(sf::Keyboard::Key key, InputStatus status) const;
    bool queryMouseButton(sf::Mouse::Button mouseButton, InputStatus status) const;

    bool getMouseIsMoving() const;
    void setMouseIsMoving(bool status);

    sf::Vector2i getMousePosition() const;
    void setMousePosition(sf::Vector2i mousePosition);

    void keySet(sf::Keyboard::Key key, InputStatus inputStatus);
    void keyReset(sf::Keyboard::Key key, InputStatus inputStatus);
    void mouseButtonSet(sf::Mouse::Button mouseButton, InputStatus inputStatus);
    void mouseButtonReset(sf::Mouse::Button mouseButton, InputStatus inputStatus);

  private:
    bool mouseIsMoving;
    sf::Vector2i mousePosition;

    std::bitset<sf::Keyboard::KeyCount * 3> keys;
    std::bitset<sf::Mouse::ButtonCount * 3> buttons;
};

} // namespace Powder

#endif // POWDER_INPUT_EVENT
