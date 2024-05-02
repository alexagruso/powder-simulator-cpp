<<<<<<< HEAD
#ifndef POWDER_ELEMENT
#define POWDER_ELEMENT

#include <SFML/Graphics/Color.hpp>

#include <optional>
#include <sys/types.h>
=======
#ifndef ELEMENT
#define ELEMENT

#include <SFML/Graphics/Color.hpp>

#include <variant>
>>>>>>> main

namespace Powder::Physics
{

<<<<<<< HEAD
struct Element
{
    virtual ~Element() {}

    virtual sf::Color fillColor();
    virtual uint staticWeight();

    template <typename ElementType>
    static std::optional<ElementType*> isOfType(Element* element)
    {
        ElementType* result = dynamic_cast<ElementType*>(element);

        if (result != nullptr)
        {
            return result;
        }

        return std::nullopt;
    }
};

struct Fire : Element
{
    sf::Color fillColor() override;
    uint staticWeight() override;
};

struct Plant : Element
{
    sf::Color fillColor() override;
    uint staticWeight() override;
};

struct Wood : Element
{
    sf::Color fillColor() override;
    uint staticWeight() override;
};

struct Stone : Element
{
    sf::Color fillColor() override;
    uint staticWeight() override;
};

struct Water : Element
{
    sf::Color fillColor() override;
    uint staticWeight() override;
};

} // namespace Powder::Physics

#endif // POWDER_ELEMENT
=======
struct Plant
{
    sf::Color fillColor = sf::Color::Green;
};

struct Fire
{
    sf::Color fillColor = sf::Color::Red;
};

struct Wood
{
    sf::Color fillColor = sf::Color::Yellow;
};

struct Stone
{
    sf::Color fillColor = sf::Color::White;
};

// HACK: janky
using Element = std::variant<Wood, Stone, Plant, Fire>;

} // namespace Powder::Physics

#endif // ELEMENT
>>>>>>> main
