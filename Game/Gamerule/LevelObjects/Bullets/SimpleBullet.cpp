#include <cmath>
#include "SimpleBullet.hpp"

SimpleBullet::SimpleBullet(Vector2f position, double angle, double speed, double lifeTime, Type type)
    :Bullet(nullptr, position, angle, lifeTime, type), _movingDirection(speed * cos(angle), speed * sin(angle)) {}

void SimpleBullet::onFrame()
{
    _currentLifeTime += GameInfo::deltaTime();
    setPosition(position() + _movingDirection * GameInfo::deltaTime());
}
