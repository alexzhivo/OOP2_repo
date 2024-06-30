#pragma once

#include "Window.h"

enum class Setting {
	GAMESOUND,
	PLAYERNAME,
	BACK,
	NONE
};

// operators for enum class
Setting& operator++(Setting& setting);
Setting& operator--(Setting& setting);

class SettingsWindow : public Window {
public:
	SettingsWindow(sf::RenderWindow& window, ObjectCreator* objectCreator);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

private:
	sf::Text m_title;
	sf::Text m_gameSoundText;
	sf::Text m_playerNameText;
	sf::Text m_backButtonText;

	Setting m_settingHover;
	void resetWindow();
	void updateHover();
	void updateGameSound();
	void resetHover();

	bool m_isGameSoundOn;
	bool m_isEditName;
	std::string m_playerName;

};