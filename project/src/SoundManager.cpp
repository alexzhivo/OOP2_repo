#include "SoundManager.h"

#include <iostream>

SoundManager::SoundManager()
    : m_soundOn(true), m_musicOn(true)
{
    loadSounds();
}

void SoundManager::loadSounds()
{
    addSound("theme_music", "stardust_music.mp3", 2.f);
    addSound("game_music", "game_music.mp3", 1.f);

    addSound("select", "select_sound.mp3",2.f);
    addSound("add_pts", "collect_pts.mp3",1.f);
    addSound("game_start", "game_start.mp3",2.f);
    addSound("game_lose", "game_lose.mp3", 2.f);
    addSound("not_break", "not_break.mp3",1.f);
    addSound("lose_ball", "lose_ball.mp3", 2.f);
    addSound("pop_once", "pop_once.mp3", 2.f);
    addSound("hover", "hover_sound.wav",2.f);
    addSound("game_win", "game_win.wav",2.f);
    addSound("level_up", "level_up.wav", 2.f);
}

bool SoundManager::addSound(const std::string& name, const std::string& filepath, float volume)
{
    auto soundSlot = std::make_unique<SoundSlot>();
    if (!soundSlot->buffer.loadFromFile(filepath)) {
        std::cerr << "Error : " + filepath + " Not Found!\n";
        return false;
    }
    soundSlot->sound.setBuffer(soundSlot->buffer);
    soundSlot->sound.setVolume(volume);
    m_sounds[name] = std::move(soundSlot);
    return true;
}

void SoundManager::playSound(const std::string& name, bool loop = false)
{
    if (m_sounds.find(name) != m_sounds.end()) {
        auto& slot = m_sounds[name];
        slot->sound.setLoop(loop);
        slot->sound.play();
    }
}

void SoundManager::stopSound(const std::string& name)
{
    if (m_sounds.find(name) != m_sounds.end()) {
        auto& slot = m_sounds[name];
        slot->sound.stop();
    }
}

void SoundManager::muteSound(bool mute)
{
    if (mute) {
        m_sounds["select"]->sound.setVolume(0.f);
        m_sounds["add_pts"]->sound.setVolume(0.f);
        m_sounds["game_start"]->sound.setVolume(0.f);
        m_sounds["game_lose"]->sound.setVolume(0.f);
        m_sounds["not_break"]->sound.setVolume(0.f);
        m_sounds["lose_ball"]->sound.setVolume(0.f);
        m_sounds["pop_once"]->sound.setVolume(0.f);
        m_sounds["hover"]->sound.setVolume(0.f);
        m_sounds["game_win"]->sound.setVolume(0.f);
        m_sounds["level_up"]->sound.setVolume(0.f);
    }
    else {
        m_sounds["select"]->sound.setVolume(2.f);
        m_sounds["add_pts"]->sound.setVolume(1.f);
        m_sounds["game_start"]->sound.setVolume(2.f);
        m_sounds["game_lose"]->sound.setVolume(2.f);
        m_sounds["not_break"]->sound.setVolume(1.f);
        m_sounds["lose_ball"]->sound.setVolume(2.f);
        m_sounds["pop_once"]->sound.setVolume(2.f);
        m_sounds["hover"]->sound.setVolume(2.f);
        m_sounds["game_win"]->sound.setVolume(2.f);
        m_sounds["level_up"]->sound.setVolume(2.f);
    }

    m_soundOn = !mute;
}

void SoundManager::muteMusic(bool mute)
{
    if (mute) {
        m_sounds["theme_music"]->sound.setVolume(0.f);
        m_sounds["game_music"]->sound.setVolume(0.f);
    }
    else {
        m_sounds["theme_music"]->sound.setVolume(2.f);
        m_sounds["game_music"]->sound.setVolume(1.f);
    }

    m_musicOn = !mute;
}

bool SoundManager::isSoundMute() const
{
    return !m_soundOn;
}

bool SoundManager::isMusicMute() const
{
    return !m_musicOn;
}