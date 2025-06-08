#ifndef POWDER_BOARD_DISPLAY
#define POWDER_BOARD_DISPLAY

#include "Board.hpp"
#include "ConfigManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <optional>
#include <random>

/**
 * @file BoardDisplay.hpp
 * @brief Board display management for the Powder Simulator.
 *
 * This file defines the BoardDisplay struct which handles rendering
 * and user interaction with the simulation board.
 */

/// General namespace for containing custom application code
namespace Powder
{

/**
 * @brief Manages the display and user interaction for the simulation board.
 *
 * The BoardDisplay handles rendering the board state, processing user input,
 * and updating the visual representation of the simulation.
 */
struct BoardDisplay
{
    /**
     * @brief Constructs a BoardDisplay with specified dimensions and configuration.
     *
     * @param xSize Width of the display board
     * @param ySize Height of the display board
     * @param config Reference to the configuration manager
     */
    BoardDisplay(uint xSize, uint ySize, const ConfigManager& config);

    /**
     * @brief Handles SFML events for user interaction.
     *
     * @param event Optional SFML event to process
     */
    void handleEvent(std::optional<sf::Event> event);

    /**
     * @brief Updates the display state for a single tick.
     *
     * @param window Pointer to the SFML rendering window
     */
    void tick(sf::RenderWindow* window);

    /**
     * @brief Renders the board to the window.
     *
     * @param window Pointer to the SFML rendering window
     */
    void render(sf::RenderWindow* window);

  private:
    const ConfigManager& config; ///< Reference to configuration manager
    const uint width;            ///< Width of the display
    const uint height;           ///< Height of the display

    int mouseX;               ///< Current mouse X position
    int mouseY;               ///< Current mouse Y position
    bool isLeftHeld = false;  ///< State of left mouse button
    bool isRightHeld = false; ///< State of right mouse button

    Board particles;           ///< Underlying board state
    std::mt19937 randomEngine; ///< Random number generator engine
    std::uniform_int_distribution<int>
        leftRightDistribution; ///< Random distribution for determining if a particle falls left or right
    std::uniform_int_distribution<int> colorDistribution; ///< Random distribution for generating color components

    /**
     * @brief Converts mouse coordinates to board positions.
     *
     * @param mouseX Mouse X position
     * @param mouseY Mouse Y position
     * @return Optional pair of board coordinates if valid, empty otherwise
     */
    std::optional<std::pair<uint, uint>> mouseToBoardPosition(int mouseX, int mouseY) const;
};

} // namespace Powder

#endif // POWDER_BOARD_DISPLAY
