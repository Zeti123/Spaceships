#include "LevelManager.hpp"
#include "Engine.hpp"

LevelManager* LevelManager::_level = nullptr;

LevelManager& LevelManager::Instance()
{
    if (_level == nullptr)
        _level = new LevelManager;
    return *_level;
}

LevelManager::LevelManager()
    :_active(false), _duration(0){}

void LevelManager::loadLevel(const LevelInfo& levelInfo)
{
    if (_activeObjects.size())
        throw "there are still active objects";

    _currentLevel = levelInfo;
    _active = true;
    _duration = 0;
}

void LevelManager::addObject(ILevelObject* obj)
{
    if (_active == false)
        throw "cannot add object when active = false";
    _activeObjects.push_back(obj);
}

void LevelManager::work()
{
    if (_active == false)
        throw "cannot work when active = false";
    bool blocked = false;
    for (size_t i = 0; i < _activeObjects.size(); i++)
    {
        if (!_activeObjects[i]->isAlive())
        {
            _activeObjects[i]->onDestroy();
            delete _activeObjects[i];
            std::swap(_activeObjects[i], _activeObjects.back());
            _activeObjects.pop_back();
            i--;
        }
        else if (_activeObjects[i]->blockLevel())
            blocked = true;
    }
    Spaceship* newSpaceship = _currentLevel.nextShipIf(duration());
    if (newSpaceship  != nullptr)
    {
        _activeObjects.push_back(newSpaceship);
        newSpaceship->setActive(true);
    }
    _duration += GameInfo::deltaTime();

    if (_currentLevel.endOfLevel())
    {
        if (!blocked)
            endLevel();
    }
    else if ((_currentLevel.endOfPart() && !blocked) || _currentLevel.partDuration() < _duration)
        nextPart();
}

void LevelManager::pause()
{
    if (_active == false)
        throw "cannot pause when active = false";
    Engine::Instance().setTimeRate(0);
}

void LevelManager::resume()
{
    if (_active == false)
        throw "cannot resume when active = false";
    Engine::Instance().setTimeRate(1);
}

bool LevelManager::isActive() const
{
    return _active;
}

size_t LevelManager::partsNumber() const
{
    return _currentLevel.partsNumber();
}

double LevelManager::duration() const
{
    return _duration;
}

void LevelManager::nextPart()
{
    if (_active == false)
        throw "cannot change part when active = false";
    _currentLevel.nextPart();
    _duration = 0;
}

void LevelManager::endLevel()
{
    _active = false;
    for (auto object : _activeObjects)
        delete object;
    _activeObjects.clear();
}
