#include "GameInfo.hpp"

const Vector2i& GameInfo::resolution()
{
    return _resolution;
}

const Vector2i& GameInfo::mousePosition()
{
    return _mousePosition;
}

bool GameInfo::isKeyPressed(Key key)
{
    return _keyStatusMask & static_cast<int>(key);
}

double GameInfo::_deltaTime;
Vector2i GameInfo::_resolution;
int GameInfo::_keyStatusMask;
Vector2i GameInfo::_mousePosition;
