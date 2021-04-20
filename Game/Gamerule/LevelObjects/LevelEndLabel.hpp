#ifndef LEVELPASSEDLABEL_HPP
#define LEVELPASSEDLABEL_HPP

#include "GameObject.hpp"
#include "ILevelObject.hpp"

class LevelEndLabel: public GameObject, public ILevelObject
{
public:
    LevelEndLabel(bool passed);
    void onFrame() final;
    void kill() final;
    bool isAlive() final;
    void onDestroy() final;
    bool blockLevel() final;

private:
    double _timeToDeath;
    bool _passed;
};

#endif // LEVELPASSEDLABEL_HPP
