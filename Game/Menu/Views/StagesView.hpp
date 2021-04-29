#ifndef STAGESVIEW_HPP
#define STAGESVIEW_HPP

#include "IMenuView.hpp"
#include "GameState.hpp"
#include "LevelButton.hpp"

class StagesView: public IMenuView
{
public:
    StagesView(const GameState* gameState);
    void create(MainMenu* parent) override;
    void destroy() override;
    ~StagesView() = default;

private:
    std::vector<Vector2f> calculateButtonsPosition(size_t buttonsNum, Vector2i buttonsSize) const;
    std::vector<LevelButton*> _stages;
    SimpleButton* _back;
    const GameState* _gameStateRef;
};

#endif // STAGESVIEW_HPP
