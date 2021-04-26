#include "Levels.hpp"

#include "Enemy1.hpp"
#include "Enemy2.hpp"
#include "Enemy3.hpp"
#include "Enemy4.hpp"
#include "Enemy5.hpp"
#include "Enemy6.hpp"

#include <cmath>

std::vector<LevelsGroupInfo> getLevelsGroupsStructure()
{
    std::vector<LevelsGroupInfo> lgi;
    lgi.emplace_back(std::vector<std::function<LevelInfo()>>{loadLevel1_1, loadLevel1_2, loadLevel1_3, loadLevel1_4});

    return lgi;
}

LevelInfo loadLevel1_1()
{
    Vector2f res = GameInfo::resolution().toV2f();

    auto triangle = [res](const Enemy2& obj, double offset, int y) -> Vector2f
    {
        double time = obj.currentLifeTime() + offset;
        double speed = 16;
        if (static_cast<int>(time)%32 < speed)
            return Vector2f(50 + (res.x-100) * (time/speed - static_cast<int>(time/speed)), y);
        return Vector2f(res.x - 50 - (res.x-100) * (time/speed - static_cast<int>(time/speed)), y);
    };

    LevelInfo level;
    level.setMusicPath("TEN_TIMES_BETTER_THAN_YOU_FOBIA_INSTRUMENTAL.wav");

    level.addNewPart(60);

    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2, -40), new Enemy1(M_PI/2)));
    for (int i = 1; i <= 3; i++)
    {
        level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2 + 200*i, (res.y + 80)*(i%2) - 40), new Enemy1(((-M_PI)*(i%2)) + M_PI/2)));
        level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2 - 200*i, (res.y + 80)*(i%2) - 40), new Enemy1(((-M_PI)*(i%2)) + M_PI/2)));
    }

    level.addSpaceship(LevelInfo::SpaceshipInfo(5, Vector2f(-40, res.y/2), new Enemy2([res](const Enemy2&){ return Vector2f(110, res.y/2); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(5, Vector2f(res.x + 40, res.y/2), new Enemy2([res](const Enemy2&){ return Vector2f(res.x - 110, res.y/2); })));

    level.addNewPart(40);
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x, 0), new Enemy1(M_PI*3/4)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(0, 0), new Enemy1(M_PI/4)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(0, res.y), new Enemy1(-M_PI/4)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x, res.y), new Enemy1(M_PI*5/4)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(5, Vector2f(res.x/2, -40), new Enemy3([res](const Enemy3&){ return Vector2f(res.x/2 + 40, res.y/2); })));

    level.addNewPart(10);
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2, -40), new Enemy2([triangle](const Enemy2& obj){ return triangle(obj, 0, 50); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2, res.y + 40), new Enemy2([triangle, res](const Enemy2& obj){ return triangle(obj, 16, res.y - 50); })));


return level;
}

