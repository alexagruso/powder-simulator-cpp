#ifndef POWDER_EVENT_APPLICATION_EXIT
#define POWDER_EVENT_APPLICATION_EXIT

#include "application/events/Event.hpp"

namespace Powder
{

// This event will trigger the application to close
struct ApplicationExitEvent : Event
{
    uint staticPriority() override;

  protected:
    static const uint priority = 50;
};

} // namespace Powder

#endif // POWDER_EVENT_APPLICATION_EXIT
