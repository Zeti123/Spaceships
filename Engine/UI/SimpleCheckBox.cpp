#include "SimpleCheckBox.hpp"

SimpleCheckBox::SimpleCheckBox(Vector2f position, size_t texture, Vector2i size, size_t checkTexture, Vector2f checkOffset)
    :_checked(false)
{
    setPosition(position);
    addTexture(texture);
    addTexture(checkTexture);
    setSize(size);
    this->texture(1).offsetPosition = checkOffset;
    this->texture(1).visible = false;
}
void SimpleCheckBox::setCallFunction(std::function<void(bool)> func)
{
    _call = func;
}
bool SimpleCheckBox::checked() const
{
    return _checked;
}
void SimpleCheckBox::setChecked(bool checked)
{
    _checked = checked;
    this->texture(1).visible = checked;
}

void SimpleCheckBox::onStartDrag() {}
void SimpleCheckBox::onDrag() {}
void SimpleCheckBox::onEndDrag() {}
void SimpleCheckBox::onMouseDown() {}
void SimpleCheckBox::onMouseClick() {}
void SimpleCheckBox::onMouseUp()
{
    setChecked(checked() ^ true);
    _call(checked());
}
void SimpleCheckBox::onFrame() {}
