#ifndef CONFIG
#define CONFIG

#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <string>

namespace ps::config
{

constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;
const std::string WINDOW_TITLE = "Powder Simulator";
const int WINDOW_STYLE = sf::Style::Default;

constexpr unsigned int FPS_MAX_LIMIT = 60;

} // namespace ps::config

#endif // CONFIG
