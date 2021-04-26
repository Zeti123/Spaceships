#ifndef ENEMY1_HPP
#define ENEMY1_HPP

#include "Spaceship.hpp"

class Enemy1 : public Spaceship
{
public:
    Enemy1(double angle);
    void onFrame() override;
    void kill() override;
    bool isAlive() override;

private:
    static constexpr size_t _maxHp = 100;
    static constexpr size_t _speed = 100;
    static constexpr double _shotSpeed = 0.75;
    static constexpr double _bulletSpeed = 240;

    Vector2f _direction;
    double _shotTimer;
};

#endif // ENEMY2_HPP
