#ifndef PHYSICALOBJECT_HPP
#define PHYSICALOBJECT_HPP

#include "GameObject.hpp"
#include "Collider.hpp"

class PhysicalObject : public GameObject
{
    friend class Engine;

public:
    PhysicalObject();
    PhysicalObject(const Position2D& position);
    virtual ~PhysicalObject();
    virtual void onCollide(PhysicalObject* with);
    bool isCollideWith(PhysicalObject* with);
    void addCollider(const std::vector<Vector2f>& pointsconst,
                     const std::vector<Collider::CollisionType>& collisionType = {Collider::CollisionType::A},
                     const std::vector<Collider::CollisionType>& collideWith = {Collider::CollisionType::A});
    void addCollider(std::vector<Vector2f>&& points,
                     const std::vector<Collider::CollisionType>& collisionType = {Collider::CollisionType::A},
                     const std::vector<Collider::CollisionType>& collideWith = {Collider::CollisionType::A});
private:
    struct CollInfo
    {
        size_t collider;
        PhysicalObject* object; // parent
        int posInVector;        // position in vector _positionsInCollidersVector
        bool isAlive;
    };
    static const std::vector<std::pair<PhysicalObject*, bool>>& getObjects();
    static const std::vector<CollInfo>& getColliders(Collider::CollisionType type);
    static void clearVector();
    static std::vector<std::pair<PhysicalObject*, bool>> _allObjects;
    static std::vector<CollInfo> _allColliders[6];

private:
    std::vector<Collider> _colliders;
    std::vector<Vector2i> _positionsInCollidersVector;
    size_t _positionInVector;
};

#endif // PHYSICALOBJECT_HPP
