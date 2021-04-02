#ifndef MAINMENU_H
#define MAINMENU_H

#include "Button.hpp"
#include "SimpleButton.hpp"
#include "Slider.hpp"

class MainMenu
{
public:
    void openMenu();
    void closeMenu();
    void openOptions();
    void closeOptions();
    void openLevelsMenu();
    void closeLevelsMenu();

    void exitGame();

    void masterVolume(float volume);
    void musicVolume(float volume);
    void soundVolume(float volume);

    bool isActive() const;
    size_t loadedLevel() const;

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

    //general use
    SimpleButton* _back;
    bool _active;
    size_t _loadedLevel;
};

#endif // MAINMENU_H
