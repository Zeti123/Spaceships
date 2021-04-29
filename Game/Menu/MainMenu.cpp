#include "MainMenu.hpp"
#include "Button.hpp"
#include "Engine.hpp"
#include "IMenuView.hpp"

MainMenu::MainMenu()
    :_currentView(nullptr), _nextView(nullptr), _loadedLevel({}), _nextAction(Action::NONE), _viewChanged(false) {}

void MainMenu::update()
{
    if (_viewChanged)
    {
        if (_currentView != nullptr)
            _currentView->destroy();

        if (_nextView != nullptr)
            _nextView->create(this);

        delete _currentView;
        _currentView = _nextView;
        _nextView = nullptr;

        _viewChanged = false;
    }
    _nextAction = Action::NONE;
}

void MainMenu::changeView(IMenuView* newView)
{
    _viewChanged = true;
    _nextView = newView;
}

void MainMenu::setNextAction(Action action)
{
    _nextAction = action;
}

void MainMenu::setLoadedLevel(LoadedLevel loadedLevel)
{
    _loadedLevel = loadedLevel;
}

MainMenu::Action MainMenu::getAction() const
{
    return _nextAction;
}

MainMenu::LoadedLevel MainMenu::getLoadedLevel() const
{
    return _loadedLevel;
}
