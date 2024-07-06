#include "SoundManager.h"

SoundManager::SoundManager()
{
    loadMusic("theme_music", "stardust_music.mp3");
    
}

bool SoundManager::loadSound(const std::string& name, const std::string& filename)
{
    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(filename)) {
        return false;
    }
    soundBuffers[name] = std::move(buffer);
    return true;
}

void SoundManager::playSound(const std::string& name)
{
    if (soundBuffers.find(name) != soundBuffers.end()) {
        sf::Sound sound;
        sound.setBuffer(*soundBuffers[name]);
        sound.play();
        sounds.push_back(std::move(sound)); // Store sound to keep it alive while playing
    }
}

// Load music and associate it with a name
bool SoundManager::loadMusic(const std::string& name, const std::string& filename)
{
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filename)) {
        return false;
    }
    musicTracks[name] = std::move(music);
    musicTracks[name]->setVolume(2.f);
    return true;
}

// Play music by name
void SoundManager::playMusic(const std::string & name, bool loop = false)
{
    if (musicTracks.find(name) != musicTracks.end()) {
        auto& music = musicTracks[name];
        music->setLoop(loop);
        music->play();
    }
}

// Stop music by name
void SoundManager::stopMusic(const std::string& name)
{
    if (musicTracks.find(name) != musicTracks.end()) {
        musicTracks[name]->stop();
    }
}