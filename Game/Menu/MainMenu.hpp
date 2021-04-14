#ifndef MAINMENU_H
#define MAINMENU_H

#include "Button.hpp"
#include "SimpleButton.hpp"
#include "Slider.hpp"
#include <array>

class MainMenu
{
public:
    enum class Action
    {
        NONE,
        LOAD_LEVEL,
        RESUME,
        BACK_TO_MENU,
    };
    void openMenu();
    void openOptions();
    void openLevelsMenu();
    void openPauseMenu();

    void exitGame();

    void masterVolume(float volume);
    void musicVolume(float volume);
    void soundVolume(float volume);

    size_t loadedLevel() const;
    Action nextAction() const;

private:
    void closeMenu();
    void closeOptions();
    void closeLevelsMenu();
    void closePauseMenu();

private:
    // menu
    Button* _start;
    Button* _option;
    Button* _exit;

    // options
    Slider* _masterVolume;
    Slider* _musicVolume;
    Slider* _soundVolume;

    // levels menu
    std::array<SimpleButton*, 3> _levels;

    // pause menu
    SimpleButton* _resume;
    SimpleButton* _backToMenu;

    //general use
    SimpleButton* _back;
    size_t _loadedLevel;
    Action _nextAction;
};

#endif // MAINMENU_H
