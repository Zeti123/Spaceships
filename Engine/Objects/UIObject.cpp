#include "UIObject.hpp"

std::vector<std::pair<UIObject*, bool>> UIObject::_allObjects;

UIObject::UIObject()
    :GameObject(), _positionInVector(_allObjects.size()), _dragged(0), _clicked(0)
{
    _allObjects.push_back(std::make_pair(this, true));
}

UIObject::UIObject(const Position2D& position)
    :GameObject(position), _positionInVector(_allObjects.size())
{
    _allObjects.push_back(std::make_pair(this, true));
}

UIObject::~UIObject()
{
    _allObjects[_positionInVector].second = false;
}

const std::vector<std::pair<UIObject*, bool>>& UIObject::getObjects()
{
    return _allObjects;
}

void UIObject::clearVector()
{
    for (size_t i = 0; i < _allObjects.size(); i++)
    {
        if (_allObjects[i].second == false)
        {
            std::swap(_allObjects[i], _allObjects[_allObjects.size() - 1]);
            _allObjects[i].first->_positionInVector = i;
            _allObjects.pop_back();
            i--;
        }
    }
}
