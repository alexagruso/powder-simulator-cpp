#ifndef POWDER_ENTITY_POSITIONING
#define POWDER_ENTITY_POSITIONING

namespace Powder
{

enum class HorizontalPositioning
{
    LEFT,
    RIGHT,
};

enum class VerticalPositioning
{
    TOP,
    BOTTOM,
};

// Default positioning is top left
struct EntityPositioning
{
    HorizontalPositioning horizontal = HorizontalPositioning::LEFT;
    VerticalPositioning vertical = VerticalPositioning::TOP;
};

} // namespace Powder

#endif // POWDER_ENTITY_POSITIONING
