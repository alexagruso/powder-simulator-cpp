#ifndef WINDOW
#define WINDOW

#include "eventHandler.hpp"

#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

class Window : protected EventHandler
{
  private:
    sf::Window* window;
    sf::VideoMode videoMode;

  public:
    Window(int width, int height);

    sf::VideoMode getVideoMode() const;

    void setActive();
    bool isActive() const;
};

#endif // WINDOW