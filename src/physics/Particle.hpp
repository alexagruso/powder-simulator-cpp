<<<<<<< HEAD
#ifndef POWDER_PARTICLE
#define POWDER_PARTICLE
=======
#ifndef PARTICLE
#define PARTICLE
>>>>>>> main

#include "physics/Element.hpp"

namespace Powder::Physics
{

struct Particle
{
<<<<<<< HEAD
    Particle(Element* element);
    // particle does not own element
    // ~Particle();

    Element* element;
=======
    Element element;
>>>>>>> main
};

} // namespace Powder::Physics

<<<<<<< HEAD
#endif // POWDER_PARTICLE
=======
#endif // PARTICLE
>>>>>>> main
