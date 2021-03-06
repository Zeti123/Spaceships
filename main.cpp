#include <iostream>
#include "Player.hpp"
#include "Engine.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "MainView.hpp"

using namespace std;

int main()
{
    Engine& w = Engine::Instance();
    std::string texturesPath = "Images/";
    std::vector<std::string> textures = {"player.png",                       // player                   0 - 3
                                         "player_shield.png",
                                         "player_immortal.png",
                                         "player_immortal_shield.png",
                                         "bullet_green.png",                 // normals bullets          4 - 8
                                         "bullet_super_green.png",
                                         "bullet_red.png",
                                         "rocket.png",
                                         "bullet_animation.png",
                                         "enemy1.png",                       // enemys form first part   9 - 14
                                         "enemy2.png",
                                         "enemy3.png",
                                         "enemy4.png",
                                         "enemy5.png",
                                         "enemy6.png",
                                         "boss.png",                         // boss 1                   15 - 18
                                         "boss_kill.png",
                                         "boss_kill2.png",
                                         "boss_kill3.png",
                                         "pickup_hp.png",                    // pickups                  19 - 22
                                         "pickup_shield.png",
                                         "pickup_supershot.png",
                                         "pickup_life.png",
                                         "lifes.png",                        // player hp bar            23 - 27
                                         "heart.png",
                                         "hp_bar_center.png",
                                         "hp_bar_empty.png",
                                         "hp_bar_shield.png",
                                         "button_normal.png",                // menu buttons, bars       28 - 47
                                         "button_dragged.png",
                                         "button_clicked.png",
                                         "label_start.png",
                                         "label_options.png",
                                         "label_exit.png",
                                         "button_level1.png",
                                         "button_level2.png",
                                         "button_level3.png",
                                         "button_level4.png",
                                         "button_level5.png",
                                         "button_back.png",
                                         "progressbar_background.png",
                                         "progressbar_bar.png",
                                         "progressbar_ball.png",
                                         "master_volume.png",
                                         "music_volume.png",
                                         "sound_volume.png",
                                         "button_resume.png",
                                         "button_backtomenu.png",
                                         "bullet_v.png",                     // new bullet               48
                                         "fullscreen_checkbox.png",          // fullscreen checkbox      49 - 50
                                         "fullscreen_checkbox_check.png",
                                         "level_passed_label1.png",          // level end labels         51 - 54
                                         "level_passed_label2.png",
                                         "game_over_label1.png",
                                         "game_over_label2.png",
                                         "locked_label.png",                 // level passed, not passed markers 55 - 56
                                         "level_button_passed.png",
                                         "stage_1.png",                      // stage buttons                    57 - 59
                                         "stage_2.png",
                                         "stage_3.png",
                                         "explosion_animation.png"};         // explosion animation              60

    std::string soundsPath = "Sounds/";
    std::vector<std::string> sounds = {"hit.wav",
                                       "laser_sound.wav",
                                       "additional_hp.wav",
                                       "additional_life.wav",
                                       "shield.wav",
                                       "super_shoots.ogg",
                                       "supershots.wav",
                                       "explosion.ogg"};
    for (auto& filename: textures)
        filename = texturesPath + filename;
    for (auto& filename: sounds)
        filename = soundsPath + filename;

    w.loadTextures(textures);
    w.loadSounds(sounds);
    Game game;
    try
    {
        while (w.nextFrame());
    }
    catch(const char* bladsystemy)
    {
        cout<<bladsystemy<<endl;
    }

    return 0;
}
