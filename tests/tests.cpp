#include "physics/Element.hpp"
#include "physics/Particle.hpp"
// #include "ui/Board.hpp"

#include <catch2/catch_test_macros.hpp>

// TEST_CASE("Board Physics")
// {
//     Powder::Board board{
//         {5, 5}
//     };
//
//     for (int i = 0; i < 5; i++)
//     {
//         board.set({i, i}, Powder::Physics::Particle{Powder::Physics::Fire{}});
//         REQUIRE(board.at({i, i}));
//     }
//
//     for (int i = 0; i < 5; i++)
//     {
//         board.set({i, i}, std::nullopt);
//         REQUIRE(!board.at({i, i}));
//     }
// }
