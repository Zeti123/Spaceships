#include "PauseView.hpp"
#include "MainMenu.hpp"

PauseView::PauseView() {}

void PauseView::create(MainMenu* parent)
{
    Vector2i size(400, 120);
    _resume = new SimpleButton(Vector2f(GameInfo::resolution().x/2 - size.x/2, GameInfo::resolution().y/2 - 250), 46, size);
    _backToMenu = new SimpleButton(Vector2f(GameInfo::resolution().x/2 - size.x/2, GameInfo::resolution().y/2), 47, size);

    _resume->setCallFunction([parent](){ parent->setNextAction(MainMenu::Action::RESUME); parent->changeView(nullptr); });
    _backToMenu->setCallFunction([parent](){ parent->changeView(nullptr); parent->setNextAction(MainMenu::Action::BACK_TO_MENU); });

    _resume->setActive(true);
    _backToMenu->setActive(true);
}

void PauseView::destroy()
{
    delete _resume;
    delete _backToMenu;
}
