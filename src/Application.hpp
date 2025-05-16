#ifndef POWDER_APPLICATION
#define POWDER_APPLICATION

#include "BoardDisplay.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace Powder
{

struct Application
{
    Application();
    ~Application();

    void start();

  private:
    sf::RenderWindow* window;
    BoardDisplay* board;

    void tick();
};

} // namespace Powder

#endif // POWDER_APPLICATION
