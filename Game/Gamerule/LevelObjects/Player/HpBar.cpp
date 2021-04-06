#include "HpBar.hpp"
#include <algorithm>

HpBar::HpBar(Vector2f position, size_t emptyBarTexture, size_t fullBarTeture, size_t shieldBarTeture,
             Vector2i fullBarTextureOffset, Spaceship* spaceship)
    :GameObject(), _parent(spaceship)
{
    setPosition(position);
    addTexture(emptyBarTexture);
    addTexture(fullBarTeture);
    addTexture(shieldBarTeture);
    texture(1).offsetPosition = fullBarTextureOffset.toV2f();
    texture(2).offsetPosition = fullBarTextureOffset.toV2f();
}

void HpBar::onFrame()
{
    texture(1).textureScale.x = std::max(0.0, static_cast<double>(_parent->hp()) / _parent->maxHp());
    texture(2).textureScale.x = std::max(0.0, static_cast<double>(_parent->shield()) / _parent->maxHp());
}
