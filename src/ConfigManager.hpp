#ifndef POWDER_CONFIG_MANAGER
#define POWDER_CONFIG_MANAGER

#include <SFML/Graphics/Color.hpp>

#include <string>

namespace Powder
{

struct ConfigManager
{
    ConfigManager(const std::string& configFilePath = "config.txt");

    uint getFramerateLimit() const;
    std::string getWindowTitle() const;
    sf::Color getWindowClearColor() const;
    sf::Color getVoidColor() const;
    sf::Color getPowderColor() const;
    uint getBoardWidth() const;
    uint getBoardHeight() const;
    uint getParticlePixelSize() const;
    uint getWindowWidth() const;
    uint getWindowHeight() const;

  private:
    static constexpr uint DEFAULT_FRAMERATE_LIMIT = 60;
    static const inline std::string DEFAULT_WINDOW_TITLE = "Powder Simulator";
    static const inline sf::Color DEFAULT_WINDOW_CLEAR_COLOR = sf::Color::Black;
    static const inline sf::Color DEFAULT_VOID_COLOR = sf::Color::Black;
    static const inline sf::Color DEFAULT_POWDER_COLOR = sf::Color::White;
    static constexpr uint DEFAULT_BOARD_WIDTH = 100;
    static constexpr uint DEFAULT_BOARD_HEIGHT = 100;
    static constexpr uint DEFAULT_PARTICLE_PIXEL_SIZE = 4;

    uint framerateLimit;
    std::string windowTitle;
    sf::Color windowClearColor;
    sf::Color voidColor;
    sf::Color powderColor;
    uint boardWidth;
    uint boardHeight;
    uint particlePixelSize;

    uint windowWidth;
    uint windowHeight;

    void loadConfigFile(const std::string& filePath);
    sf::Color parseColor(const std::string& colorStr);
    uint parseUint(const std::string& str, uint defaultValue);
};

} // namespace Powder

#endif // POWDER_CONFIG_MANAGER
