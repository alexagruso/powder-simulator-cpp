#ifndef POWDER_APPLICATION
#define POWDER_APPLICATION

#include "application/InputManager.hpp"
#include "application/events/Event.hpp"
#include "ui/Entity.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <stack>
#include <vector>

namespace Powder
{

struct Application
{
    Application();
    ~Application();

    void start();

  private:
    sf::RenderWindow* window;
    InputManager inputManager;
    std::stack<Event*> events; //  TODO: make this a priority queue
    std::vector<UIEntity*> entities;

    void tick();

    bool exiting = false;
};

} // namespace Powder

#endif // POWDER_APPLICATIONkjkkkk
