#include "Player.hpp"
#include <math.h>
#include <iostream>
#include "LevelManager.hpp"
#include "Engine.hpp"

Player::Player()
    :Spaceship(_maxHp, _speed), _timeToShot(0),
      _bar(Vector2f(0, GameInfo::resolution().y-12), 26, 25, 27, Vector2i(13, 6), this), _lives(Vector2f(0, GameInfo::resolution().y - 35), this),
      _alive(true), _superShots(0)
{
    auto func = [](Bullet& a) -> void
    {
        a.setPosition(a.position() + Vector2f(cos(a.angle() - M_PI/2),
                                              sin(a.angle() - M_PI/2)) * _basicBulletSpeed * GameInfo::deltaTime());
    };
    auto func2 = [](Bullet& a) -> void
    {
        a.setPosition(a.position() + Vector2f(cos(a.angle() - M_PI/2),
                                  sin(a.angle() - M_PI/2)) * _superBulletSpeed * GameInfo::deltaTime());
        a.setAngle(a.angle() + M_PI);
    };

    setTexture(0);
    setId("player");
    setTextureSize(Vector2i(39, 39));
    _shutter.addBulletType(func, 10, Bullet::Type::Green);
    _shutter.addBulletType(func2, 100, Bullet::Type::SuperGreen);

    addCollider({Vector2f(0, -18), Vector2f(4, -9), Vector2f(10, 0), Vector2f(19, 4), Vector2f(7, 7), Vector2f(17, 17),
                 Vector2f(-17, 17), Vector2f(-7, 7), Vector2f(-19, 4), Vector2f(-10, 0), Vector2f(-4, -9)},
    {Collider::CollisionType::A}, {Collider::CollisionType::B});
    _bar.setActive(false);
    _lives.setActive(false);
}

void Player::reset()
{
    setPosition(Vector2f(GameInfo::resolution().x/2, GameInfo::resolution().y*2/3));
    setAngle(0);
    _hp = _maxHp;
    _lives.reset();
    _shield = 0;
    _superShots = false;
}

void Player::onFrame()
{
    move();
    _shutter.setPosition(position() + (Vector2f(cos(angle() - M_PI/2), sin(angle() - M_PI/2))) * 18);
    if (GameInfo::isKeyPressed(GameInfo::Key::UP) && _timeToShot <= 0)
    {
        if (_superShots == false)
        {
            _shutter.shot(0, angle());
            Engine::soundPlayer().playSound(1, 40);
        }
        else
        {
            _shutter.shot(1, angle());
            Engine::soundPlayer().playSound(5, 100);
        }
        _timeToShot = _shootSpeed;
    }
    if (_timeToShot > 0)
        _timeToShot -= GameInfo::deltaTime();

    if (isUntouchable())
    {
        if (shield())
            setTexture(3);
        else
            setTexture(2);
        _untouchable -= GameInfo::deltaTime();
    }
    else
    {
        if (shield())
            setTexture(1);
        else
            setTexture(0);
    }
}

void Player::onCollide(PhysicalObject* with)
{
    Spaceship* sp;
    if ((sp = dynamic_cast<Spaceship*>(with)))
    {
        Vector2f vector = sp->position() - position();
        int proby = 100;
        while (isCollideWith(sp) && --proby)
        {
            moveTo((position() - vector));
        }
        if (!proby)
            throw "too meny Player::onCollide";
    }
}

void Player::kill()
{
    _alive = false;
    LevelManager::Instance().endLevel();
}

bool Player::isAlive()
{
    return _alive;
}

void Player::addLife()
{
    _lives.addLife();
}

void Player::superShots()
{
    _superShots = true;
}

void Player::lifeLost()
{
    _superShots = false;
    setPosition(Vector2f(GameInfo::resolution().x / 2, GameInfo::resolution().y - 100));
    setAngle(0);
    makeUntouchable(_untouchableTime);
}

void Player::move()
{
    double trueSpeed = _speed;
    if (GameInfo::isKeyPressed(GameInfo::Key::RIGHT))
        setAngle(angle() + M_PI*GameInfo::deltaTime()*2);
    if (GameInfo::isKeyPressed(GameInfo::Key::LEFT))
        setAngle(angle() - M_PI*GameInfo::deltaTime()*2);
    if (GameInfo::isKeyPressed((GameInfo::Key::LSHIFT)))
        trueSpeed = _speed/2;

    if (GameInfo::isKeyPressed(GameInfo::Key::D))
        setPosition(position() + Vector2f(trueSpeed, 0) * GameInfo::deltaTime());
    if (GameInfo::isKeyPressed(GameInfo::Key::A))
        setPosition(position() - Vector2f(trueSpeed, 0) * GameInfo::deltaTime());
    if (GameInfo::isKeyPressed(GameInfo::Key::W))
        setPosition(position() - Vector2f(0, trueSpeed) * GameInfo::deltaTime());
    if (GameInfo::isKeyPressed(GameInfo::Key::S))
        setPosition(position() + Vector2f(0, trueSpeed) * GameInfo::deltaTime());
}

void Player::setActive(bool active)
{
    _alive = true;
    GameObject::setActive(active);
    _bar.setActive(active);
    _lives.setActive(active);
}
