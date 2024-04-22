#include "Element.hpp"

#include "config/Config.hpp"

using namespace Powder::Physics;

sf::Color Element::fillColor()
{
    return Config::PUKE_PLACEHOLDER;
}

sf::Color Fire::fillColor()
{
    return sf::Color::Red;
}

sf::Color Plant::fillColor()
{
    return sf::Color::Green;
}
