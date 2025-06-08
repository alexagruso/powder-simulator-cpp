#ifndef POWDER_CONFIG_MANAGER
#define POWDER_CONFIG_MANAGER

#include <SFML/Graphics/Color.hpp>

#include <string>

/**
 * @file ConfigManager.hpp
 * @brief Configuration management for the Powder Simulator.
 *
 * This file defines the ConfigManager class which handles loading and
 * providing access to application configuration settings.
 */

/// General namespace for containing custom application code
namespace Powder
{

/**
 * @brief Manages configuration settings for the Powder Simulator.
 *
 * The ConfigManager loads settings from a configuration file and provides
 * access to various application parameters like colors, sizes, and limits.
 */
class ConfigManager
{
  public:
    /**
     * @brief Constructs the ConfigManager with optional configuration file.
     *
     * @param configFilePath Path to the configuration file (default: "config.txt")
     */
    ConfigManager(const std::string& configFilePath = "config.txt");

    // Configuration getters
    /**
     * @brief Gets the configured framerate limit.
     * @return Framerate limit in frames per second
     */
    uint getFramerateLimit() const;

    /**
     * @brief Gets the configured window title.
     * @return Window title string
     */
    std::string getWindowTitle() const;

    /**
     * @brief Gets the color used for clearing the window.
     * @return SFML Color for window clearing
     */
    sf::Color getWindowClearColor() const;

    /**
     * @brief Gets the color representing void/empty space.
     * @return SFML Color for void
     */
    sf::Color getVoidColor() const;

    /**
     * @brief Gets the color used for powder particles.
     * @return SFML Color for powder
     */
    sf::Color getPowderColor() const;

    /**
     * @brief Gets the configured board width.
     * @return Board width in cells
     */
    uint getBoardWidth() const;

    /**
     * @brief Gets the configured board height.
     * @return Board height in cells
     */
    uint getBoardHeight() const;

    /**
     * @brief Gets the pixel size for each particle.
     * @return Particle size in pixels
     */
    uint getParticlePixelSize() const;

    /**
     * @brief Gets the calculated window width.
     * @return Window width in pixels
     */
    uint getWindowWidth() const;

    /**
     * @brief Gets the calculated window height.
     * @return Window height in pixels
     */
    uint getWindowHeight() const;

  private:
    // Default values
    static constexpr uint DEFAULT_FRAMERATE_LIMIT = 60;
    static const inline std::string DEFAULT_WINDOW_TITLE = "Powder Simulator";
    static const inline sf::Color DEFAULT_WINDOW_CLEAR_COLOR = sf::Color::Black;
    static const inline sf::Color DEFAULT_VOID_COLOR = sf::Color::Black;
    static const inline sf::Color DEFAULT_POWDER_COLOR = sf::Color::White;
    static constexpr uint DEFAULT_BOARD_WIDTH = 100;
    static constexpr uint DEFAULT_BOARD_HEIGHT = 100;
    static constexpr uint DEFAULT_PARTICLE_PIXEL_SIZE = 4;

    // Actual configuration values
    uint framerateLimit;        ///< Stored framerate limit
    std::string windowTitle;    ///< Stored window title
    sf::Color windowClearColor; ///< Stored window clear color
    sf::Color voidColor;        ///< Stored void color
    sf::Color powderColor;      ///< Stored powder color
    uint boardWidth;            ///< Stored board width
    uint boardHeight;           ///< Stored board height
    uint particlePixelSize;     ///< Stored particle pixel size

    // Derived values
    uint windowWidth;  ///< Calculated window width
    uint windowHeight; ///< Calculated window height

    /**
     * @brief Loads configuration from a file.
     *
     * @param filePath Path to the configuration file
     */
    void loadConfigFile(const std::string& filePath);

    /**
     * @brief Parses a color string into an SFML Color.
     *
     * @param colorStr String representation of the color
     * @return Parsed SFML Color
     */
    sf::Color parseColor(const std::string& colorStr);

    /**
     * @brief Parses a string to an unsigned integer with default fallback.
     *
     * @param str String to parse
     * @param defaultValue Default value if parsing fails
     * @return Parsed unsigned integer or default value
     */
    uint parseUint(const std::string& str, uint defaultValue);
};

} // namespace Powder

#endif // POWDER_CONFIG_MANAGER
