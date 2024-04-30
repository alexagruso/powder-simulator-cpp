#ifndef POWDER_ELEMENT
#define POWDER_ELEMENT

#include <SFML/Graphics/Color.hpp>

#include <optional>

namespace Powder::Physics
{

struct Element
{
    virtual ~Element() {}

    virtual sf::Color fillColor();

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
};

//  TODO: extract these into separate files

struct Plant : Element
{
    sf::Color fillColor() override;
};

// struct Wood : Element
// {
//     sf::Color fillColor() final
//     {
//         return sf::Color::Yellow;
//     }
// };
//
// struct Stone : Element
// {
//     sf::Color fillColor()
//     {
//         return sf::Color::White;
//     }
// };

} // namespace Powder::Physics

#endif // POWDER_ELEMENT
