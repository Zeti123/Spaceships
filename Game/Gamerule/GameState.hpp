#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
#include <vector>

class GameState
{
public:
    // describes level state
    struct LevelState
    {
        bool unlocked;
        bool passed;
    };

    // describes the state of the level group
    struct LevelGroupState
    {
        bool unlocked;
        std::vector<LevelState> levels;
    };

public:
    GameState();
    void createNewGame(const std::vector<size_t>& numOfLevelsInParts);
    void saveToFile(const std::string& filename);

    // returns true if success
    bool loadFromFile(const std::string& filename);

    LevelState getLevelState(size_t part, size_t level) const;
    bool isGroupUnlocked(size_t part) const;
    size_t getGroupsNum() const;
    size_t getLevelsNumInGroup(size_t part) const;
    void updateLevelState(size_t part, size_t level, LevelState newState);
    void unlockGroup(size_t part);
    void addNewGroup(size_t levelsNum);
    void addLevelToGroup(size_t groupNum);

private:
    std::vector<LevelGroupState> _gameState;
};

#endif // GAMESTATE_HPP
