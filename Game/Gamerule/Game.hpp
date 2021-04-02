#ifndef GAME_HPP
#define GAME_HPP

#include "Button.hpp"
#include "Player.hpp"
#include "MainClass.hpp"
#include "LevelManager.hpp"
#include "MainMenu.hpp"

class Game : public MainClass
{
    enum class State
    {
        GAME_PLAY, GAME_PAUSED, MENU
    };

public:
    Game();
    void onFrame() override;
    void loadLevel1();
    void loadLevel2();
    void loadLevel3();

private:
    MainMenu _menu;
    LevelManager& _level;
    Player* _player;
    State _state;
    std::string _current_music;
};

#endif // GAME_HPP
