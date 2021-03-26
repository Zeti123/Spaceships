#include "Enemy6.hpp"
#include "Engine.hpp"
#include <cmath>

constexpr std::array<double, 4> Enemy6::_shotsSec;

Enemy6::Enemy6(std::function<Vector2f(const Enemy6& obj)> moving)
    :Spaceship(_maxHp, _speed), _moving(moving), _shotTimer(0), _currentLifeTime(0), _shotSeq(0)
{
    setTexture(14);
    setId("enemy");
    setTextureSize(Vector2i(50, 50));

    addCollider({Vector2f(-25, -25), Vector2f(-25, 25), Vector2f(25, 25), Vector2f(25, -25)}, {Collider::CollisionType::B}, {});

    auto player = Engine::Instance().findObjectById("player");
    auto func = [player](Bullet& b)
    {
        auto pos = b.position();
        if (b.currentLifeTime() < 1.5)
        {
            b.setAngle(atan2(player->position().y - b.position().y, player->position().x - b.position().x) + M_PI/2);
            b.setPosition(Vector2f(cos(b.angle()), sin(b.angle())) * (_rocketSpeed/2 * (1 - b.currentLifeTime()/1.5)) * GameInfo::deltaTime() + pos);
        }
        else
            b.setPosition(Vector2f(cos(b.textureAngle() - M_PI/2), sin(b.textureAngle() - M_PI/2)) * _rocketSpeed * GameInfo::deltaTime() + pos);
    };

    _shutter.addBulletType(func, 100, Bullet::Type::Rocket);
}

void Enemy6::onFrame()
{
    _currentLifeTime += GameInfo::deltaTime();
    _shotTimer += GameInfo::deltaTime();

    _shutter.setPosition(Vector2f(cos(angle()), sin(angle())) * (50/2) + position());
    if (_shotTimer >= _shotsSec[_shotSeq])
    {
        if (_shotSeq <= 2)
            _shutter.shotSimple(angle(), _bulletSpeed, 1000000.0, Bullet::Type::Red);
        else
            _shutter.shot(0, angle());

        _shotSeq++;
        if (_shotSeq >= _shotsSec.size())
        {
            _shotSeq = 0;
            _shotTimer = 0;
        }
    }

    Vector2f nextPos = _moving(*this);
    if (nextPos.x != position().x && nextPos.y != position().y)
    {
        float movingAngle = atan2(nextPos.y - position().y, nextPos.x - position().x);
        setAngle(movingAngle);
    }
    moveTo(nextPos);
}

void Enemy6::kill()
{
    _hp = 0;
}

bool Enemy6::isAlive()
{
    return _hp > 0;
}

double Enemy6::currentLifeTime() const
{
    return _currentLifeTime;
}
