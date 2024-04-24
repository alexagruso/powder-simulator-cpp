#ifndef TEXT
#define TEXT
#include "ui/Positioning.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string.h>

#include <stack>

namespace Powder
{

// TODO: extract this into general enum

using std::string;
// TODO: Tidy up member variables

class Text
{
  private:
  public:
    sf::Vector2f position;

    sf::Text text;

    sf::Font font;

    Positioning positioning = Positioning::RIGHT;

    Text(sf::Vector2i position, Positioning positioning);

    void setColor(sf::Color color);

    void setText(string name);

    void tick(sf::RenderWindow& window);
};

} // namespace Powder

#endif // Text
