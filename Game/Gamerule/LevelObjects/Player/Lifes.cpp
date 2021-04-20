#include "Lifes.hpp"
#include "Player.hpp"

Lifes::Lifes(Vector2f position, Player* spaceship)
    :_parent(spaceship), _lifes(3)
{
    setPosition(position);

    addTexture(23);
    addTexture(24);
    addTexture(24);
    addTexture(24);
    addTexture(24);

    texture(1).offsetPosition = Vector2f(60, 0);
    texture(2).offsetPosition = Vector2f(85, 0);
    texture(3).offsetPosition = Vector2f(110, 0);
    texture(4).offsetPosition = Vector2f(135, 0);
}

void Lifes::onFrame()
{
    for (size_t i = 1; i <= 4; i++)
    {
        if (i <= _lifes)
            texture(i).visible = true;
        else
            texture(i).visible = false;
    }

    if (_parent->hp() <= 0 && _parent->isAlive())
    {
        if (_lifes <= 1)
        {
            _parent->kill();
            _lifes--;
        }
        else
        {
            _parent->refillHp();
            _parent->lifeLost();
            _lifes--;
        }
    }
}

void Lifes::addLife()
{
    if (_lifes >= 4)
    {
        _parent->refillHp();
    }
    else
    {
        _lifes++;
    }
}

void Lifes::reset()
{
    _lifes = 3;
}
