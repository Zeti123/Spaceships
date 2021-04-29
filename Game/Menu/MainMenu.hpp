#ifndef MAINMENU_H
#define MAINMENU_H

#include "Button.hpp"
#include "SimpleButton.hpp"
#include "SimpleCheckBox.hpp"
#include "Slider.hpp"
#include "LevelButton.hpp"
#include "IMenuView.hpp"
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
        END_GAME
    };

    struct LoadedLevel
    {
        size_t stage;
        size_t level;
    };

public:
    MainMenu();
    void update();
    void changeView(IMenuView* newView);
    void setNextAction(Action action);
    void setLoadedLevel(LoadedLevel loadedLevel);
    Action getAction() const;
    LoadedLevel getLoadedLevel() const;


private:
    IMenuView* _currentView;
    IMenuView* _nextView;
    LoadedLevel _loadedLevel;
    Action _nextAction;
    bool _viewChanged;
};

#endif // MAINMENU_H
