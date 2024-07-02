#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
    : Window(window,objectCreator), m_currBackButton(false)
{
    m_title = objectCreator->createTextButton("LEADERBOARD", 70, 'W', 400.f, 100.f);
    m_backButton = objectCreator->createTextButton("<< BACK >>", 20, 'G', 600.f, 800.f);

    // initilize leaderboard
    for (int i = 0; i < 10; i++) {
        m_data.push_back(std::make_shared<DataCell>());
        m_data.back()->m_lineText = objectCreator->createTextButton(std::to_string(i + 1) + ".\t\t<EMPTY>\t\t:", 20, 'W', 550.f, 250.f + (i * 50));
    }
}

UserChoice LeaderboardWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter && m_currBackButton) {
            choice.isSelected = true;
            choice.nextWindow = WindowState::MENU;
            resetWindow();
        }
        else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up) {
            if (m_currBackButton)
                m_currBackButton = false;
            else
                m_currBackButton = true;
            updateHover();
        }
    }
    return choice;
}

void LeaderboardWindow::update(float dt)
{
}

void LeaderboardWindow::render()
{
    m_window.draw(m_title);
    m_window.draw(m_backButton);
    drawLeaderboard();
}

void LeaderboardWindow::resetWindow()
{
    m_currBackButton = false;
    updateHover();
}

void LeaderboardWindow::drawLeaderboard()
{
    int index = 1;
    for (auto& line : m_data) {
        std::string lineStr = std::to_string(index) + ".\t" + line->m_playerName + "\t\t" + std::to_string(line->m_score);
        line->m_lineText.setString(lineStr);
        m_window.draw(line->m_lineText);
        index++;
    }
}

void LeaderboardWindow::updateHover()
{
    if (m_currBackButton) {
        m_backButton.setFillColor(sf::Color::White);
    }
    else {
        m_backButton.setFillColor(sf::Color(100, 100, 100));
    }
}

bool LeaderboardWindow::isScoreValidForBoard(int score) const
{
    if (m_data.back()->m_score < score)
        return true;
    return false;
}

void LeaderboardWindow::insertValue(int score, std::string name)
{
    if (!isScoreValidForBoard(score)) {
        std::cout << "Score is not high enough for leaderboard insertion.\n";
        return;
    }

    auto newEntry = std::make_shared<DataCell>();
    newEntry->m_playerName = name;
    newEntry->m_score = score;
    newEntry->m_lineText = m_objectCreator->createTextButton("", 20, 'W',0.f,0.f);

    // Find the correct insertion point based on score (descending order)
    auto insertIt = std::find_if(m_data.begin(), m_data.end(),
        [&score](const std::shared_ptr<DataCell>& entry) {
            return entry->m_score < score;
        });

    // Insert the new entry before the found position
    m_data.insert(insertIt, std::move(newEntry));

    // Ensure leaderboard size does not exceed 10 entries
    if (m_data.size() > 10) {
        m_data.pop_back();
    }

    // Re-position all text in data
    int index = 0;
    for (auto& line : m_data) {
        line->m_lineText.setPosition(550.f, 250.f + (index * 50));
        index++;
    }
}