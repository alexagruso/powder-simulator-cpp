#ifndef POWDER_PARTICLE
#define POWDER_PARTICLE

#include <SFML/Graphics/Color.hpp>

#include <optional>

namespace Powder
{

struct Particle
{
    Particle(sf::Color color);

    sf::Color color;
};

typedef std::optional<Particle> OptParticle;

} // namespace Powder

#endif // POWDER_PARTICLE
