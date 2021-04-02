#include "PickUp.hpp"
#include "Player.hpp"
#include "Engine.hpp"

PickUp::PickUp(Vector2f position)
    :PhysicalObject(), _alive(true)
{
    setActive(true);
    _type = static_cast<Type>(rand()%4);
    setPosition(position);
    addCollider({Vector2f(-11, -10), Vector2f(11, -10),Vector2f(11, 10),Vector2f(-11, 10)}, {});
    switch (_type)
    {
    case Type::Hp:
        addTexture(19);
        break;

    case Type::Life:
        addTexture(20);
        break;

    case Type::Shild:
        addTexture(21);
        break;

    case Type::SuperShots:
        addTexture(22);
        break;
    }
    texture(0).offsetPosition = Vector2f(-11, -10);
    texture(0).visible = true;
}

PickUp::PickUp(Vector2f position, Type type)
    :PhysicalObject(), _type(type)
{
    setActive(true);
    setPosition(position);
    addCollider({Vector2f(-11, -10), Vector2f(11, -10),Vector2f(11, 10),Vector2f(-11, 10)});
    switch (_type)
    {
    case Type::Hp:
        addTexture(20);
        break;

    case Type::Life:
        addTexture(21);
        break;

    case Type::Shild:
        addTexture(22);
        break;

    case Type::SuperShots:
        addTexture(23);
        break;
    }
    texture(0).visible = true;
}

void PickUp::onFrame()
{
    setPosition(position() + Vector2f(0, 30)*GameInfo::deltaTime());
    if (position().y - 10 > GameInfo::resolution().y)
        kill();
}

void PickUp::onCollide(PhysicalObject* with)
{
    Player* player;
    if ((player = dynamic_cast<Player*>(with)))
    {
        switch(_type)
        {
        case Type::Hp:
            player->refillHp();
            Engine::soundPlayer().playSound(2, 80);
            break;

        case Type::Life:
            player->addLife();
            Engine::soundPlayer().playSound(3, 80);
            break;

        case Type::Shild:
            player->addShield();
            Engine::soundPlayer().playSound(4, 80);
            break;

        case Type::SuperShots:
            player->superShots();
            break;
        }
        kill();
    }
}

void PickUp::kill()
{
    _alive = false;
}

bool PickUp::isAlive()
{
    return _alive;
}

void PickUp::onDestroy(){}

bool PickUp::blockLevel(){return true;}
