#ifndef ENEMY3_HPP
#define ENEMY3_HPP

#include "Spaceship.hpp"

class Enemy3 : public Spaceship
{
public:
    Enemy3(std::function<Vector2f(const Enemy3& obj)> moving);
    void onFrame() override;
    void kill() override;
    bool isAlive() override;
    void resetTime();

    double currentLifeTime() const;

private:
    static constexpr size_t _maxHp = 300;
    static constexpr size_t _speed = 75;
    static constexpr double _shotSpeed = 1;

    std::function<Vector2f(const Enemy3& obj)> _moving;
    double _shotTimer;
    double _rotationSpeed;
    double _currentLifeTime;
};
#endif // ENEMY3_HPP
