#include "Game.hpp"
#include "Enemy1.hpp"
#include "Enemy2.hpp"
#include "Enemy3.hpp"
#include "Enemy5.hpp"
#include "Enemy6.hpp"
#include "LevelManager.hpp"
#include "Engine.hpp"
#include "Levels.hpp"
#include "MainView.hpp"
#include "PauseView.hpp"
#include "LevelsView.hpp"

#include <math.h>
#include <iostream>
#include <limits>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

const std::string Game::musicPath = "Sounds/";

Game::Game()
    :_level(LevelManager::Instance()), _player(new Player()), _state(State::MENU), _currentMusic("Sounds/main_menu.ogg"), _lastPlayedLevel({})
{
    _menu.changeView(new MainView(&_gameState));
    bool success = _gameState.loadFromFile("save.sav");
    if (!success)
    {
        createNewSave();
        _gameState.saveToFile("save.sav");
    }
    else
        checkSave();
}

void Game::onFrame()
{
    if (_state == State::MENU)
    {
        if (!Engine::soundPlayer().isMusicPlayed())
                    Engine::Instance().soundPlayer().playMusic(_currentMusic);

        if (_menu.getAction() == MainMenu::Action::LOAD_LEVEL)
        {
            _state = State::GAME_PLAY;
            Engine::soundPlayer().stopMusic();
            _lastPlayedLevel =  _menu.getLoadedLevel();
            loadAndStartLevel(_lastPlayedLevel.stage, _lastPlayedLevel.level);
        }

        if (_menu.getAction() == MainMenu::Action::END_GAME)
            Engine::Instance().exit();

        _menu.update();
    }
    else if (_state == State::GAME_PLAY)
    {
        if (!Engine::soundPlayer().isMusicPlayed())
                    Engine::Instance().soundPlayer().playMusic(_currentMusic);

        if (_level.getLevelStatus() != LevelManager::LevelStatus::RUNNING)
        {
            if (_level.getLevelStatus() == LevelManager::LevelStatus::PASSED)
            {
                _gameState.updateLevelState(_lastPlayedLevel.stage, _lastPlayedLevel.level, {true, true});
                if (_lastPlayedLevel.level + 1 < _gameState.getLevelsNumInGroup(_lastPlayedLevel.stage))
                {
                    auto nextLevelState = _gameState.getLevelState(_lastPlayedLevel.stage, _lastPlayedLevel.level + 1);
                    _gameState.updateLevelState(_lastPlayedLevel.stage, _lastPlayedLevel.level + 1, {true, nextLevelState.passed});
                }
                _gameState.saveToFile("save.sav");
            }

            switchToMenu();
            return;
        }
        if (GameInfo::isKeyPressed(GameInfo::Key::ESC))
        {
            _level.pause();
            _menu.changeView(new PauseView());
            Engine::soundPlayer().stopMusic();
            _state = State::GAME_PAUSED;
            return;
        }
        _level.work();
    }
    else if (_state == State::GAME_PAUSED)
    {
        if (_menu.getAction() == MainMenu::Action::RESUME)
        {
            _level.resume();
            _state = State::GAME_PLAY;
            Engine::Instance().soundPlayer().resumeMusic();
            _menu.update();
            return;
        }
        if (_menu.getAction() == MainMenu::Action::BACK_TO_MENU)
        {
            _level.endLevel(LevelManager::LevelStatus::NOT_PASSED);
            switchToMenu();
            _menu.update();
            return;
        }
        _menu.update();
        _level.work();
    }
}

void Game::loadAndStartLevel(size_t group, size_t level)
{
    auto groups = getLevelsGroupsStructure();
    _player->setActive(true);
    _player->reset();

    auto levelInfo = groups[group].getLoaderFunction(level)();
    _currentMusic = musicPath + levelInfo.getMusicPath();
    _level.Instance().loadLevel(levelInfo);
}

void Game::switchToMenu()
{
    Engine::soundPlayer().stopMusic();
    _currentMusic = musicPath + "main_menu.ogg";
    _state = State::MENU;
    _player->setActive(false);
    _menu.changeView(new LevelsView(&_gameState, _lastPlayedLevel.stage));
}

void Game::createNewSave()
{
    auto vec = getLevelsGroupsStructure();
    std::vector<size_t> numOfLevelsInGroup;
    for (const auto& v: vec)
        numOfLevelsInGroup.push_back(v.levelsNum());
    _gameState.createNewGame(numOfLevelsInGroup);
}

// checks if save is up to date and contains info about all levels if not function repers this
void Game::checkSave()
{
    auto vec = getLevelsGroupsStructure();

    // add new levels to existing gropus
    for (size_t i = 0; i < _gameState.getGroupsNum(); i++)
    {
        while (_gameState.getLevelsNumInGroup(i) < vec[i].levelsNum())
            _gameState.addLevelToGroup(i);
    }

    // adding new groups
    for (size_t i = _gameState.getGroupsNum(); i < vec.size(); i++)
    {
        _gameState.addNewGroup(vec[i].levelsNum());
    }
    _gameState.saveToFile("save.sav");
}
