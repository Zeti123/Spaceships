#include "LevelEndLabel.hpp"

#include "Engine.hpp"
#include "LevelManager.hpp"

LevelEndLabel::LevelEndLabel(bool passed)
    :GameObject(), ILevelObject(), _timeToDeath(6.0), _passed(passed) {

    auto size = Vector2f(_passed ? 460 : 400, 96);
    setPosition(Vector2f(GameInfo::resolution().x/2 - size.x/2, GameInfo::resolution().y/2 - size.y/2 - 50));
    addTexture(51);
    setActive(true);
}
void LevelEndLabel::onFrame()
{
    _timeToDeath -= GameInfo::deltaTime();
    if (static_cast<int>(_timeToDeath*2)%2 == 0)
        setTexture(_passed ? 52 : 54);
    else
        setTexture(_passed ? 51 : 53);
}
void LevelEndLabel::kill() { _timeToDeath = 0; }
bool LevelEndLabel::isAlive() { return _timeToDeath > 0; }
void LevelEndLabel::onDestroy()
{
    LevelManager::Instance().endLevel(_passed ? LevelManager::LevelStatus::PASSED : LevelManager::LevelStatus::NOT_PASSED);
}
bool LevelEndLabel::blockLevel() { return true; }
