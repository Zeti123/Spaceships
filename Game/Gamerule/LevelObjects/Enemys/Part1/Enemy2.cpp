#include "Enemy2.hpp"
#include "math.h"
#include "Engine.hpp"

constexpr double Enemy2::_shotSpeed;

Enemy2::Enemy2(std::function<Vector2f(const Enemy2& obj)> moving)
    :Spaceship(_maxHp, _speed), _moving(moving), _shotTimer(0), _currentLifeTime(0)
{
    setTexture(10);
    setId("enemy");
    setTextureSize(Vector2i(35, 40));

    addCollider({Vector2f(-20, 0), Vector2f(-3, 16), Vector2f(15, 16),
                 Vector2f(15, -16), Vector2f(-3, -16)}, {Collider::CollisionType::B}, {});
}

void Enemy2::onFrame()
{
    Vector2f nextPos = _moving(*this);
    moveTo(nextPos);
    GameObject* obj = Engine::Instance().findObjectById("player");
    setAngle(atan2(obj->position().y - position().y, obj->position().x - position().x));
    if(_shotTimer >= _shotSpeed)
    {
        _shotTimer = 0;
        _shutter.setPosition(position() + Vector2f(cos(angle()), sin(angle())) * 20);
        _shutter.shotSimple(angle(), _bulletSpeed, 1000000.0, Bullet::Type::Red);
    }
    _shotTimer += GameInfo::deltaTime();
    _currentLifeTime += GameInfo::deltaTime();
}

void Enemy2::kill()
{
    _hp = 0;
}

bool Enemy2::isAlive()
{
    return _hp > 0;
}

void Enemy2::resetTime()
{
    _currentLifeTime = 0;
}

double Enemy2::currentLifeTime() const
{
    return _currentLifeTime;
}
