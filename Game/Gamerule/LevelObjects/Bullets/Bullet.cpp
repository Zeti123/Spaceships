#include "Bullet.hpp"
#include "GameInfo.hpp"
#include "LevelManager.hpp"
#include "Engine.hpp"

#include <iostream>
#include "Spaceship.hpp"

Bullet::Bullet(std::function<void(Bullet& b)> nextStep,
               const Vector2f& pos, double angle, double lifeTime, Type type, size_t tex)
    : PhysicalObject(Position2D(pos, Vector2i(10, 10))), _nextStep(nextStep), _angle(angle), _lifeTime(lifeTime),
      _currentLifeTime(0), _type(type), _alive(true)
{
    setId("bullet");


    if (_type == Type::Red)
        addCollider({Vector2f(5, 0), Vector2f(0, -5), Vector2f(-5, 0), Vector2f(0, 5)},
                    {}, {Collider::CollisionType::A});

    if (_type == Type::Green)
        addCollider({Vector2f(5, 0), Vector2f(0, -5), Vector2f(-5, 0), Vector2f(0, 5)},
                    {}, {Collider::CollisionType::B});

    if (_type == Type::SuperGreen)
        addCollider({Vector2f(0, -8.5), Vector2f(-8.5, 0.5), Vector2f(-8.5, 3.5), Vector2f(-2.5, 8.5),
                     Vector2f(2.5, 8.5), Vector2f(8.5, 3.5), Vector2f(8.5, 0.5)}, {}, {Collider::CollisionType::B});

    if (_type == Type::Rocket)
        addCollider({Vector2f(-5.5, -12.5), Vector2f(-5.5, 12.5), Vector2f(5.5, 12.5), Vector2f(5.5, -12.5)}, {}, {Collider::CollisionType::A});

    switch (_type)
    {
    case Type::Green:
        addTexture(4);
        texture(0).offsetPosition = Vector2f(-5, -5);
        break;
    case Type::SuperGreen:
        addTexture(5);
        texture(0).offsetPosition = Vector2f(-8.5, -8.5);
        break;
    case Type::Red:
        addTexture(tex);
        texture(0).offsetPosition = Vector2f(-5, -5);
        break;
    case Type::Rocket:
        addTexture(7);
        texture(0).offsetPosition = Vector2f(-5.5, -12.5);
    }
}

void Bullet::onFrame()
{
    _currentLifeTime += GameInfo::deltaTime();
    _nextStep(*this);
}

void Bullet::onCollide(PhysicalObject *with)
{
    if (with->id() == "enemy" && (_type == Type::Green))
    {
        dynamic_cast<Spaceship*>(with)->takeDamage(10);
        _alive = false;
    }
    else if (with->id() == "enemy" && _type == Type::SuperGreen)
    {
        dynamic_cast<Spaceship*>(with)->takeDamage(15);
        _alive = false;
    }
    else if (with->id() == "player" && (_type == Type::Red))
    {
        dynamic_cast<Spaceship*>(with)->takeDamage(20);
        _alive = false;
    }
    else if (with->id() == "player" && (_type == Type::Rocket))
    {
        dynamic_cast<Spaceship*>(with)->takeDamage(50);
        _alive = false;
    }
    if (!_alive)
    {
        Engine::soundPlayer().playSound(0, 100);
        LevelManager::Instance().addObject(new Bullet::Animation(position()));
    }
}

void Bullet::kill()
{
    _alive = false;
}

bool Bullet::isAlive()
{
    const Vector2f& pos = position();
    if (pos.x > -10 && pos.y > -10 && pos.x < GameInfo::resolution().x && pos.y < GameInfo::resolution().y &&
        _alive && _lifeTime - _currentLifeTime > 0)
        return true;
    return false;
}

void Bullet::onDestroy(){}

bool Bullet::blockLevel()
{
    return false;
}

double Bullet::angle() const
{
    return _angle;
}

double Bullet::textureAngle() const
{
    return GameObject::angle();
}

double Bullet::currentLifeTime() const
{
    return _currentLifeTime;
}

Bullet::Animation::Animation(Vector2f position)
    :_time(0.0)
{
    setPosition(position);
    addTexture(8);
    texture(0).offsetPosition = Vector2f(-9, -9);
    texture(0).textureScale = Vector2f(1.0/5, 1.0);
    setActive(true);
}

void Bullet::Animation::onFrame()
{
    _time += GameInfo::deltaTime();
    if (_time < 0.25)
        texture(0).textureOffset = Vector2i(18 * static_cast<int>(_time/0.05), 0);
}

void Bullet::Animation::kill() {}

bool Bullet::Animation::isAlive()
{
    return _time < 0.05*5;
}

void Bullet::Animation::onDestroy(){}

bool Bullet::Animation::blockLevel()
{
    return false;
}
