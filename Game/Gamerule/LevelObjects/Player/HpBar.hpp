#ifndef HPBAR_HPP
#define HPBAR_HPP

#include "Spaceship.hpp"
#include "Vector2i.hpp"

class HpBar: public GameObject
{
public:
    HpBar(Vector2f position, size_t emptyBarTexture, size_t fullBarTeture, size_t shieldBarTexture,
          Vector2i fullBarTextureOffset, Spaceship* spaceship);
    void onFrame() override;

private:
    Spaceship* _parent;
};

#endif // HPBAR_HPP
