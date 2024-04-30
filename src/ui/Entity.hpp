#ifndef POWDER_ENTITY
#define POWDER_ENTITY

#include "application/events/Event.hpp"

#include <SFML/Graphics/Drawable.hpp>

#include <vector>

namespace Powder
{

struct UIEntity
{
    virtual ~UIEntity() {}

    virtual std::vector<Event*> handleEvent(Event* event);
    virtual std::vector<Event*> tick();
    virtual std::vector<sf::Drawable*> render();

    // This must be defined per class because dynamic_cast requires a pointer to a polymorphic object
    template <typename CheckType>
    static std::optional<CheckType*> isOfType(UIEntity* object)
    {
        CheckType* result = dynamic_cast<CheckType*>(object);

        if (result != nullptr)
        {
            return result;
        }

        return std::nullopt;
    }
};

} // namespace Powder

#endif // POWDER_ENTITY
