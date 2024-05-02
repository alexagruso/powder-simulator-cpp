#include "physics/Element.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Element Pattern Checking")
{
    using namespace Powder::Physics;

    std::vector<Element*> elements;

    elements.push_back(new Fire{});
    elements.push_back(new Acid{});
    elements.push_back(new Water{});

    REQUIRE(Element::isOfType<Fire>(elements.at(0)));
    REQUIRE(Element::isOfType<Acid>(elements.at(1)));
    REQUIRE(Element::isOfType<Water>(elements.at(2)));

    REQUIRE_FALSE(Element::isOfType<Acid>(elements.at(0)));
    REQUIRE_FALSE(Element::isOfType<Water>(elements.at(1)));
    REQUIRE_FALSE(Element::isOfType<Fire>(elements.at(2)));

    for (Element* element : elements)
    {
        delete element;
    }
}
