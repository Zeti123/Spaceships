#include "Game.hpp"
#include "Enemy1.hpp"
#include "Enemy2.hpp"
#include "Enemy3.hpp"
#include "Enemy5.hpp"
#include "Enemy6.hpp"
#include "LevelManager.hpp"
#include "Engine.hpp"

#include <math.h>
#include <iostream>

Game::Game()
    :_level(LevelManager::Instance()), _player(new Player()), _state(State::MENU), _current_music("../Spaceships/Game/Resources/Sounds/main_menu.ogg")
{
    _menu.openMenu();
}

void Game::onFrame()
{
    if (!Engine::soundPlayer().isMusicPlayed())
                Engine::Instance().soundPlayer().playMusic(_current_music);

    const std::string musicPath = "../Spaceships/Game/Resources/Sounds/";
    if (_state == State::MENU)
    {
        if (!_menu.isActive())
        {
            _state = State::GAME_PLAY;
            Engine::soundPlayer().stopMusic();
            switch (_menu.loadedLevel())
            {
            case 0:
                loadLevel1();
                _current_music = musicPath + "TEN_TIMES_BETTER_THAN_YOU_FOBIA_INSTRUMENTAL.wav";
                break;
            case 1:
                loadLevel2();
                _current_music = musicPath + "BACK_IN_TIME_FOBIA_INSTRUMENTAL.wav";
                break;
            case 2:;
                loadLevel3();
                _current_music = musicPath + "ALKOMECH_FOBIA_INSTRUMENTAL.wav";
                break;
            }
        }
    }
    else if (_state == State::GAME_PLAY)
    {
        if (!_level.isActive())
        {
            Engine::soundPlayer().stopMusic();
            _current_music = musicPath + "main_menu.ogg";
            _state = State::MENU;
            _player->setActive(false);
            _menu.openLevelsMenu();
            return;
        }
        if (GameInfo::isKeyPressed(GameInfo::Key::SPACE))
        {
            _level.pause();
            _state = State::GAME_PAUSED;
            return;
        }
        _level.work();
    }
    else if (_state == State::GAME_PAUSED)
    {
        if (GameInfo::isKeyPressed(GameInfo::Key::SPACE))
        {
            _level.resume();
            _state = State::GAME_PLAY;
            return;
        }
        _level.work();
    }
}

void Game::loadLevel1()
{
    Vector2f gRes = GameInfo::resolution().toV2f();
    LevelInfo level1;

    level1.addNewPart(50);

    level1.addSpaceship(LevelInfo::SpaceshipInfo(2, Vector2f(gRes.x/2, -40), new Enemy1(M_PI/2)));
    for (int i = 1; i <= 4; i++)
    {
        level1.addSpaceship(LevelInfo::SpaceshipInfo(i * 0.8 + 2, Vector2f(gRes.x/2 - 150*i, -40), new Enemy1(M_PI/2)));
        level1.addSpaceship(LevelInfo::SpaceshipInfo(i * 0.8 + 2, Vector2f(gRes.x/2 + 150*i, -40), new Enemy1(M_PI/2)));
    }
    level1.addSpaceship(LevelInfo::SpaceshipInfo(5.3, Vector2f(-50, -50), new Enemy2([](const Enemy2&) { return Vector2f(100, 100); })));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(5.3, Vector2f(50 + gRes.x, -50), new Enemy2([gRes](const Enemy2&) { return Vector2f(gRes.x - 100, 100); })));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(12, Vector2f(gRes.x/2, gRes.y+40), new Enemy1(-M_PI/2)));
    for (int i = 0; i < 4; i++)
    {
        level1.addSpaceship(LevelInfo::SpaceshipInfo(12 + 0.8*i, Vector2f(gRes.x/2 - 150*i, gRes.y+40), new Enemy1(-M_PI/2)));
        level1.addSpaceship(LevelInfo::SpaceshipInfo(12 + 0.8*i, Vector2f(gRes.x/2 + 150*i, gRes.y+40), new Enemy1(-M_PI/2)));
    }

    level1.addNewPart(120);
    auto add4 = [&level1, gRes](float time, float offset, bool horizontal)
    {
        Vector2f a, b, off;
        float angle;
        if (horizontal)
        {
            a = Vector2f(gRes.x/2, -40);
            b = Vector2f(gRes.x/2, gRes.y+40);
            off = Vector2f(offset, 0);
            angle = M_PI/2;
        }
        else
        {
            a = Vector2f(-40, gRes.y/2);
            b = Vector2f(gRes.x + 40, gRes.y/2);
            off = Vector2f(0, offset);
            angle = M_PI;
        }
        level1.addSpaceship(LevelInfo::SpaceshipInfo(time, a + off, new Enemy1(angle)));
        level1.addSpaceship(LevelInfo::SpaceshipInfo(time, a - off, new Enemy1(angle)));
        level1.addSpaceship(LevelInfo::SpaceshipInfo(time, b + off, new Enemy1(angle + M_PI)));
        level1.addSpaceship(LevelInfo::SpaceshipInfo(time, b - off, new Enemy1(angle + M_PI)));
    };
    for (int i = 0; i < 8; i++)
        add4(0.8 * i, 50 * (i + 1), i%2);


    level1.addSpaceship(LevelInfo::SpaceshipInfo(25, Vector2f(gRes.x/2, -40), new Enemy3([gRes](const Enemy3&){ return Vector2f(gRes.x/2, gRes.y/2); })));
    _player->setActive(true);
    _player->reset();


    _level.loadLevel(level1);
}

