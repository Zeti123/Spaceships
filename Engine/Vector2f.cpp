#include "Vector2f.hpp"

#include <math.h>

Vector2f::Vector2f()
    :x(0.0), y(0.0) {}

Vector2f::Vector2f(const double& a, const double& b)
    :x(a), y(b) {}

double Vector2f::length() const
{
    return std::sqrt(x*x+y*y);
}

double Vector2f::squareLength() const
{
    return x*x + y*y;
}

Vector2f operator+ (const Vector2f& a, const Vector2f& b)
{
    return {a.x + b.x, a.y + b.y};
}

Vector2f operator- (const Vector2f& a, const Vector2f& b)
{
    return {a.x - b.x, a.y - b.y};
}

Vector2f operator* (const Vector2f& a, double b)
{
    return Vector2f(a.x * b, a.y * b);
}

Vector2f operator* (double b, const Vector2f& a)
{
    return Vector2f(a.x * b, a.y * b);
}

void operator +=(Vector2f a, Vector2f b)
{
    a.x += b.x;
    a.y += b.y;
}

std::ostream& operator<<(std::ostream& a, Vector2f b)
{
    a<<"("<<b.x<<" "<<b.y<<") ";
    return a;
}

