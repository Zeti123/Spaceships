#ifndef BULLETSHUTTER_HPP
#define BULLETSHUTTER_HPP

#include <functional>
#include "Vector2f.hpp"
#include "Bullet.hpp"
#include "SimpleBullet.hpp"

class BulletShutter
{
public:
    void addBulletType(std::function<void(Bullet& b)> func,
                       double lifeTime, Bullet::Type col);
    void shot(size_t bulletType, double angle);
    void shotSimple(double angle, double speed, double lifeTime, Bullet::Type type);
    void setPosition(Vector2f position);

private:
    struct BulletType
    {
        std::function<void(Bullet& b)> func;
        double lifeTime;
        Bullet::Type color;
    };
    Vector2f _position;
    std::vector<BulletType> _bulletTypes;
};

#endif // BULLETSHUTTER_HPP
