#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "LevelInfo.hpp"
#include "ILevelObject.hpp"
#include "Player.hpp"

class LevelManager
{
public:
    static LevelManager& Instance();

    void loadLevel(const LevelInfo& levelInfo);
    void addObject(ILevelObject* obj);
    void work();
    void pause();
    void resume();
    void endLevel();

    bool isActive() const;
    size_t partsNumber() const;
    double duration() const;

private:
    static LevelManager* _level;

    LevelManager();
    void nextPart();

    LevelInfo _currentLevel;
    std::vector<ILevelObject*> _activeObjects;
    bool _active;
    double _duration;
};

#endif // LEVEL_HPP
