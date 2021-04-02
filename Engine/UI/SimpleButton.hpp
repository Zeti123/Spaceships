#ifndef SIMPLEBUTTON_HPP
#define SIMPLEBUTTON_HPP

#include <functional>
#include "UIObject.hpp"

class SimpleButton : public UIObject
{
    friend class Window;

public:
    SimpleButton(Vector2f position, size_t texture, Vector2i size, std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> normalColor = {0, 0, 0, 0},
                 std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> draggedColor = {20, 20, 20, 0}, std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> clickedColor = {40, 40, 40, 0});
    void setCallFunction(std::function<void()> call);

private:
    void onStartDrag() final;
    void onDrag() final;
    void onEndDrag() final;
    void onMouseDown() final;
    void onMouseClick() final;
    void onMouseUp() final;
    void onFrame() override;

    void setNormalColor(std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> color);
    void setDraggedColor(std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> color);
    void setClickedColor(std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> color);

    std::function <void()> _call;
    size_t _texture;
    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> _normalColor, _draggedColor, _clickedColor;
};

#endif // SIMPLEBUTTON_HPP
