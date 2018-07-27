////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "DynamicObject.h"

////////////////////////////////////////////////////////////
DynamicObject::DynamicObject(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position)
	: GameObject(texture, rectangle, position)
	, m_speed{ 120.f }
	, m_previousPosition{ position }
	, m_explode(false)
{
	setScale(SCALE, SCALE);
}


////////////////////////////////////////////////////////////
float DynamicObject::getSpped()
{
	return m_speed;
}


////////////////////////////////////////////////////////////
void DynamicObject::setSpeed(float speed)
{
	m_speed = speed;
}


////////////////////////////////////////////////////////////
sf::Vector2f DynamicObject::getPreviousPosition() const
{
	return m_previousPosition;
}


////////////////////////////////////////////////////////////
sf::FloatRect DynamicObject::getGlobalBounds() const
{
	return getTransform().transformRect({
		getLocalBounds().left + 3
		, getLocalBounds().top + 10
		, getLocalBounds().width - 5
		, getLocalBounds().height - 15 });
}


////////////////////////////////////////////////////////////
void DynamicObject::setTile(const std::weak_ptr<Tile>& tile)
{
	m_tile = tile;
}


////////////////////////////////////////////////////////////
const std::weak_ptr<Tile>& DynamicObject::getTile() const
{
	return m_tile;
}
