#ifndef POWDER_BOARD_DISPLAY
#define POWDER_BOARD_DISPLAY

#include "Board.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <random>

namespace Powder
{

struct BoardDisplay
{
    BoardDisplay(uint xSize, uint ySize);

    void handleEvent(sf::Event event);
    void tick();
    void render(sf::RenderWindow* window);

  private:
    const uint width;
    const uint height;

    int mouseX;
    int mouseY;
    bool isHeld = false;
    std::pair<int, int> mousePosition = {0, 0};

    Board particles;
    Board particleReservations;
    std::mt19937 randomEngine;
};

} // namespace Powder

#endif // POWDER_BOARD_DISPLAY
