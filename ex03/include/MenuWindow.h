#pragma once

#include <SFML/Graphics.hpp>

class MenuWindow {
public:
	MenuWindow(sf::RenderWindow& m_window);

	void handleEvent(const sf::Event& event);
	void update();
	void draw();
	bool startGameSelected() const;
	void resetMenu();

private:
	sf::RenderWindow& m_window;
	sf::Font m_font;
	sf::Text m_title;
	sf::Text m_playButton;
	sf::Text m_exitButton;
	bool m_startSelected;
};