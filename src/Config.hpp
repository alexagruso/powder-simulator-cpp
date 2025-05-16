#ifndef POWDER_CONFIG
#define POWDER_CONFIG

#include <SFML/Graphics/Color.hpp>

#include <string>

namespace Powder::Config
{

const uint FRAMERATE_LIMIT = 60;

const std::string WINDOW_TITLE = "Powder Simulator";

const sf::Color WINDOW_CLEAR_COLOR = sf::Color::Black;
const sf::Color VOID_COLOR = sf::Color::Black;
const sf::Color POWDER_COLOR = sf::Color::White;

const uint BOARD_WIDTH = 100;
const uint BOARD_HEIGHT = 100;
const uint PARTICLE_PIXEL_SIZE = 4;

const uint WINDOW_WIDTH = BOARD_WIDTH * PARTICLE_PIXEL_SIZE;
const uint WINDOW_HEIGHT = BOARD_HEIGHT * PARTICLE_PIXEL_SIZE;

} // namespace Powder::Config

#endif // POWDER_CONFIG
