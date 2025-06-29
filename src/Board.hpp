#ifndef POWDER_BOARD
#define POWDER_BOARD

#include "Particle.hpp"

#include <sys/types.h>
#include <vector>

namespace Powder
{

struct Board
{
    Board(uint xSize, uint ySize);

    OptParticle at(uint x, uint y) const;
    bool set(uint x, uint y, OptParticle value);

    bool isValidBoardPosition(int x, int y) const;

    const uint width;
    const uint height;

  private:
    std::vector<std::vector<OptParticle>> board;
};

} // namespace Powder

#endif // POWDER_BOARD
