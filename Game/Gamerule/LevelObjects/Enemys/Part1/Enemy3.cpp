#include "Enemy3.hpp"
#include "Engine.hpp"
#include <math.h>

Enemy3::Enemy3(std::function<Vector2f(const Enemy3& obj)> moving)
    : Spaceship(_maxHp, _speed),  _moving(moving), _shotTimer(0), _rotationSpeed(0.66),
      _currentLifeTime(0)
{
    auto func = [](Bullet& a) -> void
    {
        a.setPosition(a.position() + Vector2f(cos(a.angle() - M_PI/2), sin(a.angle() - M_PI/2)) *
               (240.0 * GameInfo::deltaTime() * (a.currentLifeTime()+0.5 - static_cast<int>(a.currentLifeTime()+0.5))));
    };

    setTexture(11);
    setId("enemy");
    setTextureSize(Vector2i(50, 50));
    _shutter.addBulletType(func, 100, Bullet::Type::Red);

    addCollider({Vector2f(0, -20), Vector2f(15, -15), Vector2f(20, 0), Vector2f(15, 15),
                 Vector2f(0, 20), Vector2f(-15, 15), Vector2f(-20, 0), Vector2f(-15, -15)},
    {Collider::CollisionType::B}, {});
}

void Enemy3::onFrame()
{
    Vector2f nextPos = _moving(*this);
    moveTo(nextPos);
    setAngle(angle() + GameInfo::deltaTime()*_rotationSpeed);
    if(_shotTimer >= _shotSpeed)
    {
        _shotTimer = 0;
        for (int i = 0; i < 8; i++)
        {
            _shutter.setPosition(position() + Vector2f(25 * cos(angle() + i*M_PI/4), 25 * sin(angle() + i*M_PI/4)));
            _shutter.shot(0, angle() + i*M_PI/4 - M_PI);
        }
    }
    _shotTimer += GameInfo::deltaTime();
    _currentLifeTime += GameInfo::deltaTime();
}

double Enemy3::currentLifeTime() const
{
    return _currentLifeTime;
}

void Enemy3::resetTime()
{
    _currentLifeTime = 0;
}

void Enemy3::kill()
{
    _hp = 0;
}

bool Enemy3::isAlive()
{
    return _hp > 0;
}
