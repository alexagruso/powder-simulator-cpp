#include "ui/board/Board.hpp"

#include "application/events/ParticleCreationEvent.hpp"
#include "application/events/ParticleDeletionEvent.hpp"
#include "physics/Element.hpp"
#include "ui/board/BoardDisplay.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Board Accessors")
{
    Powder::UI::Board<int> board{
        {10, 10}
    };

    REQUIRE(board.dimensions.x == 10);
    REQUIRE(board.dimensions.y == 10);

    REQUIRE(!board.at({0, 0}));
    REQUIRE(!board.at({1, 1}));
    REQUIRE(!board.at({2, 2}));

    board.set({0, 0}, 1);
    board.set({1, 1}, 3);
    board.set({2, 2}, 5);

    REQUIRE(board.at({0, 0}).value() == 1);
    REQUIRE(board.at({1, 1}).value() == 3);
    REQUIRE(board.at({2, 2}).value() == 5);
}

TEST_CASE("BoardDisplay Events")
{
    Powder::UI::BoardDisplay board{
        {10, 10},
        new Powder::Physics::Fire{}
    };

    board.handleEvent(new Powder::ParticleCreationEvent{
        {5, 5},
        new Powder::Physics::Fire{}
    });

    REQUIRE(board.particles.at({5, 5}));

    board.handleEvent(new Powder::ParticleDeletionEvent{
        {5, 5},
    });

    REQUIRE_FALSE(board.particles.at({5, 5}));
}
