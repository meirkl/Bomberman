////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Brick.h"
#include "Utilities.h"
#include "ResourceManager.h"

#include <Thor/Animations/FrameAnimation.hpp>

////////////////////////////////////////////////////////////
Brick::Brick(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position)
	: StaticObject(texture, rectangle, position)
{
	thor::FrameAnimation stand;
	addAnimationFrame(stand, rectangle, 1);
	m_animator.addAnimation("stand", stand, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
void Brick::playAnimation(const int direction)
{
	m_animator.playAnimation("stand", true);
}


////////////////////////////////////////////////////////////
HardBrick::HardBrick(const sf::Vector2f& position)
	: Brick(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 24,378,24,24 }, position)
{
}


////////////////////////////////////////////////////////////
bool HardBrick::isExpired() const 
{
	return false;
}


////////////////////////////////////////////////////////////
SoftBrick::SoftBrick(const sf::Vector2f& position)
	: Brick(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 24,354,24,24 }, position)
{
}


////////////////////////////////////////////////////////////
bool SoftBrick::isExpired() const 
{
	return false;
}

