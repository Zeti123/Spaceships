#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include "UIObject.hpp"

class Button : public UIObject
{

    friend class Window;

public:
    Button(Vector2f position, size_t nornalTexture, size_t draggedTexture, size_t clickedTexture, size_t label,
           Vector2f labelOffset, Vector2i size);
    void setCallFunction(std::function<void()> call);

private:
    void onStartDrag() final;
    void onDrag() final;
    void onEndDrag() final;
    void onMouseDown() final;
    void onMouseClick() final;
    void onMouseUp() final;
    void onFrame() override;

    std::function <void()> _call;
    size_t _normal, _dragged, _clicked;
    size_t _label;
};

#endif // BUTTON_HPP
