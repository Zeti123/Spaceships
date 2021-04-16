#ifndef LEVELPASSEDLABEL_HPP
#define LEVELPASSEDLABEL_HPP

#include "GameObject.hpp"
#include "ILevelObject.hpp"

class LevelPassedLabel: public GameObject, public ILevelObject
{
public:
    LevelPassedLabel();
    void onFrame() final;
    void kill() final;
    bool isAlive() final;
    void onDestroy() final;
    bool blockLevel() final;

private:
    double _timeToDeath;
};

#endif // LEVELPASSEDLABEL_HPP
