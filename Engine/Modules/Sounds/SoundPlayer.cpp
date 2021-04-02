#include "SoundPlayer.hpp"
#include <iostream>

SoundPlayer::SoundPlayer()
    :_masterVolume(0.5), _musicVolume(0.5), _soundVolume(0.5) {}

void SoundPlayer::loadSounds(const std::vector<std::string>& sounds)
{
    _buffers.resize(sounds.size());
    for (size_t i = 0; i < sounds.size(); i++)
       _buffers[i].loadFromFile(sounds[i]);
}

void SoundPlayer::playSound(size_t soundId, float volume)
{
    if (soundId >= _buffers.size())
        throw "there is no such sound";

    for (size_t i = 0; i < _soundsNumber; i++)
    {
        if (_sound[i].getStatus() == sf::Sound::Status::Stopped)
        {
            _sound[i].setBuffer(_buffers[soundId]);
            _sound[i].setVolume(volume * _soundVolume * _masterVolume);
            _sound[i].play();
            break;
        }
    }
}

void SoundPlayer::stopAllSounds()
{
    for (size_t i = 0; i < _soundsNumber; i++)
        if (_sound[i].getStatus() == sf::Sound::Status::Playing)
            _sound[i].pause();
}

void SoundPlayer::resumeAllSounds()
{
    for (size_t i = 0; i < _soundsNumber; i++)
        if (_sound[i].getStatus() == sf::Sound::Status::Stopped)
            _sound[i].play();
}

void SoundPlayer::playMusic(const std::string& song, float volume)
{
    _music.stop();
    _music.openFromFile(song);
    _currentMusicVolume = volume;
    _music.setVolume(volume * _musicVolume * _masterVolume);
    _music.play();
}

void SoundPlayer::stopMusic()
{
    if (_music.getStatus() == sf::Music::Status::Playing)
        _music.stop();
}

void SoundPlayer::resumeMusic()
{
    if (_music.getStatus() == sf::Music::Status::Stopped)
        _music.play();
}

bool SoundPlayer::isMusicPlayed() const
{
    return _music.getStatus() == sf::Music::Status::Playing;
}

void SoundPlayer::setMasterVolume(float volume)
{
    _masterVolume = volume;
    std::cout<<volume * _musicVolume * _masterVolume<<std::endl;
    _music.setVolume(_currentMusicVolume * _musicVolume * _masterVolume);
}

void SoundPlayer::setMusicVolume(float volume)
{
    _musicVolume = volume;
    _music.setVolume(_currentMusicVolume * _musicVolume * _masterVolume);
}

void SoundPlayer::setSoundVolume(float volume)
{
    _soundVolume = volume;
}

float SoundPlayer::getMasterVolume() const
{
    return _masterVolume;
}

float SoundPlayer::getMusicVolume() const
{
    return _musicVolume;
}

float SoundPlayer::getSoundVolume() const
{
    return _soundVolume;
}
