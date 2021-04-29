#include "LevelsView.hpp"
#include "MainMenu.hpp"
#include "StagesView.hpp"

LevelsView::LevelsView(const GameState* gameState, size_t stage)
    :_gameStateRef(gameState), _stage(stage) {}

void LevelsView::create(MainMenu* parent)
{
    _levels.resize(_gameStateRef->getLevelsNumInGroup(_stage));

    auto buttonsPositions = calculateButtonsPosition(_levels.size(), Vector2i(300, 90));
    for (size_t i = 0; i < _levels.size(); i++)
    {
        auto state = _gameStateRef->getLevelState(_stage, i);
        _levels[i] = new LevelButton(buttonsPositions[i], i, state);
        _levels[i]->setCallFunction([this, parent, i](){ parent->changeView(nullptr); parent->setNextAction(MainMenu::Action::LOAD_LEVEL); parent->setLoadedLevel({_stage, i}); });
        _levels[i]->setActive(true);

    }
    _back = new SimpleButton(Vector2f(0, GameInfo::resolution().y - 45), 39, Vector2i(150, 45));
    _back->setCallFunction([this, parent](){ parent->changeView(new StagesView(_gameStateRef)); });
    _back->setActive(true);
}

void LevelsView::destroy()
{
    for (auto& b: _levels)
        delete b;

    _levels.clear();
    delete _back;
}

std::vector<Vector2f> LevelsView::calculateButtonsPosition(size_t buttonsNum, Vector2i buttonsSize) const
{
    std::vector<Vector2f> positions;
    auto addToRow = [buttonsSize](double height, size_t num, std::vector<Vector2f>& to) -> void
    {
        constexpr double offsetX = 50;
        double startX = (GameInfo::resolution().x - num * buttonsSize.x - (num - 1) * offsetX) / 2;
        for (size_t i = 0; i < num; i++)
            to.emplace_back(startX + i*(buttonsSize.x + offsetX), height);
    };

    auto buttonsInRow = [](size_t rowNum, size_t buttonsNum) -> size_t
    {
        return std::min(buttonsNum - rowNum*3, 3ul);
    };

    size_t rows = (buttonsNum+2)/3;
    constexpr double offsetY = 30;
    double startY = (GameInfo::resolution().y - rows * buttonsSize.y - (rows - 1) * offsetY) / 2;
    for (size_t i = 0; i < rows; i++)
    {
        double height = startY + i*(buttonsSize.y + offsetY);
        addToRow(height, buttonsInRow(i, buttonsNum), positions);
    }
    return positions;
}
