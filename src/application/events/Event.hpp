#ifndef POWDER_EVENT
#define POWDER_EVENT

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <optional>
#include <sys/types.h>

namespace Powder
{

struct Event
{
    virtual ~Event() {} // This forces the type to be considered polymorphic

    virtual uint staticPriority();

    // This must be defined per class because dynamic_cast requires a pointer to a polymorphic object
    template <typename CheckType>
    static std::optional<CheckType*> isOfType(Event* object)
    {
        CheckType* result = dynamic_cast<CheckType*>(object);

        if (result != nullptr)
        {
            return result;
        }

        return std::nullopt;
    }

    // Default priority for all events, higher value means higher priority
  protected:
    static const uint priority = 0;
};

} // namespace Powder

#endif // POWDER_EVENT
