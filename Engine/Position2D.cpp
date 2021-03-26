#include "Position2D.hpp"

Position2D::Position2D()
    :_position(), _size()
{}

Position2D::Position2D(const Vector2f& pos, const Vector2i& siz)
    :_position(pos), _size(siz) {}

const Vector2f& Position2D::position() const
{
    return _position;
}

const Vector2i& Position2D::size() const
{
    return _size;
}

void Position2D::setPosition(const Vector2f& pos)
{
    _position.x = pos.x;
    _position.y = pos.y;
}

void Position2D::setSize(const Vector2i& siz)
{
    _size.x = siz.x;
    _size.y = siz.y;
}

