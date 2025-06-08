#ifndef POWDER_APPLICATION
#define POWDER_APPLICATION

#include "BoardDisplay.hpp"
#include "ConfigManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @file Application.hpp
 * @brief Main application class for the Powder Simulator.
 *
 * This file defines the Application struct which manages the overall
 * simulation, including configuration, window management, and the game loop.
 */

/// General namespace for containing custom application code
namespace Powder
{

/**
 * @brief Main application class that orchestrates the Powder Simulator.
 *
 * The Application manages the configuration, creates and maintains the
 * rendering window, and handles the main simulation loop.
 */
struct Application
{
    /**
     * @brief Constructs the Application with optional configuration file.
     *
     * @param configFilePath Path to the configuration file (default: "config.txt")
     */
    Application(const std::string& configFilePath = "config.txt");

    /**
     * @brief Destructor that cleans up application resources.
     */
    ~Application();

    /**
     * @brief Starts the main application loop.
     */
    void start();

  private:
    ConfigManager config;     ///< Configuration manager instance
    sf::RenderWindow* window; ///< Pointer to the SFML rendering window
    BoardDisplay* board;      ///< Pointer to the board display manager

    /**
     * @brief Performs a single tick/update of the application state.
     */
    void tick();
};

} // namespace Powder

#endif // POWDER_APPLICATION
