#include "GameObject.hpp"
#include <iostream>

std::vector<std::pair<GameObject*, bool>> GameObject::_allObjects;

GameObject::GameObject()
    :_position(), _id(""), _positionInVector(_allObjects.size()), _angle(0), _active(false)
{
    _allObjects.push_back(std::make_pair(this, true));
}

GameObject::GameObject(const Position2D& position)
    : _position(position), _id(""), _positionInVector(_allObjects.size()), _angle(0), _active(false)
{
    _allObjects.push_back(std::make_pair(this, true));
}

GameObject::~GameObject()
{
    _allObjects[_positionInVector].second = false;
}

void GameObject::addTexture(size_t textureID)
{
    _textures.push_back({Vector2f(0, 0), 0, textureID, Vector2f(1, 1), Vector2i(0, 0), true, std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(255, 255, 255, 255)});
}

void GameObject::addTexture(const Texture& texture)
{
    _textures.push_back(texture);
}

void GameObject::setTexture(size_t textureId, size_t textureNum)
{
    if (textureNum >= _textures.size())
        throw "there is no such texture";

    _textures[textureNum].textureID = textureId;
}

void GameObject::setSize(const Vector2i& siz)
{
    _position.setSize(siz);
}

void GameObject::setPosition(const Vector2f& pos)
{
    _position.setPosition(pos);
}

void GameObject::setId(const std::string &id)
{
    _id = id;
}

void GameObject::setAngle(double angle)
{
    _angle = angle;
}

void GameObject::setActive(bool active)
{
    _active = active;
}

const Vector2i& GameObject::size() const
{
    return _position.size();
}

const Vector2f& GameObject::position() const
{
    return _position.position();
}

const std::string& GameObject::id() const
{
    return _id;
}

double GameObject::textureID(size_t num) const
{
    if (num >= _textures.size())
        throw "there is no such texture";

    return _textures[num].textureID;
}

double GameObject::angle() const
{
    return _angle;
}

bool GameObject::isActive() const
{
    return _active;
}

const std::vector<std::pair<GameObject*, bool>>& GameObject::getObjects()
{
    return _allObjects;
}

void GameObject::clearVector()
{
    for (size_t i = 0; i < _allObjects.size(); i++)
    {
        if (_allObjects[i].second == false)
        {
            std::swap(_allObjects[i], _allObjects.back());
            if (_allObjects[i].second == true)
                _allObjects[i].first->_positionInVector = i;
            _allObjects.pop_back();
            i--;
        }
    }
}

GameObject::Texture& GameObject::texture(size_t num)
{
    if (num >= _textures.size())
        throw "there is no such texture";

    return _textures[num];
}
