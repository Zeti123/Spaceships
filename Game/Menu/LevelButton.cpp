#include "LevelButton.hpp"
#include "Game.hpp"

LevelButton::LevelButton(Vector2f position, size_t level, GameState::LevelState lstate)
    :SimpleButton(position, level + 34, Vector2i(300, 90)), _unlocked(true)
{
    if (!lstate.unlocked)
    {
        addTexture(55);
        texture(1).offsetPosition = Vector2f((300 - 90)/2, 57);
        _unlocked = false;
        setDraggedColor({255, 255, 255, 255});
        setClickedColor({255, 255, 255, 255});
    }

    if (lstate.passed)
    {
        addTexture(56);
        addTexture(56);
        texture(1).offsetPosition = Vector2f(10, ((90 - 50)/2));
        texture(2).offsetPosition = Vector2f(290 - 50, ((90 - 50)/2));
    }
}

void LevelButton::setCallFunction(std::function<void()> call)
{
    if (_unlocked)
        SimpleButton::setCallFunction(call);
    else
        SimpleButton::setCallFunction([](){});
}

void LevelButton::setActive(bool active)
{
    GameObject::setActive(active);
}
