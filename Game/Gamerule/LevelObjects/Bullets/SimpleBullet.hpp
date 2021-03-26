#ifndef SIMPLEBULLET_HPP
#define SIMPLEBULLET_HPP

#include "Bullet.hpp"

class SimpleBullet : public Bullet
{
public:
    SimpleBullet(Vector2f position, double angle, double speed, double lifeTime, Type type);
    void onFrame() final;

private:
    Vector2f _movingDirection;
};

#endif // SIMPLEBULLET_HPP
