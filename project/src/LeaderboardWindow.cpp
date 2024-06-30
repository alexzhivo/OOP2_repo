#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
    : Window(window,objectCreator), m_currBackButton(false)
{
    m_title = objectCreator->createTextButton("LEADERBOARD", 70, 'W', 400.f, 100.f);
    m_backButton = objectCreator->createTextButton("<< BACK >>", 20, 'G', 600.f, 800.f);

    // initilize leaderboard
    for (int i = 0; i < 10; i++) {
        m_data.push_back(std::make_unique<DataCell>());
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

    int index = 1;
    for (const auto& cell : m_data) {
        std::string newStr = std::to_string(index) + ".\t\t" + cell->m_playerName + "\t\t" + std::to_string(cell->m_score);
        cell->m_lineText.setString(newStr);
        m_window.draw(cell->m_lineText);
        index++;
    }
}

void LeaderboardWindow::resetWindow()
{
    m_currBackButton = false;
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

    auto newEntry = std::make_unique<DataCell>();
    newEntry->m_playerName = name;
    newEntry->m_score = score;
    

    // Find the correct insertion point based on score (descending order)
    auto insertIt = std::find_if(m_data.begin(), m_data.end(),
        [&score](const std::unique_ptr<DataCell>& entry) {
            return entry->m_score < score;
        });

    // Insert the new entry before the found position
    m_data.insert(insertIt, std::move(newEntry));

    // Ensure leaderboard size does not exceed 10 entries
    if (m_data.size() > 10) {
        m_data.pop_back();
    }
}