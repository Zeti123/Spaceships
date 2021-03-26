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
    void move();
    double _timeToShot;
    HpBar _bar;
    Lives _lives;
    bool _alive;
    bool _superShots;
};

#endif // PLAYER_HPP
