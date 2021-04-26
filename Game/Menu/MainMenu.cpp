#include "MainMenu.hpp"
#include "Button.hpp"
#include "Engine.hpp"

void MainMenu::openMenu(const GameState& gameState)
{
    _start = new Button(Vector2f(180, 219), 28, 29, 30, 31, Vector2f(47, 70), Vector2i(232, 282));
    _option = new Button(Vector2f(524, 219), 28, 29, 30, 32, Vector2f(28, 70), Vector2i(232, 282));
    _exit = new Button(Vector2f(868, 219), 28 ,29 ,30, 33, Vector2f(68, 70), Vector2i(232, 282));

    _start->setActive(true);
    _option->setActive(true);
    _exit->setActive(true);

    _start->setCallFunction ([this, &gameState](){ closeMenu(); openLevelsMenu(gameState); });
    _option->setCallFunction([this, &gameState](){ closeMenu(); openOptions(gameState); });
    _exit->setCallFunction  (std::bind(&MainMenu::exitGame, this));
    _start->setId("button");

    _nextAction = Action::NONE;
}

void MainMenu::closeMenu()
{
    delete _start;
    delete _option;
    delete _exit;
}

void MainMenu::openOptions(const GameState& gameState)
{
    int posx = (GameInfo::resolution().x - 500) / 2;
    _masterVolume = new Slider(Vector2f(posx, 50), 40, 41, 42, 43, Vector2f(5, 5), Vector2f(72, 100), Vector2i(500, 150), Vector2i(356, 12), Vector2i(44, 44));
    _musicVolume  = new Slider(Vector2f(posx, 240), 40, 41, 42, 44, Vector2f(5, 5), Vector2f(72, 100), Vector2i(500, 150), Vector2i(356, 12), Vector2i(44, 44));
    _soundVolume  = new Slider(Vector2f(posx, 430), 40, 41, 42, 45, Vector2f(5, 5), Vector2f(72, 100), Vector2i(500, 150), Vector2i(356, 12), Vector2i(44, 44));
    _fullscreen   = new SimpleCheckBox(Vector2f(posx + 125, 600), 49, Vector2i(250, 75), 50, Vector2f(188, 15));
    _back         = new SimpleButton(Vector2f(0, GameInfo::resolution().y - 45), 39, Vector2i(150, 45));

    _masterVolume->setCallFunction(std::bind(&MainMenu::masterVolume, this, std::placeholders::_1));
    _musicVolume->setCallFunction(std::bind(&MainMenu::musicVolume, this, std::placeholders::_1));
    _soundVolume->setCallFunction(std::bind(&MainMenu::soundVolume, this, std::placeholders::_1));
    _fullscreen->setCallFunction([](bool checked){ Engine::Instance().switchFullscreenMode(checked);});
    _back->setCallFunction([this, &gameState](){ closeOptions(); openMenu(gameState); });

    _masterVolume->setActive(true);
    _musicVolume->setActive(true);
    _soundVolume->setActive(true);
    _fullscreen->setActive(true);
    _back->setActive(true);

    _masterVolume->setValue(Engine::Instance().soundPlayer().getMasterVolume());
    _musicVolume->setValue(Engine::Instance().soundPlayer().getMusicVolume());
    _soundVolume->setValue(Engine::Instance().soundPlayer().getSoundVolume());
    _fullscreen->setChecked(Engine::Instance().fullscreenMode());

    _nextAction = Action::NONE;

}

void MainMenu::closeOptions()
{
    delete _masterVolume;
    delete _musicVolume;
    delete _soundVolume;
    delete _fullscreen;
    delete _back;
}

void MainMenu::openLevelsMenu(const GameState& gameState)
{
    _levels.resize(gameState.getLevelsNumInGroup(0));

    int offset = 50;
    int rows = (_levels.size() + 2)/3;
    int startPointX = (GameInfo::resolution().x - (300 + offset)*3) / 2;
    int startPointY = ((GameInfo::resolution().y - (90 + offset/2) * rows) / 2);

    for (size_t i = 0; i < _levels.size(); i++)
    {
        auto state = gameState.getLevelState(0, i);
        _levels[i] = new LevelButton(Vector2f(startPointX + (300 + offset) * (i%3), startPointY + (offset/2 + 90)*(i/3)), i, state);
        _levels[i]->setCallFunction([this, i](){ _loadedLevel = i; _nextAction = Action::LOAD_LEVEL; closeLevelsMenu();});
        _levels[i]->setActive(true);

    }
    _back = new SimpleButton(Vector2f(0, GameInfo::resolution().y - 45), 39, Vector2i(150, 45));
    _back->setCallFunction([this, &gameState](){ closeLevelsMenu(); openMenu(gameState); });
    _back->setActive(true);

    _nextAction = Action::NONE;
}

void MainMenu::closeLevelsMenu()
{
    for (auto& b: _levels)
        delete b;

    delete _back;
}

void MainMenu::openPauseMenu()
{
    Vector2i size(400, 120);
    _resume = new SimpleButton(Vector2f(GameInfo::resolution().x/2 - size.x/2, GameInfo::resolution().y/2 - 250), 46, size);
    _backToMenu = new SimpleButton(Vector2f(GameInfo::resolution().x/2 - size.x/2, GameInfo::resolution().y/2), 47, size);

    _resume->setCallFunction([this](){ _nextAction = Action::RESUME; closePauseMenu(); });
    _backToMenu->setCallFunction([this](){ _nextAction = Action::BACK_TO_MENU; closePauseMenu();});

    _resume->setActive(true);
    _backToMenu->setActive(true);

    _nextAction = Action::NONE;
}

void MainMenu::closePauseMenu()
{
    delete _resume;
    delete _backToMenu;
}

void MainMenu::exitGame()
{
    std::cout<<"the end"<<std::endl;
    Engine::Instance().exit();
}

void MainMenu::masterVolume(float volume)
{
    Engine::Instance().soundPlayer().setMasterVolume(volume);
}

void MainMenu::musicVolume(float volume)
{
    Engine::Instance().soundPlayer().setMusicVolume(volume);
}

void MainMenu::soundVolume(float volume)
{
    Engine::Instance().soundPlayer().setSoundVolume(volume);
}

size_t MainMenu::loadedLevel() const
{
    return _loadedLevel;
}

MainMenu::Action MainMenu::nextAction() const
{
    return _nextAction;
}
