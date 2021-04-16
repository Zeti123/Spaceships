#include "LevelPassedLabel.hpp"

#include "Engine.hpp"

LevelPassedLabel::LevelPassedLabel()
    :GameObject(), ILevelObject(), _timeToDeath(6.0) {

    auto size = Vector2f(400, 96);
    setPosition(Vector2f(GameInfo::resolution().x/2 - size.x/2, GameInfo::resolution().y/2 - size.y/2 - 50));
    addTexture(51);
    setActive(true);
}
void LevelPassedLabel::onFrame() { _timeToDeath -= GameInfo::deltaTime(); }
void LevelPassedLabel::kill() { _timeToDeath = 0; }
bool LevelPassedLabel::isAlive() { return _timeToDeath > 0; }
void LevelPassedLabel::onDestroy() {}
bool LevelPassedLabel::blockLevel() { return true; }
