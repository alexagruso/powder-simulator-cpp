#ifndef POWDER_PARTICLE
#define POWDER_PARTICLE

#include "physics/Element.hpp"

namespace Powder::Physics
{

struct Particle
{
    Particle(Element* element);
    // particle does not own element
    // ~Particle();

    Element* element;
};

} // namespace Powder::Physics

#endif // POWDER_PARTICLE
