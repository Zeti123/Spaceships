#ifndef POSITION2D_HPP
#define POSITION2D_HPP

#include "Vector2f.hpp"
#include "Vector2i.hpp"

class Position2D
{
public:
    Position2D();
    Position2D(const Vector2f& pos, const Vector2i& siz);
    const Vector2f& position() const;
    const Vector2i& size() const;

    void setPosition(const Vector2f& pos);
    void setSize(const Vector2i& siz);

private:
    Vector2f _position;
    Vector2i _size;
};

#endif // POSITION2D_HPP
