#ifndef ENEMY2_HPP
#define ENEMY2_HPP

#include "Spaceship.hpp"

class Enemy2 : public Spaceship
{
public:
    Enemy2(std::function<Vector2f(const Enemy2& obj)> moving);
    void onFrame() override;
    void kill() override;
    bool isAlive() override;
    void resetTime();

    double currentLifeTime() const;

private:
    static constexpr size_t _maxHp = 250;
    static constexpr size_t _speed = 150;
    static constexpr double _shotSpeed = 1.5;
    static constexpr double _bulletSpeed = 240;

    std::function<Vector2f(const Enemy2& obj)> _moving;
    double _shotTimer;
    double _currentLifeTime;
};

#endif // ENEMY_HPP
