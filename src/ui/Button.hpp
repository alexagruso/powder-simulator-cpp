#ifndef BUTTON
#define BUTTON

#include "event/Event.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

namespace Powder
{

class Button
{
  private:
    unsigned int width;
    unsigned int height;

    int xPosition;
    int yPosition;

    bool active;

    sf::RectangleShape body;

  public:
    Button(sf::Vector2u size, sf::Vector2i position);

    bool contains(sf::Vector2i mousePosition) const;
    bool isActive() const;
    void drawTo(sf::RenderWindow* window) const;
    void setColor(sf::Color color);

    void earlyUpdate(Event event);
};

} // namespace Powder

#endif // BUTTON