TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

LIBS += -Wall -Wshadow -Wextra -Wuninitialized -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += \
    $$PWD/Engine \
    $$PWD/Engine/Modules \
    $$PWD/Engine/Modules/Collisions \
    $$PWD/Engine/Modules/Graphics \
    $$PWD/Engine/Modules/Sounds \
    $$PWD/Engine/Objects \
    $$PWD/Engine/UI \
    $$PWD/Game \
    $$PWD/Game/Gamerule \
    $$PWD/Game/Gamerule/LevelObjects \
    $$PWD/Game/Gamerule/LevelObjects/Bullets \
    $$PWD/Game/Gamerule/LevelObjects/Enemys \
    $$PWD/Game/Gamerule/LevelObjects/Enemys/Part1 \
    $$PWD/Game/Gamerule/LevelObjects/Player \
    $$PWD/Game/Menu \
    $$PWD/Game/Resources \
    $$PWD/Game/Resources/Images \
    $$PWD/Game/Resources/Sounds \
    $$PWD/Spaceships \

SOURCES += \
        Engine/Engine.cpp \
        Engine/GameInfo.cpp \
        Engine/MainClass.cpp \
        Engine/Modules/Collisions/Collider.cpp \
        Engine/Modules/Graphics/Renderer.cpp \
        Engine/Modules/Graphics/TextureContainer.cpp \
        Engine/Modules/Sounds/SoundPlayer.cpp \
        Engine/Objects/GameObject.cpp \
        Engine/Objects/PhysicalObject.cpp \
        Engine/Objects/UIObject.cpp \
        Engine/Position2D.cpp \
        Engine/UI/Button.cpp \
        Engine/UI/Slider.cpp \
        Engine/Vector2f.cpp \
        Engine/Vector2i.cpp \
        Game/Gamerule/Game.cpp \
        Game/Gamerule/LevelInfo.cpp \
        Game/Gamerule/LevelManager.cpp \
        Game/Gamerule/LevelObjects/Bullets/Bullet.cpp \
        Game/Gamerule/LevelObjects/Bullets/BulletShutter.cpp \
        Game/Gamerule/LevelObjects/Bullets/SimpleBullet.cpp \
        Game/Gamerule/LevelObjects/Enemys/Part1/Enemy1.cpp \
        Game/Gamerule/LevelObjects/Enemys/Part1/Enemy2.cpp \
        Game/Gamerule/LevelObjects/Enemys/Part1/Enemy3.cpp \
        Game/Gamerule/LevelObjects/Enemys/Part1/Enemy4.cpp \
        Game/Gamerule/LevelObjects/Enemys/Part1/Enemy5.cpp \
        Game/Gamerule/LevelObjects/Enemys/Part1/Enemy6.cpp \
        Game/Gamerule/LevelObjects/PickUp.cpp \
        Game/Gamerule/LevelObjects/Player/HpBar.cpp \
        Game/Gamerule/LevelObjects/Player/Lives.cpp \
        Game/Gamerule/LevelObjects/Player/Player.cpp \
        Game/Gamerule/LevelObjects/Spaceship.cpp \
        Game/Menu/MainMenu.cpp \
        main.cpp

DISTFILES += \
    Game/Resources/Images/boss.png \
    Game/Resources/Images/boss_kill.png \
    Game/Resources/Images/boss_kill2.png \
    Game/Resources/Images/boss_kill3.png \
    Game/Resources/Images/bullet_animation.png \
    Game/Resources/Images/bullet_green.png \
    Game/Resources/Images/bullet_red.png \
    Game/Resources/Images/bullet_super_green.png \
    Game/Resources/Images/button_clicked.png \
    Game/Resources/Images/button_dragged.png \
    Game/Resources/Images/button_normal.png \
    Game/Resources/Images/enemy1.png \
    Game/Resources/Images/enemy2.png \
    Game/Resources/Images/enemy3.png \
    Game/Resources/Images/enemy4.png \
    Game/Resources/Images/enemy5.png \
    Game/Resources/Images/enemy6.png \
    Game/Resources/Images/heart.png \
    Game/Resources/Images/hp_bar_center.png \
    Game/Resources/Images/hp_bar_empty.png \
    Game/Resources/Images/hp_bar_shield.png \
    Game/Resources/Images/label_exit.png \
    Game/Resources/Images/label_options.png \
    Game/Resources/Images/label_start.png \
    Game/Resources/Images/lives.png \
    Game/Resources/Images/pickup_hp.png \
    Game/Resources/Images/pickup_life.png \
    Game/Resources/Images/pickup_shield.png \
    Game/Resources/Images/pickup_supershot.png \
    Game/Resources/Images/player.png \
    Game/Resources/Images/player_immortal.png \
    Game/Resources/Images/player_immortal_shield.png \
    Game/Resources/Images/player_shield.png \
    Game/Resources/Images/rocket.png \
    Game/Resources/Sounds/additional_hp.wav \
    Game/Resources/Sounds/additional_life.wav \
    Game/Resources/Sounds/boss3.wav \
    Game/Resources/Sounds/hit.wav \
    Game/Resources/Sounds/laser_sound.wav \
    Game/Resources/Sounds/rocket_shoot_v3.wav \
    Game/Resources/Sounds/shield.wav

HEADERS += \
    Engine/Engine.hpp \
    Engine/GameInfo.hpp \
    Engine/MainClass.hpp \
    Engine/Modules/Collisions/Collider.hpp \
    Engine/Modules/Graphics/Renderer.hpp \
    Engine/Modules/Graphics/TextureContainer.hpp \
    Engine/Modules/Sounds/SoundPlayer.hpp \
    Engine/Objects/GameObject.hpp \
    Engine/Objects/PhysicalObject.hpp \
    Engine/Objects/UIObject.hpp \
    Engine/Position2D.hpp \
    Engine/UI/Button.hpp \
    Engine/UI/Slider.hpp \
    Engine/Vector2f.hpp \
    Engine/Vector2i.hpp \
    Game/Gamerule/Game.hpp \
    Game/Gamerule/ILevelObject.hpp \
    Game/Gamerule/LevelInfo.hpp \
    Game/Gamerule/LevelManager.hpp \
    Game/Gamerule/LevelObjects/Bullets/Bullet.hpp \
    Game/Gamerule/LevelObjects/Bullets/BulletShutter.hpp \
    Game/Gamerule/LevelObjects/Bullets/SimpleBullet.hpp \
    Game/Gamerule/LevelObjects/Enemys/Part1/Enemy1.hpp \
    Game/Gamerule/LevelObjects/Enemys/Part1/Enemy2.hpp \
    Game/Gamerule/LevelObjects/Enemys/Part1/Enemy3.hpp \
    Game/Gamerule/LevelObjects/Enemys/Part1/Enemy4.hpp \
    Game/Gamerule/LevelObjects/Enemys/Part1/Enemy5.hpp \
    Game/Gamerule/LevelObjects/Enemys/Part1/Enemy6.hpp \
    Game/Gamerule/LevelObjects/PickUp.hpp \
    Game/Gamerule/LevelObjects/Player/HpBar.hpp \
    Game/Gamerule/LevelObjects/Player/Lives.hpp \
    Game/Gamerule/LevelObjects/Player/Player.hpp \
    Game/Gamerule/LevelObjects/Spaceship.hpp \
    Game/Menu/MainMenu.hpp
