#ifndef POWDER_PARTICLE
#define POWDER_PARTICLE

#include <SFML/Graphics/Color.hpp>

#include <optional>

/**
 * @file Particle.hpp
 * @brief Particle class for storing individual particle data
 *
 * This file defines the Particle struct which stores its color value
 */

/// General namespace for containing custom application code
namespace Powder
{

/**
 * @brief Represents an individual particle
 *
 * This struct stores information for each individual particle, including
 * its color.
 */
struct Particle
{
    /**
     * @brief Constructs a new particle with the specified color
     *
     * @param color Color of the particle
     */
    Particle(sf::Color color);

    sf::Color color; ///< Color value for the particle
};

typedef std::optional<Particle> OptParticle; ///< Type alias for convenience

} // namespace Powder

#endif // POWDER_PARTICLE
