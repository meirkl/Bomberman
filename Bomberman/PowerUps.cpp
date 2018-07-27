////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "PowerUps.h"
#include "Utilities.h"

////////////////////////////////////////////////////////////
PowerUps::PowerUps(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position)
	: StaticObject(texture, rectangle, position)
	, m_power(true)
{
	thor::FrameAnimation stand;
	addAnimationFrame(stand, rectangle, 1);
	m_animator.addAnimation("stand", stand, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
void PowerUps::playAnimation(const int direction)
{
	m_animator.playAnimation("stand", true);
}


////////////////////////////////////////////////////////////
void PowerUps::givePower()
{
	m_power = false;
}


////////////////////////////////////////////////////////////
bool PowerUps::isExpired() const
{
	return !m_power;

}


////////////////////////////////////////////////////////////
BombPower::BombPower(const sf::Vector2f& position)
	: PowerUps(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,330,24,24 }, position)
{
}


////////////////////////////////////////////////////////////
BombIncrease::BombIncrease(const sf::Vector2f& position)
	: PowerUps(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 48,330,24,24 }, position)
{
}


////////////////////////////////////////////////////////////
Skate::Skate(const sf::Vector2f& position)
	: PowerUps(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 96,330,24,24 }, position)
{
}


////////////////////////////////////////////////////////////
Heart::Heart(const sf::Vector2f& position)
	: PowerUps(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 192,330,24,24 }, position)
{
}


////////////////////////////////////////////////////////////
Clock::Clock(const sf::Vector2f& position) // ice cream 
	: PowerUps(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 168,354,24,24 }, position)
{
}


////////////////////////////////////////////////////////////
Potion::Potion(const sf::Vector2f& position)
	: PowerUps(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 144,330,24,24 }, position)
{
}


