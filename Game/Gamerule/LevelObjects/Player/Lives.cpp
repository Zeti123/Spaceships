#include "Lives.hpp"
#include "Player.hpp"

Lives::Lives(Vector2f position, Player* spaceship)
    :_parent(spaceship), _lives(3)
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

void Lives::onFrame()
{
    for (size_t i = 1; i <= 4; i++)
    {
        if (i <= _lives)
            texture(i).visible = true;
        else
            texture(i).visible = false;
    }

    if (_parent->hp() <= 0 && _parent->isAlive())
    {
        if (_lives <= 1)
        {
            _parent->kill();
            _lives--;
        }
        else
        {
            _parent->refillHp();
            _parent->lifeLost();
            _lives--;
        }
    }
}

void Lives::addLife()
{
    if (_lives >= 4)
    {
        _parent->refillHp();
    }
    else
    {
        _lives++;
    }
}

void Lives::reset()
{
    _lives = 3;
}
