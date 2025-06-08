#ifndef POWDER_BOARD
#define POWDER_BOARD

#include "Particle.hpp"

#include <sys/types.h>
#include <vector>

/**
 * @file Board.hpp
 * @brief Board class for managing the simulation grid.
 *
 * This file defines the Board struct which represents the grid where
 * particles are simulated.
 */

/// General namespace for containing custom application code
namespace Powder
{

/**
 * @brief Represents the simulation board/grid for particles.
 *
 * The Board manages a 2D grid of boolean values representing particle
 * presence or absence at each position.
 */
struct Board
{
    /**
     * @brief Constructs a Board with specified dimensions.
     *
     * @param xSize Width of the board
     * @param ySize Height of the board
     */
    Board(uint xSize, uint ySize);

    /**
     * @brief Checks if a particle exists at the specified position.
     *
     * @param x X-coordinate to check
     * @param y Y-coordinate to check
     * @return Particle instance if present at the position, std::nullopt if void
     */
    OptParticle at(uint x, uint y) const;

    /**
     * @brief Sets the particle state at the specified position.
     *
     * @param x X-coordinate to set
     * @param y Y-coordinate to set
     * @param value New particle instance (std::nullopt for void particle)
     * @return True if the position was valid and state was set, false otherwise
     */
    bool set(uint x, uint y, OptParticle value);

    /**
     * @brief Checks if a position is within the board boundaries.
     *
     * @param x X-coordinate to check
     * @param y Y-coordinate to check
     * @return True if (x, y) is within board bounds, false otherwise
     */
    bool isValidBoardPosition(int x, int y) const;

    const uint width;  ///< Width of the board
    const uint height; ///< Height of the board

  private:
    std::vector<std::vector<OptParticle>> board; ///< 2D vector representing the board state
};

} // namespace Powder

#endif // POWDER_BOARD
