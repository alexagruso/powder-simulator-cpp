#ifndef BUTTON
#define BUTTON

#include "event/Event.hpp"
#include "physics/Particle.hpp"
#include "ui/Board.hpp"
#include "ui/Positioning.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

#include <stack>

namespace Powder
{

// TODO: extract this into general enum



// TODO: Tidy up member variables

class Button
{
  private:
  public:
    sf::Vector2f size;
    sf::Vector2f position;

    sf::RectangleShape body;

    // TODO: this element is for demo purposes only
    Physics::Element element;

    Positioning positioning = Positioning::RIGHT;

    Button(sf::Vector2u size, sf::Vector2i position, Positioning positioning);

    bool contains(sf::Vector2i mousePosition) const;
    void setColor(sf::Color color);


    void handleEvent(const Event& event, std::stack<Event>& events);
    void tick(sf::RenderWindow& window);
};

} // namespace Powder

#endif // BUTTON
