////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Executable.h"
#include "ResourceManager.h"
#include "Menu.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <fstream>

////////////////////////////////////////////////////////////
Executable::Executable(sf::RenderWindow& window)
	: m_window(window)
	, m_background(ResourceManager::getResource().getTexture("help_background"))
{
}


////////////////////////////////////////////////////////////
void Executable::waitForUserClick()
{
	while (m_window.isOpen()) {
		sf::Event event;
		while (m_window.waitEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					m_window.close();
					break;
				case sf::Event::MouseButtonReleased:
					if (m_button.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)))) {
						m_button.execute(m_window);
						break;
					}
				default:;
			}
		}
	}
}


////////////////////////////////////////////////////////////
HighScore::HighScore(sf::RenderWindow& window)
	: Executable(window)
{
}


////////////////////////////////////////////////////////////
std::string HighScore::getFileInfo() const
{
	std::ifstream ifstr;
	ifstr.open("Text/score.txt");
	std::string fileInfo, line;
	while (std::getline(ifstr, line))
		fileInfo += line + '\n';
	ifstr.close();
	return fileInfo;
}


////////////////////////////////////////////////////////////
void HighScore::run()
{
	sf::Text text(getFileInfo(), ResourceManager::getResource().getScoreFont());
	text.setCharacterSize(25u);
	m_background.setScale(
		m_window.getView().getSize().x / m_background.getLocalBounds().width,
		m_window.getView().getSize().y / m_background.getLocalBounds().height);
	m_window.clear();
	m_window.draw(m_background);
	m_window.draw(m_button.getSprite());
	m_window.draw(text);
	m_window.display();

	waitForUserClick();
}


////////////////////////////////////////////////////////////
Instructions::Instructions(sf::RenderWindow& window)
	: Executable(window)
	, m_info(ResourceManager::getResource().getTexture("instructions"))
{
}


////////////////////////////////////////////////////////////
void Instructions::run()
{
	m_background.setScale(
		m_window.getView().getSize().x / m_background.getLocalBounds().width,
		m_window.getView().getSize().y / m_background.getLocalBounds().height);
	m_info.setScale(m_background.getScale());
	m_window.clear();
	m_window.draw(m_background);
	m_window.draw(m_info);
	m_window.draw(m_button.getSprite());
	m_window.display();

	waitForUserClick();
}