void Game::loadLevel2()
{
    auto func = [](const Enemy2& obj) -> Vector2f
    {
        double _time = obj.currentLifeTime();
        return Vector2f(cos(_time/2.5)*(GameInfo::resolution().y/2 - 40) + GameInfo::resolution().x/2 - 20,
                        sin(_time/2.5)*(GameInfo::resolution().y/2 - 40) + GameInfo::resolution().y/2 - 20);
    };
    auto func2 = [](const Enemy2& obj) -> Vector2f
    {
        double _time = obj.currentLifeTime();
        return Vector2f(cos(_time/2.5 + M_PI)*(GameInfo::resolution().y/2 - 40) + GameInfo::resolution().x/2 - 20,
                        sin(_time/2.5 + M_PI)*(GameInfo::resolution().y/2 - 40) + GameInfo::resolution().y/2 - 20);
    };
    auto func3 = [](const Enemy3& obj) -> Vector2f
    {
        double _time = obj.currentLifeTime();
        return Vector2f(cos(_time/2.5 + M_PI)*cos(_time/2.5 + M_PI)*(GameInfo::resolution().y/2 - 40) + GameInfo::resolution().x/2 - 20,
                        sin(_time/2.5 + M_PI)*sin(_time/2.5 + M_PI)*(GameInfo::resolution().y/2 - 40) + GameInfo::resolution().y/2 - 20);

    };
    auto func4 = [](const Enemy3& obj) -> Vector2f
    {
        double _time = obj.currentLifeTime();
        return Vector2f(-cos(_time/2.5 + M_PI)*cos(_time/2.5 + M_PI)*(GameInfo::resolution().y/2 - 40) + GameInfo::resolution().x/2 - 20,
                        -sin(_time/2.5 + M_PI)*sin(_time/2.5 + M_PI)*(GameInfo::resolution().y/2 - 40) + GameInfo::resolution().y/2 - 20);
    };
    auto func5 = [](const Enemy5& obj, float angle) -> Vector2f
    {

        int time = obj.currentLifeTime();
        if (time % 20 <= 10)
            return Vector2f(cos(angle), sin(angle)) * 0.2 * GameInfo::resolution().x + Vector2f(GameInfo::resolution().x/2, GameInfo::resolution().y/2);
        return Vector2f(cos(angle), sin(angle)) * 0.6 * GameInfo::resolution().x + Vector2f(GameInfo::resolution().x/2, GameInfo::resolution().y/2);
    };

    LevelInfo level1;
    level1.addNewPart(30);

    for (int i = 0; i < 5; i++)
    {
        level1.addSpaceship(LevelInfo::SpaceshipInfo(i, Vector2f(100 + 200*i, -50), new Enemy1(M_PI/2)));
        level1.addSpaceship(LevelInfo::SpaceshipInfo(i, Vector2f(GameInfo::resolution().x - (100 + 200*i), -50), new Enemy1(M_PI/2)));
    }
    level1.addSpaceship(LevelInfo::SpaceshipInfo(5, Vector2f(-50, 300), new Enemy2(func)));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(5, Vector2f(GameInfo::resolution().x + 50, 300), new Enemy2(func2)));

    level1.addNewPart(40);
    level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(-50, 300), new Enemy3(func3)));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x + 50, 300), new Enemy3(func4)));

    level1.addNewPart(50);
    for (int i = 0; i < 4; i++)
        level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(-50, -50), new Enemy5([func5, i](const Enemy5& obj){ return func5(obj, i * M_PI/2); })));

    _player->setActive(true);
    _player->reset();


    _level.loadLevel(level1);
}

class Functor_spaceships_circle
{
public:
    Functor_spaceships_circle()
        :_num(_counter++) {}
    ~Functor_spaceships_circle()
    {
        for (size_t i = 0; i + 1 < _ships.size(); i++)
            if (_ships[i] == _num)
                std::swap(_ships[i], _ships[i + 1]);

        if (!_ships.empty() && _ships.back() == _num)
            _ships.pop_back();
    }

