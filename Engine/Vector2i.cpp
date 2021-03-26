#include "Vector2i.hpp"
#include "Vector2f.hpp"

Vector2i::Vector2i()
    :x(0), y(0) {}

Vector2i::Vector2i(int a, int b)
    :x(a), y(b) {}

Vector2f Vector2i::toV2f() const
{
    return Vector2f(x, y);
}

Vector2i operator+ (const Vector2i& a, const Vector2i& b)
{
    return {a.x + b.x, a.y + b.y};
}

Vector2i operator- (const Vector2i& a, const Vector2i& b)
{
    return {a.x - b.x, a.y - b.y};
}
