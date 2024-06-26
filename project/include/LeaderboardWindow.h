#pragma once

#include "Window.h"
#include <list>
#include <memory>

struct DataCell {
	std::string m_playerName = "<< empty >>";
	int m_score = 0;
	sf::Text m_lineText;
};

class LeaderboardWindow : public Window {
public:
	LeaderboardWindow(sf::RenderWindow& window, ObjectCreator* objectCreator);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

	bool isScoreValidForBoard(int score) const;
	void insertValue(int score, std::string name);

private:
	sf::Text m_title;
	sf::Text m_backButton;

	std::list<std::unique_ptr<DataCell>> m_data;

	void resetWindow();

	// hover effect
	bool m_currBackButton;
	void updateHover();
};