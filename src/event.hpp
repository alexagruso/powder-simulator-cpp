#ifndef EVENT
#define EVENT

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <string>
#include <variant>

namespace ps::sys
{

struct MovementEvent
{
    // source: pixel
};

struct KeyboardEvent
{
    sf::Keyboard::Key code;
    bool isPressed;
    bool isPressedThisFrame;
};

struct MouseEvent
{
    // mouse button, position
    sf::Mouse::Button code;
    int xPosition;
    int yPosition;
};

using EventType = std::variant<MovementEvent, KeyboardEvent, MouseEvent>;

class Event
{
  private:
    const EventType type;

  public:
    Event(EventType type) : type{type} {};

    EventType getType() const;

    void perform(std::string message);
};

} // namespace ps::sys

#endif // EVENT