#pragma once

#include "Window.h"

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

	std::list<std::shared_ptr<DataCell>> m_data;

	void drawLeaderboard();

	void resetWindow();

	// hover effect
	bool m_currBackButton;
	void updateHover();
	bool inputFromFile(const std::string& filename);
	bool updateFile(const std::string& filename);
	bool handleLineInput(std::string& line, int lineNum);
};