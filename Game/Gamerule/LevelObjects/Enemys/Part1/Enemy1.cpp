#include "Enemy1.hpp"
#include "math.h"
#include <iostream>

constexpr double Enemy1::_shotSpeed;

Enemy1::Enemy1(double angle)
    : Spaceship(_maxHp, _speed), _shotTimer(0)
{
    _direction = Vector2f(cos(angle), sin(angle));
    setTexture(9);
    setId("enemy");
    setTextureSize(Vector2i(50, 50));
    setAngle(angle);

    addCollider({Vector2f(17, 0), Vector2f(25, 23), Vector2f(7, 23),
                 Vector2f(-23, 0), Vector2f(7, -23), Vector2f(25, -23)}, {Collider::CollisionType::B}, {});
}

void Enemy1::onFrame()
{
    moveTo(position() + (_direction*200));
    _shutter.setPosition(position() + _direction*20);
    _shotTimer += GameInfo::deltaTime();
    if (_shotTimer >= _shotSpeed)
    {
        _shutter.shotSimple(angle(), _bulletSpeed, 1000000.0, Bullet::Type::Red);
        _shotTimer = 0;
    }
    if (position().x > GameInfo::resolution().x + size().x)
        setPosition(Vector2f(-size().x, position().y));
    if (position().y > GameInfo::resolution().y + size().y)
        setPosition(Vector2f(position().x, -size().y));
    if (position().x < -size().x)
        setPosition(Vector2f(GameInfo::resolution().x + size().x, position().y));
    if (position().y < -size().y)
        setPosition(Vector2f(position().x, GameInfo::resolution().y + size().y));
}

void Enemy1::kill()
{
    _hp = 0;
}

bool Enemy1::isAlive()
{
    return _hp > 0;
}
