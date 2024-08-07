#pragma once

#include "Window.h"

enum class Setting {
	GAMESOUND,
	GAMEMUSIC,
	PLAYERNAME,
	BACK,
	NONE
};

// operators for enum class
Setting& operator++(Setting& setting);
Setting& operator--(Setting& setting);

class SettingsWindow : public Window {
public:
	SettingsWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

	std::string getPlayerName() const;

private:
	sf::Text m_title;
	sf::Text m_gameSoundText;
	sf::Text m_gameMusicText;
	sf::Text m_playerNameText;
	sf::Text m_backButtonText;

	Setting m_settingHover;
	void resetWindow();
	void updateHover();
	void updateGameSoundText();
	void resetHover();

	bool m_isEditName;
	std::string m_playerName;

};