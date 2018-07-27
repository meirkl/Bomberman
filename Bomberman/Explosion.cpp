////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Explosion.h"
#include "ResourceManager.h"
#include "Utilities.h"

#include <Thor/Animations/FrameAnimation.hpp>

////////////////////////////////////////////////////////////
Explosion::Explosion(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position)
	: StaticObject(texture, rectangle, position)
{
	setScale(3.f, 3.f);
	thor::FrameAnimation explode;
	addAnimationFrame(explode, rectangle, 4);
	m_animator.addAnimation("explode", explode, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
void Explosion::playAnimation(const int direction)
{
	m_animator.playAnimation("explode", true);
}


////////////////////////////////////////////////////////////
bool Explosion::isExpired() const
{
	return m_explosionClock.getElapsedTime().asSeconds() > 0.8f;
}


////////////////////////////////////////////////////////////
CenterExplosion::CenterExplosion(const sf::Vector2f& position)
	: Explosion(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,270,20,20 }, position)
{
	ResourceManager::getResource().playSound("explosion");
}


////////////////////////////////////////////////////////////
UpExplosion::UpExplosion(const sf::Vector2f& position)
	: Explosion(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,290,20,20 }, position)
{
}


////////////////////////////////////////////////////////////
DownExplosion::DownExplosion(const sf::Vector2f& position)
	: Explosion(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,310,20,20 }, position)
{
}


////////////////////////////////////////////////////////////
RightExplosion::RightExplosion(const sf::Vector2f& position)
	: Explosion(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 80,290,20,20 }, position)
{
}


////////////////////////////////////////////////////////////
LeftExplosion::LeftExplosion(const sf::Vector2f& position)
	: Explosion(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 80,270,20,20 }, position)
{
}


VerticalExplosion::VerticalExplosion(const sf::Vector2f& position)
	: Explosion(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 160,290,20,20 }, position)
{
}


////////////////////////////////////////////////////////////
HorizontalExplosion::HorizontalExplosion(const sf::Vector2f& position)
	: Explosion(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 160,270,20,20 }, position)
{
}

