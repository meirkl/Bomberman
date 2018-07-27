////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Bomb.h"
#include "Utilities.h"

#include <Thor/Animations/FrameAnimation.hpp>

////////////////////////////////////////////////////////////
Bomb::Bomb(const sf::Vector2f& position)
	: StaticObject(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,64,20,20 }, position)
	, m_explosionClock{}
	, m_explode{}
{
	thor::FrameAnimation wait;
	addAnimationFrame(wait, { 0,64,20,20 }, 3);
	m_animator.addAnimation("wait", wait, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
void Bomb::playAnimation(const int direction)
{
	m_animator.playAnimation("wait", true);
}


////////////////////////////////////////////////////////////
void Bomb::exlpode()
{
	m_explode = true;
}


////////////////////////////////////////////////////////////
bool Bomb::exploded() const
{
	return m_explosionClock.getElapsedTime().asSeconds() > 3.f;

}


////////////////////////////////////////////////////////////
bool Bomb::isExpired() const
{
	return false;
}


////////////////////////////////////////////////////////////
sf::Time Bomb::getElapsedTime() const
{
	return m_explosionClock.getElapsedTime();
}

