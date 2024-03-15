#ifndef ELEMENT
#define ELEMENT

#include <SFML/Graphics/Color.hpp>

#include <variant>

namespace Powder::Physics
{

struct Plant
{
    sf::Color fillColor = sf::Color::Green;
};

struct Fire
{
    sf::Color fillColor = sf::Color::Red;
};

struct Wood
{
    sf::Color fillColor = sf::Color::Yellow;
};

struct Stone
{
    sf::Color fillColor = sf::Color::White;
};

// HACK: janky
using Element = std::variant<Wood, Stone, Plant, Fire>;

} // namespace Powder::Physics

#endif // ELEMENT
