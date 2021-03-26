#include "Button.hpp"

Button::Button(Vector2f position, size_t nornalTexture, size_t draggedTexture, size_t clickedTexture,
               size_t label, Vector2f labelOffset, Vector2i size)
    : UIObject(Position2D(position, size)), _normal(nornalTexture),
      _dragged(draggedTexture), _clicked(clickedTexture), _label(label)
{
    addTexture(_normal);
    addTexture(_label);
    texture(1).offsetPosition = labelOffset;
}

void Button::setCallFunction(std::function<void()> call)
{
    _call = call;
}

void Button::onStartDrag()
{
    setTexture(_dragged);
}

void Button::onDrag(){}

void Button::onEndDrag()
{
    setTexture(_normal);
}

void Button::onMouseDown()
{
    setTexture(_clicked);
}

void Button::onMouseClick() {}

void Button::onMouseUp()
{
    setTexture(_dragged);
    _call();
}

void Button::onFrame(){}
