#ifndef LIFES_HPP
#define LIFES_HPP

class Player;
#include "Vector2f.hpp"
#include "GameObject.hpp"

class Lifes : public GameObject
{
public:
    Lifes(Vector2f position, Player* spaceship);
    void onFrame() override;
    void addLife();
    void reset();

private:
    Player* _parent;
    size_t _lifes;
};

#endif // LIFES_HPP
