#ifndef POWDER_INPUT_MANAGER
#define POWDER_INPUT_MANAGER

#include "application/Event.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Powder
{

struct InputManager
{
    InputManager();
    ~InputManager();

    void processKeyPress(sf::Keyboard::Key keyCode);
    void processKeyRelease(sf::Keyboard::Key keyCode);
    void processMousePress(sf::Mouse::Button mouseButtonCode, sf::Vector2i mousePosition);
    void processMouseRelease(sf::Mouse::Button mouseButtonCode, sf::Vector2i mousePosition);
    void processMouseMovement(sf::Vector2i mousePosition);

    void reset();

    InputEvent* inputStatus;
};

} // namespace Powder

#endif // POWDER_INPUT_MANAGER
