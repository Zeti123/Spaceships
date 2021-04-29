#ifndef LEVELSVIEW_HPP
#define LEVELSVIEW_HPP

#include <LevelButton.hpp>
#include "IMenuView.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"

class LevelsView: public IMenuView
{
public:
    LevelsView(const GameState* gameState, size_t stage);
    void create(MainMenu* parent) override;
    void destroy() override;
    ~LevelsView() = default;

private:
    std::vector<Vector2f> calculateButtonsPosition(size_t buttonsNum, Vector2i buttonsSize) const;
    std::vector<LevelButton*> _levels;
    SimpleButton* _back;
    const GameState* _gameStateRef;
    size_t _stage;
};

#endif // LEVELSVIEW_HPP
