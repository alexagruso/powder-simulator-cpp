#ifndef ELEMENT
#define ELEMENT

#include <SFML/Graphics/Color.hpp>

#include <variant>

enum class ElementType
{
    SOLID,
    LIQUID,
    GAS,
    POWDER,
};

namespace Powder::Physics
{

struct Plant
{
    sf::Color fillColor = sf::Color::Green;
    ElementType type = ElementType::SOLID;
};

struct Fire
{
    sf::Color fillColor = sf::Color::Red;
    ElementType type = ElementType::GAS;
};

struct Wood
{
    sf::Color fillColor = sf::Color::Yellow;
    ElementType type = ElementType::SOLID;
};

struct Stone
{
    sf::Color fillColor = sf::Color::White;
    ElementType type = ElementType::POWDER;
};

// HACK: janky
using Element = std::variant<Wood, Stone, Plant, Fire>;

} // namespace Powder::Physics

#endif // ELEMENT
