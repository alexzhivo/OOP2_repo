#pragma once

#include <SFML/Audio.hpp>

#include <string>
#include <memory>
#include <unordered_map>

struct SoundSlot {
    sf::SoundBuffer buffer;
    sf::Sound sound;
};

class SoundManager {
public:
    SoundManager();

    void playSound(const std::string& name, bool loop);
    void stopSound(const std::string& name);

private:
    void loadSounds();
    bool addSound(const std::string& name, const std::string& filepath, float volume);

    std::unordered_map<std::string, std::unique_ptr<SoundSlot>> m_sounds;
};

