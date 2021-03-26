#ifndef PICKUP_HPP
#define PICKUP_HPP

#include "PhysicalObject.hpp"
#include "ILevelObject.hpp"

class PickUp : public PhysicalObject, public ILevelObject
{
public:
    enum class Type
    {
        Hp,
        Life,
        Shild,
        SuperShots
    };

    PickUp(Vector2f position);
    PickUp(Vector2f position, Type type);
    void onFrame() override;
    void onCollide(PhysicalObject* with) override;
    void kill() override;
    bool isAlive() override;
    void onDestroy() override;
    bool blockLevel() override;

private:
    Type _type;
    bool _alive;
};

#endif // PICKUP_HPP
