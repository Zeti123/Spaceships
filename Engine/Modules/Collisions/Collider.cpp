#include "Collider.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

Collider::Collider(const std::vector<Vector2f>& points, const std::vector<CollisionType>& collisionType,
                   const std::vector<CollisionType>& collideWith)
    :_points(points), _fixedPoints(points), _collisionTypeMask(0), _collideWithMask(0), _longest(0)
{
    if(_points.size() < 2)
        throw "collider must have at least 2 points";

    for (const auto& point: _points)
        _longest = std::max(_longest, point.squareLength());

    for (const auto& type: collisionType)
        _collisionTypeMask |= 1<<(static_cast<int>(type));

    for (const auto& type: collideWith)
        _collideWithMask |= 1<<(static_cast<int>(type));
}

Collider::Collider(std::vector<Vector2f>&& points, const std::vector<CollisionType>& collisionType,
                   const std::vector<CollisionType>& collideWith)
    :_points(points), _fixedPoints(std::move(points)), _collisionTypeMask(0),
     _collideWithMask(0), _longest(0)
{
    if(_points.size() < 2)
        throw "collider must have at least 2 points";

    for (const auto& point: _points)
        _longest = std::max(_longest, point.squareLength());

    for (const auto& type: collisionType)
        _collisionTypeMask |= 1<<(static_cast<int>(type));

    for (const auto& type: collideWith)
        _collideWithMask |= 1<<(static_cast<int>(type));
}

void Collider::fixPosition(double angle, Vector2f position)
{
    for (size_t i = 0; i < _fixedPoints.size(); i++)
    {
        const auto co = std::cos(angle);
        const auto si = std::sin(angle);
        _fixedPoints[i] = Vector2f(_points[i].x * co - _points[i].y * si,
                                   _points[i].x * si + _points[i].y * co) + position;
    }
}

bool Collider::isCollideWith(const Collider& collider) const
{
    for (size_t i = 0; i < _points.size(); i++)
    {
        for (size_t j = 0; j < collider._points.size(); j++)
        {
            size_t siz = _points.size();
            size_t siz2 = collider._points.size();
            if (isIntersect(_fixedPoints[i], _fixedPoints[(i+1)%siz],
                            collider._fixedPoints[j], collider._fixedPoints[(j+1)%siz2]))
                return true;
        }
    }
    return false;
}

double Collider::longestSquare() const
{
    return _longest;
}

const std::vector<Vector2f>& Collider::getPoints() const
{
    return _fixedPoints;
}

bool Collider::isIntersect(Vector2f A, Vector2f B, Vector2f C, Vector2f D) const
{
    double v1 = vectorProduct(C, D, A);
    double v2 = vectorProduct(C, D, B);
    double v3 = vectorProduct(A, B, C);
    double v4 = vectorProduct(A, B, D);

    if(((v1 > 0 && v2 < 0) || (v1 < 0 && v2 > 0)) && ((v3 > 0 && v4 < 0) || (v3 < 0 && v4 > 0)))
        return 1;
    return 0;
}

