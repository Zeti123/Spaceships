#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Spaceship.hpp"
#include "HpBar.hpp"
#include "Lives.hpp"
#include "SoundPlayer.hpp"

class Player : public Spaceship
{
public:
    Player();
    ~Player() = default;
    void onFrame() override;
    void onCollide(PhysicalObject* with) override;
    void kill() override;
    bool isAlive() override;
    void reset();
    void addLife();
    void superShots();
    void lifeLost();
    void setActive(bool active);

private:
    static constexpr size_t _maxHp = 100;
    static constexpr size_t _speed = 150;
    static constexpr size_t _bulletSpeed = 240;
    static constexpr double _shootSpeed = 0.15;
    static constexpr size_t _basicBulletSpeed = 400;
    static constexpr size_t _superBulletSpeed = 500;
    static constexpr double _untouchableTime = 5;

private:
    void move();
    double _timeToShot;
    HpBar _bar;
    Lives _lives;
    bool _alive;
    bool _superShots;
};

#endif // PLAYER_HPP
