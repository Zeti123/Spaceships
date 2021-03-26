#ifndef ENEMY5_HPP
#define ENEMY5_HPP


#include "Spaceship.hpp"
#include "Player.hpp"
#include "Enemy4.hpp"

class Enemy5: public Spaceship
{
public:
    Enemy5(std::function<Vector2f(const Enemy5& obj)> moving);
    void onFrame() override;
    void kill() override;
    bool isAlive() override;
    void onDestroy() override;

    void deadChild(Enemy4* child);
    void spawnNewChild();
    double currentLifeTime() const;

private:
    static constexpr size_t _maxHp = 400;
    static constexpr size_t _speed = 150;
    static constexpr double _shotSpeed = 3;
    static constexpr double _respawnTime = 10;
    static constexpr size_t _maxChildrenNumber = 4;
    static constexpr size_t _bulletSpeed = 240;

    size_t _aliveChildrenNumber;
    Enemy4* _child[_maxChildrenNumber];
    double _respawnTimer;
    double _currentLifeTime;
    double _shotTimer;
    std::function<Vector2f(const Enemy5& obj)> _moving;

};

#endif // ENEMY5_HPP
