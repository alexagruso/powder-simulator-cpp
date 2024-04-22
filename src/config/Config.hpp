#ifndef POWDER_CONFIG
#define POWDER_CONFIG

#include <SFML/Graphics/Color.hpp>

#include <string>

namespace Powder::Config
{

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int FRAMERATE_LIMIT = 60;

const std::string WINDOW_TITLE = "Powder Simulator";

const sf::Color WINDOW_CLEAR_COLOR = sf::Color::Black;
const sf::Color PUKE_PLACEHOLDER = sf::Color(0x89A203FF);

} // namespace Powder::Config

#endif // POWDER_CONFIG
