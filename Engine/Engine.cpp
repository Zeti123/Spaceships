#include "Engine.hpp"
#include "PhysicalObject.hpp"
#include "UIObject.hpp"
#include <iostream>
#include "MainClass.hpp"

Engine* Engine::_instance = nullptr;

Engine::Engine()
    :_window(new sf::RenderWindow(sf::VideoMode(1280, 720), "Game")), _renderer(), _timeRate(1)
{
    _window->setFramerateLimit(240);
    GameInfo::_deltaTime = 1.0/240;
    GameInfo::_resolution = Vector2i(1280, 720);
    GameInfo::_keyStatusMask = 0;
    GameInfo::_mousePosition = Vector2i(0, 0);
    std::srand(std::time(nullptr));
}

using std::cout;
using std::endl;

Engine& Engine::Instance()
{
    if (_instance == nullptr)
        _instance = new Engine();
    return *_instance;
}

SoundPlayer& Engine::soundPlayer()
{
    return Engine::Instance()._player;
}

void Engine::loadTextures(const std::vector<std::string>& textures)
{
    _renderer.loadTextures(textures);
}

void Engine::loadSounds(const std::vector<std::string>& sounds)
{
    _player.loadSounds(sounds);
}

GameObject* Engine::findObjectById(const std::string& id)
{
    const auto& objects = GameObject::getObjects();
    for (auto& obj : objects)
    {
        if (obj.first->id() == id)
            return obj.first;
    }
    return nullptr;
}

bool Engine::nextFrame()
{
    _window->clear();
    updateGameInfo();
    checkEvents();
    checkCollisions();
    updateUI();
    const auto& objects = GameObject::getObjects();
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (!objects[i].first->isActive()) continue;
        if (objects[i].second == true)
            objects[i].first->onFrame();
        if (objects[i].second == true)
            for (const auto& texture : objects[i].first->_textures)
                if (texture.visible == true)
                {
                    sf::Color c = sf::Color(std::get<0>(texture.color), std::get<1>(texture.color), std::get<2>(texture.color), std::get<3>(texture.color));
                    _renderer.render(Renderer::RenderSettings(_window, objects[i].first->position(), texture.offsetPosition, texture.textureID,
                                     objects[i].first->angle(), texture.angle, texture.textureOffset, texture.textureScale, sf::Color(c)));
                }
    }
    GameObject::clearVector();

    if (MainClass::_instance != nullptr)
        MainClass::_instance->onFrame();

    _window->display();
    return _window->isOpen();
}

void Engine::setTimeRate(double timeRate)
{
    _timeRate = timeRate;
}

void Engine::exit()
{
    if (MainClass::_instance != nullptr)
        MainClass::_instance->onExit();
    _window->close();
}

void Engine::checkEvents()
{
    sf::Event event;
    while (_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            exit();
        }
    }
}

// simple check throws out cases where it is easy to say that the collision is not happening
static inline bool isCollisionPossible(Vector2f obj1Pos, Vector2f obj2Pos, const Collider& col1, const Collider& col2)
{
    Vector2f o(obj1Pos - obj2Pos);
    return (col1.longestSquare() + col2.longestSquare() >= o.squareLength());
}

void Engine::checkCollisionsWithType(size_t objIndex, Collider& col, Collider::CollisionType type) const
{
    const auto& objects = PhysicalObject::getObjects();
    auto& obj1 = objects[objIndex];
    const auto& colliders = PhysicalObject::getColliders(static_cast<Collider::CollisionType>(type));
    for (const auto& collInfo: colliders)
    {
        if (!(collInfo.isAlive && obj1.second && collInfo.object->isActive()) || obj1.first == collInfo.object)
            continue;

        auto& collider = collInfo.object->_colliders[collInfo.collider];
        if (!isCollisionPossible(obj1.first->position(), collInfo.object->position(), col, collider))
            continue;

        collider.fixPosition(collInfo.object->angle(), collInfo.object->position());
        col.fixPosition(obj1.first->angle(), obj1.first->position());
        if (col.isCollideWith(collider))
        {
            obj1.first->onCollide(collInfo.object);
            if (collInfo.isAlive)
                collInfo.object->onCollide(obj1.first);
        }
    }
}

void Engine::checkCollisions()
{
    const auto& objects = PhysicalObject::getObjects();
    for (size_t i = 0; i < objects.size(); i++)
    {
        auto& obj1 = objects[i];
        if (!obj1.second || !obj1.first->isActive()) // continue if object is deleted or not active
            continue;

        for (auto& myCollider: obj1.first->_colliders)
            for (size_t k = 0; k < Collider::CollisionTypesNumber; k++)
                if (myCollider.collWith(static_cast<Collider::CollisionType>(k)))
                    checkCollisionsWithType(i, myCollider, static_cast<Collider::CollisionType>(k));
    }
    PhysicalObject::clearVector();
}

void Engine::updateUI()
{
    const auto& objects = UIObject::getObjects();
    const auto& mousePos = _mouse.getPosition(*_window);
    for (size_t i = 0; i < objects.size(); i++)
    {
        auto& obj = objects[i].first;
        if (!obj->isActive()) continue;
        if (objects[i].second == true &&
            mousePos.x > obj->position().x && mousePos.x < obj->position().x + obj->size().x &&
            mousePos.y > obj->position().y && mousePos.y < obj->position().y + obj->size().y)
        {
            if (!obj->_dragged)
            {
                obj->_dragged = true;
                obj->onStartDrag();
            }
            obj->onDrag();
            if (_mouse.isButtonPressed(sf::Mouse::Left))
            {
                if (!obj->_clicked)
                {
                    obj->_clicked = true;
                    obj->onMouseDown();
                }
                obj->onMouseClick();
            }
            else
            {
                if (obj->_clicked)
                {
                    obj->_clicked = false;
                    obj->onMouseUp();
                }
            }
        }
        else
        {
            if (obj->_dragged)
            {
                obj->_dragged = false;
                obj->onEndDrag();
            }
            obj->_clicked = false;
        }
    }
    UIObject::clearVector();
}

void Engine::updateGameInfo()
{
    int mask = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        mask += 1 << 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        mask += 1 << 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        mask += 1 << 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        mask += 1 << 3;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        mask += 1 << 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        mask += 1 << 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        mask += 1 << 6;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        mask += 1 << 7;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        mask += 1 << 8;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        mask += 1 << 9;

    GameInfo::_keyStatusMask = mask;
    const auto& pos = _mouse.getPosition(*_window);
    GameInfo::_deltaTime = 1.0/240 * _timeRate;
    GameInfo::_mousePosition = Vector2i(pos.x, pos.y);

    _time=_clock.getElapsedTime();
    static int licznik = 0;
    licznik++;
    if (licznik%100 == 0)
        cout<<1.f/_time.asSeconds()<<" - "<<GameObject::getObjects().size()<<" "<<UIObject::getObjects().size()<<endl;
    _clock.restart();

}
