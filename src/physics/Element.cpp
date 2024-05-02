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
    return 30;
}

sf::Color Wood::fillColor()
{
    return sf::Color{222, 184, 135};
}

uint Wood::staticWeight()
{
    return 20;
}

sf::Color Stone::fillColor()
{
    return sf::Color{189, 202, 203};
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

sf::Color Oil::fillColor()
{
    return sf::Color{59, 49, 49};
}

uint Oil::staticWeight()
{
    return 4;
}

sf::Color Metal::fillColor()
{
    return sf::Color{59, 69, 69};
}

uint Metal::staticWeight()
{
    return 20;
}

sf::Color Acid::fillColor()
{
    return sf::Color{38, 216, 64};
}

uint Acid::staticWeight()
{
    return 25;
}
