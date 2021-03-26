#ifndef LIFES_HPP
#define LIFES_HPP

class Player;
#include "Vector2f.hpp"
#include "GameObject.hpp"

class Lives : public GameObject
{
public:
    Lives(Vector2f position, Player* spaceship);
    void onFrame() override;
    void addLife();
    void reset();

private:
    Player* _parent;
    size_t _lives;
};

#endif // LIFES_HPP
