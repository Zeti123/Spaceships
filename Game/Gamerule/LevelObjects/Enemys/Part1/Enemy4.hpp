#ifndef ENEMY4_HPP
#define ENEMY4_HPP

#include "Spaceship.hpp"
#include "Player.hpp"

class Enemy5;

class Enemy4: public Spaceship
{
public:
    Enemy4(Enemy5* host);
    void onFrame() override;
    void kill() override;
    bool isAlive() override;
    void onDestroy() override;
    void deadHost();

private:
    static constexpr size_t _maxHp = 30;
    static constexpr size_t _speed = 250;
    static constexpr double _shotSpeed = 2;
    static constexpr std::pair<int, int> distanceRange = {200, 400};
    static constexpr size_t _bulletSpeed = 240;

    void nextPoint();
    Player& _player;
    Vector2f _nextPoint;
    double _shotTimer;
    Enemy5* _host;
    bool _isHostAlive;
};

#endif // ENEMY4_HPP
