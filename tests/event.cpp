#include "application/events/ApplicationExitEvent.hpp"
#include "application/events/ChangeActiveElementEvent.hpp"
#include "application/events/ParticleDeletionEvent.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Event Pattern Checking")
{
    using namespace Powder;

    std::vector<Event*> events;

    events.push_back(new ApplicationExitEvent{});
    events.push_back(new ChangeActiveElementEvent{nullptr});
    events.push_back(new ParticleDeletionEvent{
        {10, 10}
    });

    REQUIRE(Event::isOfType<ApplicationExitEvent>(events.at(0)));
    REQUIRE(Event::isOfType<ChangeActiveElementEvent>(events.at(1)));
    REQUIRE(Event::isOfType<ParticleDeletionEvent>(events.at(2)));

    REQUIRE_FALSE(Event::isOfType<ParticleDeletionEvent>(events.at(0)));
    REQUIRE_FALSE(Event::isOfType<ApplicationExitEvent>(events.at(1)));
    REQUIRE_FALSE(Event::isOfType<ChangeActiveElementEvent>(events.at(2)));

    for (Event* event : events)
    {
        delete event;
    }
}
