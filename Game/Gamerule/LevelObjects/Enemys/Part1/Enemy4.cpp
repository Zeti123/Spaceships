#include "Enemy4.hpp"
#include "Enemy5.hpp"
#include <math.h>
#include "Engine.hpp"
#include <algorithm>

constexpr std::pair<int, int> Enemy4::distanceRange;

Enemy4::Enemy4(Enemy5* host)
    :Spaceship(_maxHp, _speed), _player(*dynamic_cast<Player*>(Engine::Instance().findObjectById("player"))),
      _nextPoint(0, 0), _host(host), _isHostAlive(true)
{
    nextPoint();
    addCollider({{17, 0}, {6, 8}, {-8, 18}, {-8, -18}, {6, -6}}, {Collider::CollisionType::B}, {});
    setTexture(12);
    setId("enemy");
    setPosition(host->position());
    setTextureSize(Vector2i(36, 36));
}

void Enemy4::onFrame()
{
    _shotTimer += GameInfo::deltaTime();
    setAngle(atan2(_player.position().y - position().y, _player.position().x - position().x));
    _shutter.setPosition(Vector2f(cos(angle()), sin(angle())) * (36/2) + position());
    if (_shotTimer >= _shotSpeed)
    {
        _shutter.shotSimple(angle(), _bulletSpeed, 1000000.0, Bullet::Type::Red);
        _shotTimer = 0;
    }
    if (!moveTo(_nextPoint))
        nextPoint();
}

void Enemy4::kill()
{
    _hp = 0;
}

bool Enemy4::isAlive()
{
    return _hp > 0;
}

void Enemy4::deadHost()
{
    _isHostAlive = false;
}

void Enemy4::onDestroy()
{
    if (_isHostAlive && _host != nullptr)
        _host->deadChild(this);
    Spaceship::onDestroy();
}

void Enemy4::nextPoint()
{
    double prevAngle = atan2(position().y - _player.position().y, position().x - _player.position().x);
    double angle = ((rand() % 1000)/1000.0 - 0.5) * 2 + prevAngle;
    size_t dist = (rand() % (distanceRange.second - distanceRange.first)) + distanceRange.first;
    _nextPoint = Vector2f(cos(angle), sin(angle)) * dist + _player.position();
    _nextPoint.x = std::max(std::min(static_cast<int>(_nextPoint.x), GameInfo::resolution().x), 18);
    _nextPoint.y = std::max(std::min(static_cast<int>(_nextPoint.y), GameInfo::resolution().y - 36), 18);
}
