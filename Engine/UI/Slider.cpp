#include "Slider.hpp"
#include "GameInfo.hpp"
#include <algorithm>

Slider::Slider(Vector2f position, size_t background, size_t slider, size_t circle, size_t label,
       Vector2f labelOffset, Vector2f sliderOffset, Vector2i size, Vector2i sliderSize, Vector2i ballSize)
    :UIObject(Position2D(position, size)), _sliderOffset(sliderOffset), _sliderSize(sliderSize),  _ballSize(ballSize), _value(0)
{
    addTexture(background);
    addTexture(slider);
    addTexture(circle);
    addTexture(label);

    texture(1).offsetPosition = sliderOffset;
    texture(2).offsetPosition = _sliderOffset + Vector2f(_value * _sliderSize.x - _ballSize.x/2, _sliderSize.y/2 - _ballSize.y/2);
    texture(3).offsetPosition = labelOffset;
}

void Slider::setCallFunction(std::function<void(float)> call)
{
    _call = call;
}

void Slider::setValue(float value)
{
    if (value < 0 && value > 1)
        throw "value should be from 0 to 1";

    _value = value;
    texture(2).offsetPosition = _sliderOffset + Vector2f(_value * _sliderSize.x - _ballSize.x/2, _sliderSize.y/2 - _ballSize.y/2);
}

void Slider::onStartDrag(){}
void Slider::onDrag() {}
void Slider::onEndDrag() {}
void Slider::onMouseDown() {}
void Slider::onMouseClick()
{
    Vector2i pos = GameInfo::mousePosition();
    float newValue = (pos.x - position().x - _sliderOffset.x) / _sliderSize.x;
    if (pos.y >= position().y + _sliderOffset.y && pos.y <= position().y + _sliderOffset.y + _sliderSize.y)
    {
        float oldValue = _value;
        _value = std::max(0.f, std::min(newValue, 1.f));

        if (_value != oldValue)
        {
            _call(_value);
            texture(2).offsetPosition = _sliderOffset + Vector2f(_value * _sliderSize.x - _ballSize.x/2, _sliderSize.y/2 - _ballSize.y/2);
        }
    }
}
void Slider::onMouseUp() {}
void Slider::onFrame() {}
