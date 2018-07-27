////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Door.h"
#include "Utilities.h"

////////////////////////////////////////////////////////////
Door::Door(const sf::Vector2f& position) 
	: StaticObject(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,402,20,20 }, position)
{
	setScale(3.f, 3.f);
	thor::FrameAnimation show;
	addAnimationFrame(show, { 0,402,20,20 }, 4);
	m_animator.addAnimation("show", show, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
void Door::playAnimation(const int direction)
{
	m_animator.playAnimation("show", true);
}


////////////////////////////////////////////////////////////
bool Door::isExpired() const
{
	return false;
}
