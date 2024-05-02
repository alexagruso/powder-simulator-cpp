#include "ui/Entity.hpp"

#include "physics/Element.hpp"
#include "ui/ElementButton.hpp"
#include "ui/EntityPositioning.hpp"
#include "ui/Positioning.hpp"
#include "ui/Text.hpp"
#include "ui/board/BoardDisplay.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Entity Pattern Checking")
{
    using namespace Powder;

    std::vector<UIEntity*> entities;

    EntityPositioning positioning;
    positioning.horizontal = HorizontalPositioning::LEFT;
    positioning.vertical = VerticalPositioning::TOP;

    entities.push_back(new Text{
        {10, 10},
        "Test", Positioning::LEFT
    });
    entities.push_back(new UI::BoardDisplay{
        {10, 10},
        new Physics::Fire{}
    });
    entities.push_back(new ElementButton{
        {10, 10},
        {10, 10},
        positioning, new Physics::Fire{}
    });

    REQUIRE(UIEntity::isOfType<Text>(entities.at(0)));
    REQUIRE(UIEntity::isOfType<UI::BoardDisplay>(entities.at(1)));
    REQUIRE(UIEntity::isOfType<ElementButton>(entities.at(2)));

    REQUIRE_FALSE(UIEntity::isOfType<ElementButton>(entities.at(0)));
    REQUIRE_FALSE(UIEntity::isOfType<Text>(entities.at(1)));
    REQUIRE_FALSE(UIEntity::isOfType<UI::BoardDisplay>(entities.at(2)));

    for (UIEntity* entity : entities)
    {
        delete entity;
    }
}
