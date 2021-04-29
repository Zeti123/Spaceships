#include "OptionsView.hpp"
#include "Engine.hpp"
#include "MainMenu.hpp"
#include "MainView.hpp"

OptionsView::OptionsView(const GameState* gameState)
    :_gameStateRef(gameState) { }

void OptionsView::create(MainMenu* parent)
{
    int posx = (GameInfo::resolution().x - 500) / 2;
    _masterVolume = new Slider(Vector2f(posx, 50), 40, 41, 42, 43, Vector2f(5, 5), Vector2f(72, 100), Vector2i(500, 150), Vector2i(356, 12), Vector2i(44, 44));
    _musicVolume  = new Slider(Vector2f(posx, 240), 40, 41, 42, 44, Vector2f(5, 5), Vector2f(72, 100), Vector2i(500, 150), Vector2i(356, 12), Vector2i(44, 44));
    _soundVolume  = new Slider(Vector2f(posx, 430), 40, 41, 42, 45, Vector2f(5, 5), Vector2f(72, 100), Vector2i(500, 150), Vector2i(356, 12), Vector2i(44, 44));
    _fullscreen   = new SimpleCheckBox(Vector2f(posx + 125, 600), 49, Vector2i(250, 75), 50, Vector2f(188, 15));
    _back         = new SimpleButton(Vector2f(0, GameInfo::resolution().y - 45), 39, Vector2i(150, 45));

    _masterVolume->setCallFunction([](double volume){ Engine::Instance().soundPlayer().setMasterVolume(volume); });
    _musicVolume->setCallFunction([](double volume){ Engine::Instance().soundPlayer().setMusicVolume(volume); });
    _soundVolume->setCallFunction([](double volume){ Engine::Instance().soundPlayer().setSoundVolume(volume); });
    _fullscreen->setCallFunction([](bool checked){ Engine::Instance().switchFullscreenMode(checked);});
    _back->setCallFunction([this, parent](){ parent->changeView(new MainView(_gameStateRef)); });

    _masterVolume->setActive(true);
    _musicVolume->setActive(true);
    _soundVolume->setActive(true);
    _fullscreen->setActive(true);
    _back->setActive(true);

    _masterVolume->setValue(Engine::Instance().soundPlayer().getMasterVolume());
    _musicVolume->setValue(Engine::Instance().soundPlayer().getMusicVolume());
    _soundVolume->setValue(Engine::Instance().soundPlayer().getSoundVolume());
    _fullscreen->setChecked(Engine::Instance().fullscreenMode());
}

void OptionsView::destroy()
{
    delete _masterVolume;
    delete _musicVolume;
    delete _soundVolume;
    delete _fullscreen;
    delete _back;
}