LevelInfo loadLevel1_2()
{
    Vector2f res = GameInfo::resolution().toV2f();

    auto small_circle = [res](const Enemy6& obj) -> Vector2f
    {
        double time = obj.currentLifeTime();
        return Vector2f(cos(time), sin(time)) * 50 + Vector2f(res.x/2, res.y/2);
    };

    auto flattened_wave = [res](const Enemy2& obj, bool neg) -> Vector2f
    {
        auto absd = [](double a) -> double { return (a >= 0) ? a : -a; };
        double time = obj.currentLifeTime();
        if (neg)
            return Vector2f(absd(cos(time)), sin(time)) * 650 + Vector2f(res.x/2, res.y/2);
        return Vector2f(-absd(cos(time)), sin(time)) * 650 + Vector2f(res.x/2, res.y/2);
    };

    class square
    {
    public:
        square(size_t startDirection)
            :direction(startDirection), offset({{Vector2f(-250, -250), Vector2f(250, -250),
                                    Vector2f(250, 250), Vector2f(-250, 250)}}) {}

        Vector2f operator()(const Enemy2& obj)
        {
            Vector2f res = GameInfo::resolution().toV2f();
            const Vector2f dest = Vector2f(res.x/2, res.y/2) + offset[direction];
            if (obj.position().x == dest.x && obj.position().y == dest.y)
                direction = (direction + 1) % 4;
            return Vector2f(res.x/2, res.y/2) + offset[direction];
        }

    private:
        size_t direction;
        std::array<Vector2f, 4> offset;
    };

    LevelInfo level;
    level.setMusicPath("ALKOMECH_FOBIA_INSTRUMENTAL.wav");
    level.addNewPart(50);
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2 + 175, -40), new Enemy1(M_PI/2)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2 - 175, -40), new Enemy1(M_PI/2)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2 + 400, -40), new Enemy1(M_PI/2)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2 - 400, -40), new Enemy1(M_PI/2)));

    level.addSpaceship(LevelInfo::SpaceshipInfo(1, Vector2f(res.x + 40, res.y/2 - 150), new Enemy1(M_PI)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(1, Vector2f(res.x + 40, res.y/2), new Enemy1(M_PI)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(1, Vector2f(res.x + 40, res.y/2 + 150), new Enemy1(M_PI)));

    level.addSpaceship(LevelInfo::SpaceshipInfo(1, Vector2f(res.x + 40, res.y/2 - 150), new Enemy1(0)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(1, Vector2f(res.x + 40, res.y/2), new Enemy1(0)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(1, Vector2f(res.x + 40, res.y/2 + 150), new Enemy1(0)));

    level.addSpaceship(LevelInfo::SpaceshipInfo(8, Vector2f(res.x/2, res.y + 40), new Enemy6(small_circle)));

    level.addNewPart(80);
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2, -40), new Enemy1(M_PI/2)));
    for (int i = 1; i <= 3; i++)
    {
        level.addSpaceship(LevelInfo::SpaceshipInfo(i*0.75, Vector2f(res.x/2 + 200*i, - 40), new Enemy1(M_PI/2)));
        level.addSpaceship(LevelInfo::SpaceshipInfo(i*0.75, Vector2f(res.x/2 - 200*i, - 40), new Enemy1(M_PI/2)));
    }
    level.addSpaceship(LevelInfo::SpaceshipInfo(3, Vector2f(res.x + 40, res.y/2), new Enemy1(M_PI)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(3, Vector2f(-40, res.y/2), new Enemy1(0)));

    level.addSpaceship(LevelInfo::SpaceshipInfo(3.5, Vector2f(res.x + 40, res.y/2 - 150), new Enemy1(M_PI)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(3.5, Vector2f(res.x + 40, res.y/2 + 150), new Enemy1(M_PI)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(3.5, Vector2f(-40, res.y/2 - 150), new Enemy1(0)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(3.5, Vector2f(-40, res.y/2 + 150), new Enemy1(0)));

    level.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(res.x + 40, res.y/2 - 200),
                                                new Enemy2([flattened_wave](const Enemy2& obj){ return flattened_wave(obj, false); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(-40, res.y/2 - 200),
                                                new Enemy2([flattened_wave](const Enemy2& obj){ return flattened_wave(obj, true); })));



    level.addNewPart(50);
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(-40, res.y/2), new Enemy3([res](const Enemy3&){ return Vector2f(150, res.y/2); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x + 40, res.y/2), new Enemy3([res](const Enemy3&){ return Vector2f(res.x - 150, res.y/2); })));

    level.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(150, -40), new Enemy1(M_PI/2)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(res.x - 150, -40), new Enemy1(M_PI/2)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(res.x/2, res.y + 40), new Enemy1(-M_PI/2)));

    level.addNewPart(10);
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2, res.y + 40), new Enemy2(square(0))));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(res.x/2, - 40), new Enemy2(square(2))));
    return level;
}

LevelInfo loadLevel1_3()
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

    LevelInfo level;
    level.setMusicPath("BACK_IN_TIME_FOBIA_INSTRUMENTAL.wav");
    level.addNewPart(30);

    for (int i = 0; i < 5; i++)
    {
        level.addSpaceship(LevelInfo::SpaceshipInfo(i, Vector2f(100 + 200*i, -50), new Enemy1(M_PI/2)));
        level.addSpaceship(LevelInfo::SpaceshipInfo(i, Vector2f(GameInfo::resolution().x - (100 + 200*i), -50), new Enemy1(M_PI/2)));
    }
    level.addSpaceship(LevelInfo::SpaceshipInfo(5, Vector2f(-50, 300), new Enemy2(func)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(5, Vector2f(GameInfo::resolution().x + 50, 300), new Enemy2(func2)));

    level.addNewPart(40);
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(-50, 300), new Enemy3(func3)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x + 50, 300), new Enemy3(func4)));

    level.addNewPart(50);
    for (int i = 0; i < 4; i++)
        level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(-50, -50), new Enemy5([func5, i](const Enemy5& obj){ return func5(obj, i * M_PI/2); })));

    return level;
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
        size_t index = std::numeric_limits<decltype(index)>::max();
        for (size_t i = 0; i < _ships.size(); i++)
            if (_num == _ships[i])
                index = i;

        if (index == std::numeric_limits<decltype(index)>::max())
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

