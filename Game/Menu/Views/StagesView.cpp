#include "StagesView.hpp"
#include "MainMenu.hpp"
#include "LevelsView.hpp"
#include "MainView.hpp"

StagesView::StagesView(const GameState* gameState)
    :_gameStateRef(gameState){}

void StagesView::create(MainMenu* parent)
{
    _stages.resize(_gameStateRef->getGroupsNum());
    auto positions = calculateButtonsPosition(_stages.size(), Vector2i(300, 90));
    for (size_t i = 0; i < _stages.size(); i++)
    {
        _stages[i] = new LevelButton(positions[i], 23 + i, {_gameStateRef->isGroupUnlocked(i), 0});
        _stages[i]->setActive(true);
        _stages[i]->setCallFunction([this, parent, i](){ parent->changeView(new LevelsView(_gameStateRef, i)); });
    }
    _back = new SimpleButton(Vector2f(0, GameInfo::resolution().y - 45), 39, Vector2i(150, 45));
    _back->setCallFunction([this, parent](){ parent->changeView(new MainView(_gameStateRef)); });
    _back->setActive(true);
}

void StagesView::destroy()
{
    for (auto ptr: _stages)
         delete ptr;

    _stages.clear();
    delete _back;
}

std::vector<Vector2f> StagesView::calculateButtonsPosition(size_t buttonsNum, Vector2i buttonsSize) const
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
