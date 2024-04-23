#ifndef POWDER_EVENT
#define POWDER_EVENT

#include "physics/Element.hpp"
#include "physics/Particle.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <bitset>
#include <optional>

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
    virtual ~Event() {} // This forces the type to be considered polymorphic

    // Must be implemented in header
    template <typename EventType>
    static std::optional<EventType*> isOfType(Event* event)
    {
        EventType* result = dynamic_cast<EventType*>(event);

        if (result != nullptr)
        {
            return result;
        }

        return std::nullopt;
    }

    // Default priority for all events, higher value means higher priority
    static const uint priority = 0;
};

//  TODO: implement comparator
struct EventComparator
{
};

// This event will trigger the application to close
struct ApplicationExitEvent : Event
{
};

struct ChangeActiveElementEvent : Event
{
    ChangeActiveElementEvent(Physics::Element* element) : element{element} {}

    Physics::Element* element;
};

//  TODO: move to separate file
struct InputEvent : Event
{
    std::bitset<sf::Keyboard::KeyCount * 3> keys;

    bool mouseIsMoving;
    sf::Vector2i mousePosition;
    std::bitset<sf::Mouse::ButtonCount * 3> buttons;

    bool queryKey(sf::Keyboard::Key key, InputStatus status) const;
    bool queryMouseButton(sf::Mouse::Button mouseButton, InputStatus status) const;

    //  TODO: find a better name for this
    InputEvent* cloneIntoNew();
};

// struct PhysicsUpdateEvent : Event
// {
//     // static const uint priority = 10;
// };
//
// struct ParticleCreationEvent : Event
// {
//     ParticleCreationEvent(sf::Vector2u position, Physics::Particle particle) : position{position}, particle{particle}
//     {}
//
//     sf::Vector2u position;
//     Physics::Particle particle;
// };
//
// struct ParticleDeletionEvent : Event
// {
//     ParticleDeletionEvent(sf::Vector2u position) : position{position} {}
//
//     sf::Vector2u position;
// };

} // namespace Powder

#endif // POWDER_EVENT
