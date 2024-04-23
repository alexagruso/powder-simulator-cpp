#ifndef TEXT
#define TEXT
#include "ui/Positioning.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Text.hpp>

#include <stack>

namespace Powder
{

// TODO: extract this into general enum



// TODO: Tidy up member variables

class Text
{
  private:
  public:
    sf::Vector2f position;

    sf::Text text;

    Positioning positioning = Positioning::RIGHT;

    Text(sf::Vector2i position, Positioning positioning);

    void setColor(sf::Color color);

    void tick(sf::RenderWindow& window);
};

} // namespace Powder

#endif // Text
