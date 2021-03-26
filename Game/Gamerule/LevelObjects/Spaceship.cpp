#include "Spaceship.hpp"
#include "Bullet.hpp"
#include "LevelManager.hpp"
#include "PickUp.hpp"

#include <iostream>
#include <math.h>

Spaceship::Spaceship(int maxHp, int speed)
    :PhysicalObject(), _untouchable(0), _maxHp(maxHp), _hp(maxHp), _shield(0), _speed(speed)
{
    addTexture(0);
}

void Spaceship::onDestroy()
{
    if (std::rand()%20 < 1)
        LevelManager::Instance().addObject(new PickUp(position()));
}

bool Spaceship::blockLevel()
{
    return true;
}

bool Spaceship::moveTo(const Vector2f& position)
{
    /*Vector2f l = position - this->position();
    double len = l.length();
    if (_speed*deltaTime >= len)
    {
        setPosition(position);
        return false;
    }
    l = l * (_speed/len * deltaTime);
    setPosition(this->position() + l);
    return true;*/
    double dist = (this->position().x - position.x)*(this->position().x - position.x) +
                  (this->position().y - position.y)*(this->position().y - position.y);
    double toMove = _speed * GameInfo::deltaTime();

    if (dist <= toMove)
    {
        setPosition(Vector2f(position.x, position.y));
        return false;
    }

    int right = (position.x > this->position().x) ? 1 : -1;
    int down = (position.y > this->position().y) ? 1 : -1;

    double distX = std::abs(this->position().x - position.x);
    double distY = std::abs(this->position().y - position.y);

    this->setPosition(this->position() + Vector2f((distX / (distX + distY)) * right * toMove,
                                                  (distY / (distX + distY)) * down * toMove));

    return true;
}

void Spaceship::takeDamage(int damage)
{
    if (isUntouchable() == false)
    {
        if (_shield > 0)
        {
            _shield-=damage;
            if (_shield < 0)
                _hp += _shield;
        }
        else
            _hp -= damage;
    }
}

void Spaceship::setTextureSize(Vector2i siz)
{
    setSize(siz);
    texture(0).offsetPosition = texture(0).offsetPosition - Vector2f(size().x, size().y)*(1.0/2);
}

void Spaceship::refillHp()
{
    _hp = _maxHp;
}

void Spaceship::addShield()
{
    _shield = _maxHp;
}

void Spaceship::makeUntouchable(double time)
{
    _untouchable = time;
}

int Spaceship::hp() const
{
    return _hp;
}

int Spaceship::maxHp() const
{
    return _maxHp;
}

int Spaceship::shield() const
{
    return _shield;
}

bool Spaceship::isUntouchable() const
{
    return _untouchable > 0;
}

/*
    auto func = [](const Vector2f& prevPos, double angle, double time) -> Vector2f
    {
        Vector2f pos;
        pos = Vector2f(cos(prevPos.x / 20) * 1.1, sin(prevPos.y / 20) * 1.1) + Vector2f(cos(angle)*1.2, 1.2);
        return (prevPos + pos);
    };*/
