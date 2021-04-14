#include "BulletShutter.hpp"
#include "LevelManager.hpp"

void BulletShutter::addBulletType(std::function<void(Bullet& b)> func,
                                 double lifeTime, Bullet::Type color, size_t texture)
{
    _bulletTypes.push_back({func, lifeTime, color, texture});
}

void BulletShutter::shot(size_t bulletType, double angle)
{
    Bullet* bullet = new Bullet(_bulletTypes[bulletType].func, _position,
                                angle, _bulletTypes[bulletType].lifeTime, _bulletTypes[bulletType].color, _bulletTypes[bulletType].texture);
    LevelManager::Instance().addObject(bullet);
    bullet->setActive(true);
}

void BulletShutter::shotSimple(double angle, double speed, double lifeTime, Bullet::Type type)
{
    SimpleBullet* bullet = new SimpleBullet(_position, angle, speed, lifeTime, type);
    LevelManager::Instance().addObject(bullet);
    bullet->setActive(true);
}

void BulletShutter::setPosition(Vector2f position)
{
    _position = position;
}
