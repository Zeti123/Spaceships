#include "GameState.hpp"

#include <fstream>

GameState::GameState()
    :_gameState() {}

void GameState::createNewGame(const std::vector<size_t>& numOfLevelsInParts)
{
    if (numOfLevelsInParts.empty())
        throw "parts number have to be positive";

    _gameState.resize(numOfLevelsInParts.size());
    for (size_t i = 0; i < numOfLevelsInParts.size(); i++)
    {
        _gameState[i].levels.resize(numOfLevelsInParts[i], {false, false});
        _gameState[i].unlocked = false;
    }

    // level 1 in first part is always unlocked
    _gameState[0].unlocked = true;
    _gameState[0].levels[0].unlocked = true;
}

void GameState::saveToFile(const std::string& filename)
{
    std::ofstream file;
    file.open(filename, std::ofstream::out | std::ofstream::trunc);
    if (!file.good())
        throw "cannot open or create file";

    for (auto& group: _gameState)
    {
        file<<group.levels.size()<<" "<<group.unlocked<<std::endl;
        for (auto& level: group.levels)
        {
            file<<level.unlocked<<" ";
            file<<level.passed<<" ";
        }
        file<<std::endl;
    }
    file.close();
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file;
    file.open(filename);
    if (!file.good())
        return false;

    while (file.good())
    {
        size_t partSize;
        bool unlocked;
        file>>partSize;
        if (!file.good())
            return true;

        file>>unlocked;

        _gameState.push_back({});
        auto& elem = _gameState.back();
        elem.levels.resize(partSize);
        elem.unlocked = unlocked;
        for (size_t i = 0; i < partSize; i++)
        {
            bool lUnlocked;
            bool lPassed;
            file>>lUnlocked>>lPassed;
            elem.levels[i] = {lUnlocked, lPassed};
        }
    }
    return true;
}

GameState::LevelState GameState::getLevelState(size_t part, size_t level) const
{
    if (_gameState.size() <= part || _gameState[part].levels.size() <= level)
        throw "requested level doesn't exist";

    return _gameState[part].levels[level];
}

bool GameState::isGroupUnlocked(size_t part) const
{
    if (_gameState.size() <= part)
        throw "requested part doesn't exist";

    return _gameState[part].unlocked;
}

size_t GameState::getGroupsNum() const
{
    return _gameState.size();
}

size_t GameState::getLevelsNumInGroup(size_t part) const
{
    if (_gameState.size() <= part)
        throw "requested part doesn't exist";

    return _gameState[part].levels.size();
}

void GameState::updateLevelState(size_t part, size_t level, LevelState newState)
{
    if (_gameState.size() <= part || _gameState[part].levels.size() <= level)
        throw "requested level doesn't exist";

    _gameState[part].levels[level] = newState;
}

void GameState::unlockGroup(size_t part)
{
    if (_gameState.size() <= part)
        throw "requested part doesn't exist";

    _gameState[part].unlocked = true;
}

void GameState::addNewGroup(size_t levelsNum)
{
    _gameState.push_back({});
    auto& elem = _gameState.back();
    elem.unlocked = false;
    elem.levels.resize(3);
    for (size_t i = 0; i < levelsNum; i++)
        elem.levels[i] = {false, false};
}
