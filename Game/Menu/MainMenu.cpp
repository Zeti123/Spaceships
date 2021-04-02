#include "MainMenu.hpp"
#include "Button.hpp"
#include "Engine.hpp"

void MainMenu::openMenu()
{
    _start = new Button(Vector2f(180, 219), 28, 29, 30, 31, Vector2f(47, 70), Vector2i(232, 282));
    _option = new Button(Vector2f(524, 219), 28, 29, 30, 32, Vector2f(28, 70), Vector2i(232, 282));
    _exit = new Button(Vector2f(868, 219), 28 ,29 ,30, 33, Vector2f(68, 70), Vector2i(232, 282));

    _start->setActive(true);
    _option->setActive(true);
    _exit->setActive(true);

    _start->setCallFunction ([this](){ closeMenu(); openLevelsMenu(); });
    _option->setCallFunction([this](){ closeMenu(); openOptions(); });
    _exit->setCallFunction  (std::bind(&MainMenu::exitGame, this));
    _start->setId("button");

    _active = true;
}

void MainMenu::closeMenu()
{
    delete _start;
    delete _option;
    delete _exit;
}

void MainMenu::openOptions()
{
    int posx = (GameInfo::resolution().x - 500) / 2;
    _masterVolume = new Slider(Vector2f(posx, 50), 40, 41, 42, 43, Vector2f(5, 5), Vector2f(72, 110), Vector2i(500, 150), Vector2i(356, 12), Vector2i(44, 44));
    _musicVolume  = new Slider(Vector2f(posx, 250), 40, 41, 42, 44, Vector2f(5, 5), Vector2f(72, 110), Vector2i(500, 150), Vector2i(356, 12), Vector2i(44, 44));
    _soundVolume  = new Slider(Vector2f(posx, 450), 40, 41, 42, 45, Vector2f(5, 5), Vector2f(72, 110), Vector2i(500, 150), Vector2i(356, 12), Vector2i(44, 44));
    _back         = new SimpleButton(Vector2f(0, GameInfo::resolution().y - 45), 39, Vector2i(150, 45));

    _masterVolume->setCallFunction(std::bind(&MainMenu::masterVolume, this, std::placeholders::_1));
    _musicVolume->setCallFunction(std::bind(&MainMenu::musicVolume, this, std::placeholders::_1));
    _soundVolume->setCallFunction(std::bind(&MainMenu::soundVolume, this, std::placeholders::_1));
    _back->setCallFunction([this](){ closeOptions(); openMenu(); });

    _masterVolume->setActive(true);
    _musicVolume->setActive(true);
    _soundVolume->setActive(true);
    _back->setActive(true);

    _masterVolume->setValue(Engine::Instance().soundPlayer().getMasterVolume());
    _musicVolume->setValue(Engine::Instance().soundPlayer().getMusicVolume());
    _soundVolume->setValue(Engine::Instance().soundPlayer().getSoundVolume());

    _masterVolume->setId("master");
    _musicVolume->setId("music");
    _soundVolume->setId("sound");
    _back->setId("back");

    _active = true;

}

void MainMenu::closeOptions()
{
    delete _masterVolume;
    delete _musicVolume;
    delete _soundVolume;
    delete _back;
}

void MainMenu::openLevelsMenu()
{
    int offset = 50;
    int startPointX = (GameInfo::resolution().x - (300 + offset)*_levels.size()) / 2;
    for (size_t i = 0; i < _levels.size(); i++)
    {
        _levels[i] = new SimpleButton(Vector2f(startPointX + (300 + offset) * i, 300), 34 + i, Vector2i(300, 90));
        _levels[i]->setCallFunction([this, i](){ _loadedLevel = i; _active = false; closeLevelsMenu(); });
        _levels[i]->setActive(true);

        _active = true;
    }
    _back = new SimpleButton(Vector2f(0, GameInfo::resolution().y - 45), 39, Vector2i(150, 45));
    _back->setCallFunction([this](){ closeLevelsMenu(); openMenu(); });
    _back->setActive(true);
}

void MainMenu::closeLevelsMenu()
{
    for (auto& b: _levels)
        delete b;

    delete _back;
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
    Engine::Instance().soundPlayer().setSoundVolume(volume * 100);
}

bool MainMenu::isActive() const
{
    return _active;
}

size_t MainMenu::loadedLevel() const
{
    return _loadedLevel;
}
