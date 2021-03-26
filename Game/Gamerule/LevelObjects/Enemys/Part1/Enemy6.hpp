#ifndef ENEMY6_HPP
#define ENEMY6_HPP

#include "Spaceship.hpp"

class Enemy6: public Spaceship
{
public:
    Enemy6(std::function<Vector2f(const Enemy6& obj)> moving);
    void onFrame() override;
    void kill() override;
    bool isAlive() override;

    double currentLifeTime() const;

private:
    static constexpr size_t _maxHp = 300;
    static constexpr size_t _speed = 150;
    static constexpr std::array<double, 4> _shotsSec = std::array<double, 4>{0.5, 1, 1.5, 3};
    static constexpr double _bulletSpeed = 240;
    static constexpr double _rocketSpeed = 500;

    std::function<Vector2f(const Enemy6& obj)> _moving;
    double _shotTimer;
    double _currentLifeTime;
    uint8_t _shotSeq;
};

#endif // ENEMY6_HPP
