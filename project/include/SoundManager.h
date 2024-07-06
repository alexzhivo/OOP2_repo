#pragma once

#include <SFML/Audio.hpp>

#include <string>
#include <memory>
#include <unordered_map>

class SoundManager {
public:
    SoundManager();

    void playSound(const std::string& name);
    void playMusic(const std::string& name, bool loop);
    void stopMusic(const std::string& name);

private:
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> musicTracks;
    std::vector<sf::Sound> sounds; // Container to keep sounds alive

    bool loadSound(const std::string& name, const std::string& filename);
    bool loadMusic(const std::string& name, const std::string& filename);
};

