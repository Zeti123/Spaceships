#ifndef GAME_HPP
#define GAME_HPP

#include "Button.hpp"
#include "Player.hpp"
#include "MainClass.hpp"
#include "LevelManager.hpp"
#include "MainMenu.hpp"
#include "GameState.hpp"

class Game : public MainClass
{
    enum class State
    {
        GAME_PLAY, GAME_PAUSED, MENU
    };

public:
    Game();
    void onFrame() override;
    void loadAndStartLevel(size_t group, size_t level);

private:
    void switchToMenu();
    void createNewSave();
    // checks if save is up to date and contains info about all levels if not function repers this
    void checkSave();

private:
    static const std::string musicPath;
    MainMenu _menu;
    LevelManager& _level;
    Player* _player;
    State _state;
    GameState _gameState;
    std::string _currentMusic;
    size_t _lastPlayedLevel;
};
#endif // GAME_HPP
