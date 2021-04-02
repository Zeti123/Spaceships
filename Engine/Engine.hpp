#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "GameInfo.hpp"
#include "SoundPlayer.hpp"
#include "Collider.hpp"

class PhysicalObject;

class Engine
{
public:
    using ColorType = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;

    Engine(const Engine& e) = delete;
    static Engine& Instance();
    static SoundPlayer& soundPlayer();
    void loadTextures(const std::vector<std::string>& textures);
    void loadSounds(const std::vector<std::string>& sounds);
    GameObject* findObjectById(const std::string& id);
    bool nextFrame();
    void setTimeRate(double timeRate);
    void exit();

private:
    Engine();
    void checkEvents();
    void checkCollisionsWithType(size_t objIndex, Collider& col, Collider::CollisionType type) const;
    void checkCollisions();
    void updateUI();
    void updateGameInfo();

    static Engine* _instance;
    sf::RenderWindow* _window;
    sf::Mouse _mouse;
    sf::Clock _clock;
    sf::Time _time;
    Renderer _renderer;
    SoundPlayer _player;
    double _timeRate;
};

#endif // WINDOW_HPP
