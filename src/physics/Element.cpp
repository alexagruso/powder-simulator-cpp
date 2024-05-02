#include "Element.hpp"

#include "config/Config.hpp"

using namespace Powder::Physics;

sf::Color Element::fillColor()
{
    return Config::PUKE_PLACEHOLDER;
}

uint Element::staticWeight()
{
    return 0;
}

sf::Color Fire::fillColor()
{
    return sf::Color::Red;
}

uint Fire::staticWeight()
{
    return 1;
}

sf::Color Plant::fillColor()
{
    return sf::Color::Green;
}

uint Plant::staticWeight()
{
    return 20;
}

sf::Color Wood::fillColor()
{
    return sf::Color::Yellow;
}

uint Wood::staticWeight()
{
    return 20;
}

sf::Color Stone::fillColor()
{
    return sf::Color::White;
}

uint Stone::staticWeight()
{
    return 10;
}

sf::Color Water::fillColor()
{
    return sf::Color::Blue;
}

uint Water::staticWeight()
{
    return 5;
}
