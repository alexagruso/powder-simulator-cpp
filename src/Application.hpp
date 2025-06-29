#ifndef POWDER_APPLICATION
#define POWDER_APPLICATION

#include "BoardDisplay.hpp"
#include "ConfigManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace Powder
{

struct Application
{
    Application(const std::string& configFilePath = "config.txt");

    ~Application();

    void start();

  private:
    ConfigManager config;
    sf::RenderWindow* window;
    BoardDisplay* board;

    void tick();
};

} // namespace Powder

#endif // POWDER_APPLICATION
