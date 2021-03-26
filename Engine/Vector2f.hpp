#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>

class Vector2f
{
public:
    Vector2f();
    Vector2f(const double& a, const double& b);
    double length() const;
    double squareLength() const;
    double x, y;
};

Vector2f operator+ (const Vector2f& a, const Vector2f& b);
Vector2f operator- (const Vector2f& a, const Vector2f& b);
Vector2f operator* (const Vector2f& a, double b);
Vector2f operator* (double b, const Vector2f& a);
void operator +=(Vector2f a, Vector2f b);
std::ostream& operator<<(std::ostream& a, Vector2f b);

#endif // VECTOR2_HPP
