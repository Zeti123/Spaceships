#ifndef PAUSEVIEW_HPP
#define PAUSEVIEW_HPP

#include "IMenuView.hpp"
#include "GameState.hpp"
#include "SimpleButton.hpp"

class PauseView: public IMenuView
{
public:
    PauseView();
    void create(MainMenu* parent) override;
    void destroy() override;
    ~PauseView() = default;

private:
    SimpleButton* _resume;
    SimpleButton* _backToMenu;
};

#endif // PAUSEVIEW_HPP
