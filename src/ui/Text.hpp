#ifndef POWDER_TEXT
#define POWDER_TEXT

#include "ui/Entity.hpp"
#include "ui/Positioning.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

namespace Powder
{

struct Text : UIEntity
{
    Text(sf::Vector2i position, std::string value, Positioning positioning);

    void render(sf::RenderWindow* window) override;

    void setColor(sf::Color color);
    void setText(std::string name);

  private:
    sf::Vector2f position;
    sf::Text text;
    sf::Font font;

    Positioning positioning = Positioning::RIGHT;
};

} // namespace Powder

#endif // POWDER_TEXT
