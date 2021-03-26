#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "Vector2f.hpp"
#include "vector"

class Collider
{
public:
    enum class CollisionType
    {
        A, B, C, D, E, F
    };
    static constexpr size_t CollisionTypesNumber = 6;

public:
    Collider(const std::vector<Vector2f>& points, const std::vector<CollisionType>& collisionType = {CollisionType::A},
             const std::vector<CollisionType>& collideWith = {CollisionType::A});
    Collider(std::vector<Vector2f>&& points, const std::vector<CollisionType>& collisionType = {CollisionType::A},
             const std::vector<CollisionType>& collideWith = {CollisionType::A});
    void fixPosition(double angle, Vector2f position);

    inline bool collType(CollisionType type) const {return _collisionTypeMask & (1<<static_cast<int>(type));}
    inline bool collWith(CollisionType type) const {return _collideWithMask & (1<<static_cast<int>(type));}
    bool isCollideWith(const Collider& collider) const;
    double longestSquare() const;
    const std::vector<Vector2f>& getPoints() const;

private:
    bool isIntersect(Vector2f A, Vector2f B, Vector2f C, Vector2f D) const;
    inline double vectorProduct(Vector2f X, Vector2f Y, Vector2f Z) const
        {return  (Z.x - X.x)*(Y.y - X.y) - (Y.x - X.x)*(Z.y - X.y);}

    std::vector<Vector2f> _points;
    std::vector<Vector2f> _fixedPoints;
    size_t _collisionTypeMask;
    size_t _collideWithMask;
    double _longest;
};

#endif // COLLIDER_HPP
