#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include "IMenuView.hpp"
#include "Button.hpp"
#include "GameState.hpp"

class MainView: public IMenuView
{
public:
    MainView(const GameState* gameState);
    void create(MainMenu* parent) override;
    void destroy() override;
    ~MainView() = default;

private:
    Button* _start;
    Button* _option;
    Button* _exit;
    const GameState* _gameStateRef;
};

#endif // MAINVIEW_HPP
