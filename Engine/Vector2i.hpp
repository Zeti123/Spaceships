#ifndef VECTOR2I_HPP
#define VECTOR2I_HPP

class Vector2f;

class Vector2i
{
public:
    Vector2i();
    Vector2i(int a, int b);
    Vector2f toV2f() const;
    int x, y;
};

Vector2i operator+ (const Vector2i& a, const Vector2i& b);
Vector2i operator- (const Vector2i& a, const Vector2i& b);

#endif // VECTOR2I_HPP
