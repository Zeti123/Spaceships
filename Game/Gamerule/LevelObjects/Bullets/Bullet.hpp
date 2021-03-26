#ifndef BULLET_HPP
#define BULLET_HPP

#include <functional>
#include "PhysicalObject.hpp"
#include "ILevelObject.hpp"

class Bullet : public PhysicalObject, public ILevelObject
{
public:
    enum class Type
    {
        Green,
        SuperGreen,
        Red,
        Rocket
    };

public:
    Bullet(std::function<void(Bullet& b)> nextStep,
           const Vector2f& pos, double angle, double lifeTime, Type type);
    void onFrame() override;
    void onCollide(PhysicalObject *with) override;
    void kill() override;
    bool isAlive() override;
    void onDestroy() override;
    bool blockLevel() override;

    double angle() const;
    double textureAngle() const;
    double currentLifeTime() const;

protected:
    class Animation : public GameObject, public ILevelObject
    {
    public:
        Animation(Vector2f position);
        void onFrame() override;
        void kill() override;
        bool isAlive() override;
        void onDestroy() override;
        bool blockLevel() override;

    private:
        double _time;
    };

    std::function<void(Bullet& b)> _nextStep;
    double _angle;
    double _lifeTime;
    double _currentLifeTime;
    Type _type;
    bool _alive;
};

#endif // BULLET_HPP
