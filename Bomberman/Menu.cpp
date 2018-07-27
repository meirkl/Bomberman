////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Menu.h"
#include "ResourceManager.h"
#include "GameBoard.h"

#include <SFML/Window/Event.hpp>

////////////////////////////////////////////////////////////
Menu::Menu()
	: m_window(sf::VideoMode::getDesktopMode(), "Bomberman", sf::Style::Fullscreen)
	, m_background(ResourceManager::getResource().getTexture("menu_background"))
{
	m_window.setVerticalSyncEnabled(true);
	m_buttons[START] = std::make_unique<StartButton>();
	m_buttons[HELP] = std::make_unique<HelpButton>();
	m_buttons[HIGHSCORE] = std::make_unique<HighScoreButton>();
	m_buttons[EXIT] = std::make_unique<ExitButton>();
	m_buttons[MENU] = std::make_unique<MenuButton>();
}

////////////////////////////////////////////////////////////
Menu& Menu::getInstance()
{
	static Menu menu;
	return  menu;
}


////////////////////////////////////////////////////////////
void Menu::activate()
{
	ResourceManager::getResource().stopSound("music");
	m_window.create(sf::VideoMode::getDesktopMode(), "Bomberman", sf::Style::Fullscreen);
	m_background.setScale(
		m_window.getView().getSize().x / m_background.getLocalBounds().width,
		m_window.getView().getSize().y / m_background.getLocalBounds().height);
	m_window.setMouseCursorVisible(true);
	while (m_window.isOpen()) {
		show();
		sf::Event event;
		while (m_window.waitEvent(event)) {
			auto pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
			switch (event.type) {
				case sf::Event::Closed: m_window.close(); break;
				case sf::Event::MouseMoved: handleMouseButtonPressed(pos); break;
				case sf::Event::MouseButtonPressed:	handleMouseButtonPressed(pos); break;
				case sf::Event::MouseButtonReleased: handleMouseButtonReleased(pos); break;
				case sf::Event::KeyReleased:
				default:;
			}
			show();
			updateButtons();
		}
	}
}


////////////////////////////////////////////////////////////
void Menu::show()
{
	m_window.clear();
	m_window.draw(m_background);
	for (const auto& button : m_buttons) {
		if (button.first != MENU)
			m_window.draw(button.second->getSprite());
	}
	m_window.display();
}


////////////////////////////////////////////////////////////
void Menu::performAction(const size_t i)
{
	m_buttons[i]->execute(m_window);
}


////////////////////////////////////////////////////////////
void Menu::handleMouseButtonPressed(const sf::Vector2f& pos)
{
	for (const auto& button : m_buttons)
		if (button.second->isMouseOverButton(pos))
			break;
}


////////////////////////////////////////////////////////////
void Menu::handleMouseButtonReleased(const sf::Vector2f& pos)
{
	for (const auto& button : m_buttons) {
		if (button.second->contains(pos)) {
			performAction(button.first);
			break;
		}
	}
}


////////////////////////////////////////////////////////////
void Menu::updateButtons()
{
	for (const auto& button : m_buttons)
		button.second->update();
}
