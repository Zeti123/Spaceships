#ifndef SIMPLECHECKBOX_HPP
#define SIMPLECHECKBOX_HPP

#include <functional>
#include "UIObject.hpp"

class SimpleCheckBox : public UIObject
{
public:
    SimpleCheckBox(Vector2f position, size_t texture, Vector2i size, size_t checkTexture, Vector2f checkOffset);
    void setCallFunction(std::function<void(bool)> func);
    bool checked() const;
    void setChecked(bool checked);

private:
    void onStartDrag() final;
    void onDrag() final;
    void onEndDrag() final;
    void onMouseDown() final;
    void onMouseClick() final;
    void onMouseUp() final;
    void onFrame() override;

private:
    std::function <void(bool)> _call;
    bool _checked;
};

#endif // SIMPLECHECKBOX_HPP
