#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "PhysicalObject.hpp"
#include "BulletShutter.hpp"
#include "ILevelObject.hpp"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class Spaceship : public PhysicalObject, public ILevelObject
{   
public:
    Spaceship(int maxHp, int speed);
    void onDestroy() override;
    bool blockLevel() override;
    bool moveTo(const Vector2f& position);
    void takeDamage(int damage);
    void setTextureSize(Vector2i siz);
    void makeUntouchable(double time);
    void refillHp();
    void addShield();

    int hp() const;
    int maxHp() const;
    int shield() const;
    bool isUntouchable() const;



protected:
    BulletShutter _shutter;
    double _untouchable;
    int _maxHp;
    int _hp;
    int _shield;
    int _speed;
};

#endif // SPACESHIP_HPP