    Vector2f operator()(const Spaceship&)
    {
        size_t index = UINT64_MAX;
        for (size_t i = 0; i < _ships.size(); i++)
            if (_num == _ships[i])
                index = i;

        if (index == UINT64_MAX)
        {
            index = _ships.size();
            _ships.push_back(_num);
        }

        if (index == 0)
            _time += GameInfo::deltaTime();

        double angle = 2*M_PI * static_cast<double>(index)/_ships.size() + _time/2.5;
        return Vector2f(cos(angle)*300+ GameInfo::resolution().x/2, sin(angle)*250 + GameInfo::resolution().y/2);

    }

private:
    static std::vector<size_t> _ships;
    static double _time;
    static size_t _counter;
    size_t _num;
};

std::vector<size_t> Functor_spaceships_circle::_ships = {};
double Functor_spaceships_circle::_time = 0;
size_t Functor_spaceships_circle::_counter = 0;

void Game::loadLevel3()
{

    auto figure_eight = [](const Enemy6& e, float offset)
    {
        float time = e.currentLifeTime();
        Vector2f middle = Vector2f(GameInfo::resolution().x/2, GameInfo::resolution().y/2);
        return Vector2f(cos(time/M_PI*1.2 + offset), sin(time/M_PI*2.4 + offset) * 0.8) * 300 + middle;
    };

    class Functor_random_move
    {
    public:
        Functor_random_move()
            : _nextPos(0, 0), _nextMoveSeconds(0), _currentTime(0) {}
        Vector2f operator ()(const Spaceship&)
        {
            _currentTime += GameInfo::deltaTime();
            if (_currentTime >= _nextMoveSeconds)
            {
                _nextMoveSeconds = (std::rand()%50) / 10 + 2;
                _currentTime = 0;

                _nextPos = Vector2f(std::rand()%GameInfo::resolution().x, std::rand()%GameInfo::resolution().y);
            }

            return _nextPos;
        }

    private:
        Vector2f _nextPos;
        float _nextMoveSeconds;
        float _currentTime;
    };

    LevelInfo level1;

    level1.addNewPart(60);
    level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy2(Functor_random_move())));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy2(Functor_random_move())));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy6([figure_eight](const Enemy6& e){ return figure_eight(e, 0); })));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy6([figure_eight](const Enemy6& e){ return figure_eight(e, M_PI/2); })));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy6([figure_eight](const Enemy6& e){ return figure_eight(e, M_PI); })));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy6([figure_eight](const Enemy6& e){ return figure_eight(e, M_PI*3/2); })));

    level1.addNewPart(75);
    level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0),
                                                 new Enemy3([](const Spaceship&){ return Vector2f(GameInfo::resolution().x/10, GameInfo::resolution().y/10); })));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0),
                                                 new Enemy3([](const Spaceship&){ return Vector2f(GameInfo::resolution().x/10*9, GameInfo::resolution().y/10); })));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, 50.0 + GameInfo::resolution().y),
                                                 new Enemy3([](const Spaceship&){ return Vector2f(GameInfo::resolution().x/10, GameInfo::resolution().y/10*9); })));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, 50.0 + GameInfo::resolution().y),
                                                 new Enemy3([](const Spaceship&){ return Vector2f(GameInfo::resolution().x/10*9, GameInfo::resolution().y/10*9); })));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(25, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy1(M_PI/3)));
    level1.addSpaceship(LevelInfo::SpaceshipInfo(25, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy1(M_PI/3*2)));

    level1.addNewPart(82);
    for (size_t i = 0; i < 5; i++)
        level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy5(Functor_spaceships_circle())));
    for (size_t i = 0; i < 5; i++)
    level1.addSpaceship(LevelInfo::SpaceshipInfo(10, Vector2f(GameInfo::resolution().x/2 + 100 * i - 200, -50.0), new Enemy1(M_PI/2)));

    level1.addNewPart(45);
    for (size_t i = 0; i < 2; i++)
        level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy5(Functor_spaceships_circle())));
    for (size_t i = 0; i < 5; i++)
    level1.addSpaceship(LevelInfo::SpaceshipInfo(10, Vector2f(GameInfo::resolution().x/2 + 100 * i - 200, -50.0), new Enemy1(M_PI/2)));

    level1.addNewPart(30);
    for (size_t i = 0; i < 2; i++)
        level1.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy5(Functor_spaceships_circle())));
    for (size_t i = 0; i < 5; i++)
    level1.addSpaceship(LevelInfo::SpaceshipInfo(10, Vector2f(GameInfo::resolution().x/2 + 100 * i - 200, -50.0), new Enemy1(M_PI/2)));

    _player->setActive(true);
    _player->reset();


    _level.loadLevel(level1);
}

