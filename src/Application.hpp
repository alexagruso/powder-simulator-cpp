#ifndef POWDER_APPLICATION
#define POWDER_APPLICATION

#include "event/Event.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <stack>

namespace Powder
{

struct Application
{
    Application();
    ~Application();

    void start();

  private:
    sf::RenderWindow* window;
    std::stack<Event*>* events; //  TODO: make this a priority queue

    void tick();
};

} // namespace Powder

#endif // POWDER_APPLICATION
