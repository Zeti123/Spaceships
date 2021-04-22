#ifndef LEVELMENU_HPP
#define LEVELMENU_HPP

#include "SimpleButton.hpp"
#include "GameState.hpp"

class LevelButton: private SimpleButton
{
public:
    LevelButton(Vector2f position, size_t level, GameState::LevelState lstate);
    void setCallFunction(std::function<void()> call);
    void setActive(bool active);

private:
    bool _unlocked;
};

#endif // LEVELMENU_HPP
