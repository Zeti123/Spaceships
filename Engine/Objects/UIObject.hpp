#ifndef UIOBJECT_HPP
#define UIOBJECT_HPP

#include "GameObject.hpp"

class UIObject : public GameObject
{
    friend class Engine;

public:
    UIObject();
    UIObject(const Position2D& pos);
    virtual ~UIObject();
    virtual void onStartDrag() = 0;
    virtual void onDrag() = 0;
    virtual void onEndDrag() = 0;
    virtual void onMouseDown() = 0;
    virtual void onMouseClick() = 0;
    virtual void onMouseUp() = 0;


private:
    static const std::vector<std::pair<UIObject*, bool>>& getObjects();
    static void clearVector();

    static std::vector<std::pair<UIObject*, bool>> _allObjects;

private:
    size_t _positionInVector;
    bool _dragged;
    bool _clicked;
};

#endif // UIOBJECT_HPP
