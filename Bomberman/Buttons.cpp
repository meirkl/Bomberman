////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Buttons.h"
#include "ResourceManager.h"
#include "Menu.h"
#include "GameBoard.h"
#include "Score.h"
#include "Executable.h"


////////////////////////////////////////////////////////////
Buttons::Buttons(const sf::IntRect& rect)
	: m_sprite(ResourceManager::getResource().getTexture("buttons"), rect)
	, m_set(false)
{
	auto width = static_cast<float>(m_mode.getDesktopMode().width);
	auto height = static_cast<float>(m_mode.getDesktopMode().height);
	m_sprite.setScale(width / 1920, height / 1000);
	m_size = { width, height };
	m_center = m_size / 2.f;
}


////////////////////////////////////////////////////////////
bool Buttons::contains(const sf::Vector2f& pos) const
{
	return m_sprite.getGlobalBounds().contains(pos);
}


////////////////////////////////////////////////////////////
bool Buttons::isMouseOverButton(const sf::Vector2f& pos)
{
	if (contains(pos)) {
		m_set = true;
		m_sprite.setTextureRect({
			m_sprite.getTextureRect().left
			, m_sprite.getTextureRect().top + 420
			, m_sprite.getTextureRect().width
			,  m_sprite.getTextureRect().height });
		return true;
	}
	return false;
}


////////////////////////////////////////////////////////////
const sf::Sprite& Buttons::getSprite() const
{
	return m_sprite;
}


////////////////////////////////////////////////////////////
void Buttons::setSprite(const sf::IntRect& rect)
{
	m_sprite.setTextureRect(rect);
}


////////////////////////////////////////////////////////////
void Buttons::setPosition(const sf::Vector2f& pos)
{
	m_sprite.setPosition(pos);
}


////////////////////////////////////////////////////////////
void Buttons::playSound()
{
	ResourceManager::getResource().playSound("click");
}


////////////////////////////////////////////////////////////
void Buttons::update()
{
	if (m_set) {
		m_sprite.setTextureRect({
			m_sprite.getTextureRect().left
			,m_sprite.getTextureRect().top - 420
			,m_sprite.getTextureRect().width
			, m_sprite.getTextureRect().height });
		m_set = false;
	}
}


////////////////////////////////////////////////////////////
StartButton::StartButton()
	: Buttons({ 0,0,350,84 })
{
	m_sprite.setPosition(m_center.x + m_size.x / 6, m_size.y / 3);
}


////////////////////////////////////////////////////////////
void StartButton::execute(sf::RenderWindow& window)
{
	playSound();
	m_sprite.setTextureRect({ 0,0,350,84 });
	GameBoard board(window);
	board.run();
}


////////////////////////////////////////////////////////////
HighScoreButton::HighScoreButton()
	: Buttons({ 0,168,350,84 })
{
	m_sprite.setPosition(m_center.x + m_size.x / 6, m_size.y / 3 + 100);
}


////////////////////////////////////////////////////////////
void HighScoreButton::execute(sf::RenderWindow& window)
{
	playSound();
	HighScore score(window);
	score.run();
}


////////////////////////////////////////////////////////////
HelpButton::HelpButton()
	: Buttons({ 0,84,350,84 })
{
	m_sprite.setPosition(m_center.x + m_size.x / 6, m_size.y / 3 + 200);
}


////////////////////////////////////////////////////////////
void HelpButton::execute(sf::RenderWindow& window)
{
	playSound();
	Instructions information(window);
	information.run();

}


////////////////////////////////////////////////////////////
ExitButton::ExitButton()
	: Buttons({ 0,252,350,84 })
{
	m_sprite.setPosition(m_center.x + m_size.x / 6, m_size.y / 3 + 300);
}

////////////////////////////////////////////////////////////
void ExitButton::execute(sf::RenderWindow& window)
{
	playSound();
	sf::sleep(sf::seconds(.1f));
	window.close();
}


////////////////////////////////////////////////////////////
MenuButton::MenuButton()
	: Buttons({ 0,336,350,84 })
{
}


////////////////////////////////////////////////////////////
void MenuButton::execute(sf::RenderWindow&)
{
	playSound();
	Menu::getInstance().activate();
}