#ifndef SOUNDCONTAINER_HPP
#define SOUNDCONTAINER_HPP
#include <SFML/Audio.hpp>

class SoundPlayer
{
public:
    SoundPlayer();
    void loadSounds(const std::vector<std::string>& sounds);
    void playSound(size_t soundId, float volume = 100.0);
    void stopAllSounds();
    void resumeAllSounds();

    void playMusic(const std::string& song, float volume = 100.0);
    void stopMusic();
    void resumeMusic();

    void setMasterVolume(float volume);
    void setMusicVolume(float volume);
    void setSoundVolume(float volume);

    float getMasterVolume() const;
    float getMusicVolume() const;
    float getSoundVolume() const;

private:
    static constexpr size_t _soundsNumber = 26;
    std::vector<sf::SoundBuffer> _buffers;
    sf::Sound _sound[_soundsNumber];
    sf::Music _music;

    float _currentMusicVolume;

    float _masterVolume;
    float _musicVolume;
    float _soundVolume;
};

#endif // SOUNDCONTAINER_HPP
