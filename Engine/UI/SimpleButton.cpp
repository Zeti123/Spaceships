#include "SimpleButton.hpp"

SimpleButton::SimpleButton(Vector2f position, size_t texture, Vector2i size, std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> normalColor,
                           std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> draggedColor, std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> clickedColor)
    :UIObject(Position2D(position, size)), _texture(texture), _normalColor(normalColor), _draggedColor(draggedColor), _clickedColor(clickedColor)
{
    addTexture(_texture);
}

void SimpleButton::setCallFunction(std::function<void()> call)
{
    _call = call;
}

void SimpleButton::onStartDrag()
{
    texture(0).color = _draggedColor;
}

void SimpleButton::onDrag(){}

void SimpleButton::onEndDrag()
{
    texture(0).color = _normalColor;
}

void SimpleButton::onMouseDown()
{
    texture(0).color = _clickedColor;
}

void SimpleButton::onMouseClick() {}

void SimpleButton::onMouseUp()
{
    texture(0).color = _draggedColor;
    _call();
}

void SimpleButton::onFrame(){}

void SimpleButton::setNormalColor(std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> color)
{
    _normalColor = color;
}

void SimpleButton::setDraggedColor(std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> color)
{
    _draggedColor = color;
}

void SimpleButton::setClickedColor(std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> color)
{
    _clickedColor = color;
}
