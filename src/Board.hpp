#ifndef POWDER_BOARD
#define POWDER_BOARD

#include <SFML/System/Vector2.hpp>

#include <optional>
#include <sys/types.h>
#include <vector>

namespace Powder
{

struct Board
{
    Board(uint xSize, uint ySize) : width{xSize}, height{ySize}
    {
        std::vector<bool> emptyRow{};
        emptyRow.resize(width);

        for (uint i = 0; i < width; i++)
        {
            emptyRow.at(i) = false;
        }

        this->board = std::vector<std::vector<bool>>{height, emptyRow};
    }

    bool at(uint x, uint y) const;
    bool set(uint x, uint y, bool value);

    std::optional<std::pair<uint, uint>> mouseToBoardPosition(int mouseX, int mouseY) const;
    bool isValidBoardPosition(int x, int y) const;

    const uint width;
    const uint height;

  private:
    std::vector<std::vector<bool>> board;
};

} // namespace Powder

#endif // POWDER_BOARD
