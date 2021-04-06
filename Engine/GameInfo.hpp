#ifndef GAMEINFO_HPP
#define GAMEINFO_HPP

#include "Vector2i.hpp"

class GameInfo
{
    friend class Engine;

public:
    enum class Key
    {
        RIGHT = 1 << 0,
        LEFT = 1 << 1,
        UP = 1 << 2,
        DOWN = 1 << 3,
        D = 1 << 4,
        A = 1 << 5,
        W = 1 << 6,
        S = 1 << 7,
        SPACE = 1 << 8,
        ESC = 1 << 9,
        LSHIFT = 1 << 10
    };

    inline static double deltaTime() { return _deltaTime;}
    static const Vector2i& resolution();
    static const Vector2i& mousePosition();
    static bool isKeyPressed(Key key);

private:
    static double _deltaTime;
    static Vector2i _resolution;
    static Vector2i _mousePosition;
    static int _keyStatusMask;

};

#endif // GAMEINFO_HPP
