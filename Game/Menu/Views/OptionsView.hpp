#ifndef OPTIONSVIEW_HPP
#define OPTIONSVIEW_HPP

#include "IMenuView.hpp"
#include "Slider.hpp"
#include "SimpleCheckBox.hpp"
#include "SimpleButton.hpp"
#include "GameState.hpp"

class OptionsView: public IMenuView
{
public:
    OptionsView(const GameState* gameState);
    void create(MainMenu* parent) override;
    void destroy() override;
    ~OptionsView() = default;

private:
    Slider* _masterVolume;
    Slider* _musicVolume;
    Slider* _soundVolume;
    SimpleCheckBox* _fullscreen;
    SimpleButton* _back;
    const GameState* _gameStateRef;
};

#endif // OPTIONSVIEW_HPP