LevelInfo loadLevel1_4()
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

    LevelInfo level;
    level.setMusicPath("ALKOMECH_FOBIA_INSTRUMENTAL.wav");

    level.addNewPart(60);
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy2(Functor_random_move())));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy2(Functor_random_move())));
    level.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy6([figure_eight](const Enemy6& e){ return figure_eight(e, 0); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy6([figure_eight](const Enemy6& e){ return figure_eight(e, M_PI/2); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy6([figure_eight](const Enemy6& e){ return figure_eight(e, M_PI); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(15, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy6([figure_eight](const Enemy6& e){ return figure_eight(e, M_PI*3/2); })));

    level.addNewPart(75);
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0),
                                                 new Enemy3([](const Spaceship&){ return Vector2f(GameInfo::resolution().x/10, GameInfo::resolution().y/10); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0),
                                                 new Enemy3([](const Spaceship&){ return Vector2f(GameInfo::resolution().x/10*9, GameInfo::resolution().y/10); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, 50.0 + GameInfo::resolution().y),
                                                 new Enemy3([](const Spaceship&){ return Vector2f(GameInfo::resolution().x/10, GameInfo::resolution().y/10*9); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, 50.0 + GameInfo::resolution().y),
                                                 new Enemy3([](const Spaceship&){ return Vector2f(GameInfo::resolution().x/10*9, GameInfo::resolution().y/10*9); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(25, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy1(M_PI/3)));
    level.addSpaceship(LevelInfo::SpaceshipInfo(25, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy1(M_PI/3*2)));

    level.addNewPart(60);
    for (size_t i = 0; i < 5; i++)
        level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy5(Functor_spaceships_circle())));
    for (size_t i = 0; i < 5; i++)
    level.addSpaceship(LevelInfo::SpaceshipInfo(10, Vector2f(GameInfo::resolution().x/2 + 100 * i - 200, -50.0), new Enemy1(M_PI/2)));

    level.addNewPart(45);
    for (size_t i = 0; i < 2; i++)
        level.addSpaceship(LevelInfo::SpaceshipInfo(0, Vector2f(GameInfo::resolution().x/2, -50.0), new Enemy5(Functor_spaceships_circle())));
    for (size_t i = 0; i < 5; i++)
    level.addSpaceship(LevelInfo::SpaceshipInfo(10, Vector2f(GameInfo::resolution().x/2 + 100 * i - 200, -50.0), new Enemy1(M_PI/2)));

    return level;
}


/*LevelInfo loadLevel1_2()
{
    Vector2f gRes = GameInfo::resolution().toV2f();
    LevelInfo level;
    level.setMusicPath("TEN_TIMES_BETTER_THAN_YOU_FOBIA_INSTRUMENTAL.wav");

    level.addNewPart(50);

    level.addSpaceship(LevelInfo::SpaceshipInfo(2, Vector2f(gRes.x/2, -40), new Enemy1(M_PI/2)));
    for (int i = 1; i <= 4; i++)
    {
        level.addSpaceship(LevelInfo::SpaceshipInfo(i * 0.8 + 2, Vector2f(gRes.x/2 - 150*i, -40), new Enemy1(M_PI/2)));
        level.addSpaceship(LevelInfo::SpaceshipInfo(i * 0.8 + 2, Vector2f(gRes.x/2 + 150*i, -40), new Enemy1(M_PI/2)));
    }
    level.addSpaceship(LevelInfo::SpaceshipInfo(5.3, Vector2f(-50, -50), new Enemy2([](const Enemy2&) { return Vector2f(100, 100); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(5.3, Vector2f(50 + gRes.x, -50), new Enemy2([gRes](const Enemy2&) { return Vector2f(gRes.x - 100, 100); })));
    level.addSpaceship(LevelInfo::SpaceshipInfo(12, Vector2f(gRes.x/2, gRes.y+40), new Enemy1(-M_PI/2)));
    for (int i = 0; i < 4; i++)
    {
        level.addSpaceship(LevelInfo::SpaceshipInfo(12 + 0.8*i, Vector2f(gRes.x/2 - 150*i, gRes.y+40), new Enemy1(-M_PI/2)));
        level.addSpaceship(LevelInfo::SpaceshipInfo(12 + 0.8*i, Vector2f(gRes.x/2 + 150*i, gRes.y+40), new Enemy1(-M_PI/2)));
    }

    level.addNewPart(120);
    auto add4 = [&level, gRes](float time, float offset, bool horizontal)
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
        level.addSpaceship(LevelInfo::SpaceshipInfo(time, a + off, new Enemy1(angle)));
        level.addSpaceship(LevelInfo::SpaceshipInfo(time, a - off, new Enemy1(angle)));
        level.addSpaceship(LevelInfo::SpaceshipInfo(time, b + off, new Enemy1(angle + M_PI)));
        level.addSpaceship(LevelInfo::SpaceshipInfo(time, b - off, new Enemy1(angle + M_PI)));
    };
    for (int i = 0; i < 8; i++)
        add4(0.8 * i, 50 * (i + 1), i%2);


    level.addSpaceship(LevelInfo::SpaceshipInfo(25, Vector2f(gRes.x/2, -40), new Enemy3([gRes](const Enemy3&){ return Vector2f(gRes.x/2, gRes.y/2); })));

    return level;
}*/
