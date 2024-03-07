#ifndef BUTTON
#define BUTTON

#include "event/Event.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

namespace Powder
{

// TODO: Tidy up member variables

class Button
{
  private:
  public:
    sf::Vector2f size;
    sf::Vector2f position;

    sf::RectangleShape body;

    Button(sf::Vector2u size, sf::Vector2i position);

    bool contains(sf::Vector2i mousePosition) const;
    void setColor(sf::Color color);

    void handleEvent(const Event& event);
    void tick(sf::RenderWindow& window);
};

} // namespace Powder

#endif // BUTTON