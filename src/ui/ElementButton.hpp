#ifndef POWDER_ELEMENT_BUTTON
#define POWDER_ELEMENT_BUTTON

#include "Entity.hpp"
#include "EntityPositioning.hpp"
#include "physics/Element.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

#include <vector>

namespace Powder
{

struct ElementButton : Entity
{
    ElementButton(sf::Vector2u size, sf::Vector2i position, EntityPositioning positioning, Physics::Element* element);
    ~ElementButton();

    std::vector<Event*> handleEvent(Event* event);

    void tick();
    std::vector<sf::Drawable*> render();

  private:
    sf::Vector2f size;
    sf::Vector2f position;
    EntityPositioning positioning;
    Physics::Element* element;

    sf::RectangleShape* body;

    bool contains(sf::Vector2i mousePosition) const;
};

} // namespace Powder

#endif // POWDER_ELEMENT_BUTTON
