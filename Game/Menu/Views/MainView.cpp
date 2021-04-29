#include "MainView.hpp"
#include "MainMenu.hpp"
#include "StagesView.hpp"
#include "OptionsView.hpp"

MainView::MainView(const GameState* gameState)
    :_gameStateRef(gameState){}

void MainView::create(MainMenu* parent)
{
    _start = new Button(Vector2f(180, 219), 28, 29, 30, 31, Vector2f(47, 70), Vector2i(232, 282));
    _option = new Button(Vector2f(524, 219), 28, 29, 30, 32, Vector2f(28, 70), Vector2i(232, 282));
    _exit = new Button(Vector2f(868, 219), 28 ,29 ,30, 33, Vector2f(68, 70), Vector2i(232, 282));

    _start->setActive(true);
    _option->setActive(true);
    _exit->setActive(true);

    auto gm = _gameStateRef;
    _start->setCallFunction([gm, parent](){ parent->changeView(new StagesView(gm)); });
    _option->setCallFunction([this, parent](){ parent->changeView(new OptionsView(_gameStateRef)); });
    _exit->setCallFunction([parent](){ parent->setNextAction(MainMenu::Action::END_GAME); });
}

void MainView::destroy()
{
    delete _start;
    delete _option;
    delete _exit;
}

