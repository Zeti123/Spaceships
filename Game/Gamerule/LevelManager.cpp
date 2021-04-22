#include "LevelManager.hpp"
#include "Engine.hpp"
#include "LevelEndLabel.hpp"

LevelManager* LevelManager::_level = nullptr;

LevelManager& LevelManager::Instance()
{
    if (_level == nullptr)
        _level = new LevelManager;
    return *_level;
}

LevelManager::LevelManager()
    :_status(LevelStatus::NOT_PASSED), _duration(0){}

void LevelManager::loadLevel(const LevelInfo& levelInfo)
{
    if (_activeObjects.size())
        throw "there are still active objects";

    _currentLevel = levelInfo;
    _status = LevelStatus::RUNNING;
    resume();
    _duration = 0;
}

void LevelManager::addObject(ILevelObject* obj)
{
    if (_status != LevelStatus::RUNNING)
        throw "cannot add object when level is not running";
    _activeObjects.push_back(obj);
}

void LevelManager::work()
{
    if (_status != LevelStatus::RUNNING)
        throw "cannot work when level is not running";

    bool blocked = false;
    for (size_t i = 0; i < _activeObjects.size(); i++)
    {
        if (!_activeObjects[i]->isAlive())
        {
            _activeObjects[i]->onDestroy();
            if (_status != LevelStatus::RUNNING)
                return;
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
            addObject(new LevelEndLabel(true));
    }
    else if ((_currentLevel.endOfPart() && !blocked) || _currentLevel.partDuration() < _duration)
        nextPart();
}

void LevelManager::pause()
{
    if (_status != LevelStatus::RUNNING)
        throw "cannot pause when level is not running";

    Engine::Instance().setTimeRate(0);

    GameObject* obj;
    for (auto o: _activeObjects)
        if ((obj = dynamic_cast<GameObject*>(o)) != nullptr)
            obj->setActive(false);

    Player* player = dynamic_cast<Player*>(Engine::Instance().findObjectById("player"));
    if (player == nullptr)
        throw "other object is marked as player";
    player->setActive(false);
}

void LevelManager::resume()
{
    if (_status != LevelStatus::RUNNING)
        throw "cannot resume when level is not running";
    Engine::Instance().setTimeRate(1);

    GameObject* obj;
    for (auto o: _activeObjects)
        if ((obj = dynamic_cast<GameObject*>(o)) != nullptr)
            obj->setActive(true);

    Player* player = dynamic_cast<Player*>(Engine::Instance().findObjectById("player"));
    if (player == nullptr)
        throw "other object is marked as player";
    player->setActive(true);
}

LevelManager::LevelStatus LevelManager::getLevelStatus() const
{
    return _status;
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
    if (_status != LevelStatus::RUNNING)
        throw "cannot change part when level is not running";
    _currentLevel.nextPart();
    _duration = 0;
}

void LevelManager::endLevel(LevelStatus endStatus)
{
    _status = endStatus;
    _currentLevel.clear();
    for (auto object : _activeObjects)
        delete object;
    _activeObjects.clear();
}
