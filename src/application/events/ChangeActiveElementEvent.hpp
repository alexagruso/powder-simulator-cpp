#ifndef POWDER_EVENT_CHANGE_ACTIVE_ELMENT
#define POWDER_EVENT_CHANGE_ACTIVE_ELMENT

#include "application/events/Event.hpp"
#include "physics/Element.hpp"

namespace Powder
{

struct ChangeActiveElementEvent : Event
{
    ChangeActiveElementEvent(Physics::Element* element) : element{element} {}

    uint staticPriority() override;

    Physics::Element* element;

  protected:
    static const uint priority = 5;
};

} // namespace Powder

#endif // POWDER_EVENT_CHANGE_ACTIVE_ELMENT
