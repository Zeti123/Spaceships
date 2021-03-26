#include "PhysicalObject.hpp"

std::vector<std::pair<PhysicalObject*, bool>> PhysicalObject::_allObjects;
std::vector<PhysicalObject::CollInfo> PhysicalObject::_allColliders[6];

PhysicalObject::PhysicalObject()
    :GameObject(), _positionInVector(_allObjects.size())
{
    _allObjects.push_back(std::make_pair(this, true));
}

PhysicalObject::PhysicalObject(const Position2D& position)
    :GameObject(position), _positionInVector(_allObjects.size())
{
    _allObjects.push_back(std::make_pair(this, true));
}

PhysicalObject::~PhysicalObject()
{
    _allObjects[_positionInVector].second = false;
    for (const auto& position: _positionsInCollidersVector)
    {
        _allColliders[position.x][static_cast<unsigned int>(position.y)].isAlive = false;
    }
}

void PhysicalObject::onCollide(PhysicalObject* with) {}

bool PhysicalObject::isCollideWith(PhysicalObject* with)
{
    for (auto& myCollider: _colliders)
    {
        myCollider.fixPosition(angle(), position());
        for (auto& withCollider: with->_colliders)
        {
            withCollider.fixPosition(with->angle(), with->position());
            if (myCollider.isCollideWith(withCollider))
                return true;
        }
    }
    return false;
}

void PhysicalObject::addCollider(const std::vector<Vector2f>& points,
                                 const std::vector<Collider::CollisionType>& collisionType,
                                 const std::vector<Collider::CollisionType>& collideWith)
{
    _colliders.push_back(Collider(points, collisionType, collideWith));

    Collider& col = _colliders.back();
    for (int i = 0; i < 6; i++)
    {
        if (col.collType(static_cast<Collider::CollisionType>(i)))
        {
            _positionsInCollidersVector.push_back(Vector2i(i, static_cast<int>(_allColliders[i].size())));
            _allColliders[i].push_back({_colliders.size()-1,
                                        this, static_cast<int>(_positionsInCollidersVector.size()-1), true});
        }
    }
}

void PhysicalObject::addCollider(std::vector<Vector2f>&& points,
                                 const std::vector<Collider::CollisionType>& collisionType,
                                 const std::vector<Collider::CollisionType>& collideWith)
{
    _colliders.push_back(Collider(std::move(points), collisionType, collideWith));

    Collider& col = _colliders.back();
    for (int i = 0; i < 6; i++)
    {
        if (col.collType(static_cast<Collider::CollisionType>(i)))
        {
            _positionsInCollidersVector.push_back(Vector2i(i, static_cast<int>(_allColliders[i].size())));
            _allColliders[i].push_back({_colliders.size()-1,
                                        this, static_cast<int>(_positionsInCollidersVector.size()-1), true});
        }
    }
}

const std::vector<std::pair<PhysicalObject*, bool>>& PhysicalObject::getObjects()
{
    return _allObjects;
}

const std::vector<PhysicalObject::CollInfo>& PhysicalObject::getColliders(Collider::CollisionType type)
{
    switch(type)
    {
    case Collider::CollisionType::A:
        return _allColliders[0];
    case Collider::CollisionType::B:
        return _allColliders[1];
    case Collider::CollisionType::C:
        return _allColliders[2];
    case Collider::CollisionType::D:
        return _allColliders[3];
    case Collider::CollisionType::E:
        return _allColliders[4];
    case Collider::CollisionType::F:
        return _allColliders[5];
    }
    throw "wrong collider type";
}

void PhysicalObject::clearVector()
{
    for (size_t i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < _allColliders[i].size(); j++)
        {
            if (!_allColliders[i][j].isAlive)
            {
                std::swap(_allColliders[i][j], _allColliders[i].back());
                _allColliders[i].pop_back();
                if (_allColliders[i][j].isAlive)
                {
                    size_t pos = static_cast<size_t>(_allColliders[i][j].posInVector);
                    _allColliders[i][j].object->_positionsInCollidersVector[pos] = Vector2i(i, j);
                }
                j--;
            }
        }
    }
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
