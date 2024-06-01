#pragma once

#include <SFML/Graphics.hpp>

class MenuWindow {
public:
	MenuWindow(sf::RenderWindow&);

	void handleEvent(const sf::Event&);
	void update(const bool);
	void draw();
	bool startGameSelected();
	bool loadSaveSelected();

private:
	sf::RenderWindow& m_window;
	bool m_startSelected;
	bool m_loadSaveSelected;

	sf::Font m_font;
	sf::Text m_title;
	sf::Text m_subtitle;
	sf::Text m_playButton;
	sf::Text m_loadSaveButton;
	sf::Text m_exitButton;
	
};