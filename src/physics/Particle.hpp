#ifndef PARTICLE
#define PARTICLE

#include <SFML/Graphics/Color.hpp>

#include <variant>

namespace Powder::Physics
{

struct Wood
{
};

struct Stone
{
};

using Element = std::variant<Wood, Stone>;

struct Particle
{
    Element element;
};

} // namespace Powder::Physics

#endif // PARTICLE