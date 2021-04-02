#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
#include <vector>

class GameState
{
public:
    struct LevelState
    {
        bool unlocked;
        bool passed;
    };
    struct PartState
    {
        bool unlocked;
        std::vector<LevelState> levels;
    };

public:
    GameState();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void addPart(bool unlocked);
    void addLevel(size_t part, LevelState state);
};

#endif // GAMESTATE_HPP
