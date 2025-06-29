#ifndef POWDER_BOARD_DISPLAY
#define POWDER_BOARD_DISPLAY

#include "Board.hpp"
#include "ConfigManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <optional>
#include <random>

namespace Powder
{

struct BoardDisplay
{
    BoardDisplay(uint xSize, uint ySize, const ConfigManager& config);

    void handleEvent(std::optional<sf::Event> event);
    void tick(sf::RenderWindow* window);
    void render(sf::RenderWindow* window);

  private:
    const ConfigManager& config;
    const uint width;
    const uint height;

    int mouseX;
    int mouseY;
    bool isLeftHeld = false;
    bool isRightHeld = false;
    int brushSize = 1;
    static constexpr int MAX_BRUSH_SIZE = 10;

    Board particles;
    std::mt19937 randomEngine;
    std::uniform_int_distribution<int> leftRightDistribution;
    std::uniform_int_distribution<int> colorDistribution;

    std::optional<std::pair<uint, uint>> mouseToBoardPosition(int mouseX, int mouseY) const;
};

} // namespace Powder

#endif // POWDER_BOARD_DISPLAY
