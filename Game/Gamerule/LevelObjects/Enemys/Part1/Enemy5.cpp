#include "Enemy5.hpp"
#include "LevelManager.hpp"
#include <cmath>

Enemy5::Enemy5(std::function<Vector2f(const Enemy5& obj)> moving)
    :Spaceship(_maxHp, _speed), _aliveChildrenNumber(0), _child{nullptr, nullptr, nullptr, nullptr},
     _respawnTimer(0), _currentLifeTime(0), _shotTimer(0), _moving(moving)
{
    setTexture(13);
    setId("enemy");
    setTextureSize(Vector2i(39, 39));

    addCollider({Vector2f(-20, 0), Vector2f(2, 20), Vector2f(-19, 20), Vector2f(14, 15),
                 Vector2f(14, -15), Vector2f(-19, -20), Vector2f(2, -20)},
    {Collider::CollisionType::B}, {});
}

void Enemy5::onFrame()
{
    _currentLifeTime += GameInfo::deltaTime();
    Vector2f nextPos = _moving(*this);
    if (nextPos.x != position().x || nextPos.y != position().y)
    {
        float movingAngle = atan2(nextPos.y - position().y, nextPos.x - position().x);
        setAngle(movingAngle);
    }

    moveTo(nextPos);
    if(_shotTimer >= _shotSpeed)
    {
        _shotTimer = 0.0;
        _shutter.setPosition(position() + Vector2f(25.0 * cos(angle() - 0.2 * M_PI), 25.0 * sin(angle() - 0.2*M_PI)));
        _shutter.shotSimple(angle(), _bulletSpeed, 1000000.0, Bullet::Type::Red);

        _shutter.setPosition(position() + Vector2f(25.0 * cos(angle() + 0.2*M_PI), 25.0 * sin(angle() + 0.2*M_PI)));
        _shutter.shotSimple(angle(), _bulletSpeed, 1000000.0, Bullet::Type::Red);
    }
    _shotTimer += GameInfo::deltaTime();
    if (_aliveChildrenNumber < _maxChildrenNumber)
    {
        _respawnTimer += GameInfo::deltaTime();

        if (_respawnTimer >= _respawnTime)
            spawnNewChild();
    }
}

void Enemy5::kill()
{
    _hp = 0;
}

bool Enemy5::isAlive()
{
    return (_hp > 0);
}

void Enemy5::onDestroy()
{
    for (size_t i = 0; i < _maxChildrenNumber; i++)
    {
        if (_child[i] != nullptr)
        {
            _child[i]->deadHost();
        }
    }
    Spaceship::onDestroy();
}

void Enemy5::deadChild(Enemy4* child)
{
    for (size_t i = 0; i < _maxChildrenNumber; i++)
    {
        if (child == _child[i])
        {
            _child[i] = nullptr;
            _aliveChildrenNumber--;
            return;
        }
    }
    throw "there is no dead child";
}

void Enemy5::spawnNewChild()
{
    for (size_t i = 0; i < _maxChildrenNumber; i++)
    {
        if (_child[i] == nullptr)
        {
            _child[i] = new Enemy4(this);
            _child[i]->setActive(true);
            LevelManager::Instance().addObject(_child[i]);
            _aliveChildrenNumber++;
            _respawnTimer = 0;
            return;
        }
    }
    throw "cannot spawn more children";
}

double Enemy5::currentLifeTime() const
{
    return _currentLifeTime;
}
