#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "UIObject.hpp"
#include <functional>

class Slider : public UIObject
{
    friend class Window;

public:
    Slider(Vector2f position, size_t background, size_t slider, size_t circle, size_t label,
           Vector2f labelOffset, Vector2f sliderOffset, Vector2i size, Vector2i sliderSize, Vector2i ballSize);
    void setCallFunction(std::function<void(float)> call);
    void setValue(float value);

private:
    void onStartDrag() final;
    void onDrag() final;
    void onEndDrag() final;
    void onMouseDown() final;
    void onMouseClick() final;
    void onMouseUp() final;
    void onFrame() override;

    std::function <void(float)> _call;
    Vector2f _sliderOffset;
    Vector2i _sliderSize;
    Vector2i _ballSize;
    float _value;
};

#endif // SLIDER_HPP
