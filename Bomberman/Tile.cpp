////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Tile.h"
#include "Brick.h"
#include "Explosion.h"
#include "Factory.h"

////////////////////////////////////////////////////////////
Tile::Tile(const sf::FloatRect& rect, std::unique_ptr<StaticObject>&& object)
	: m_rect{ rect }
	, m_status{ NOT_VISTED }
	, m_discovery{ INT_MAX }
	, m_staticObject(std::move(object))
{
}


////////////////////////////////////////////////////////////
void Tile::resetTile()
{
	m_status = NOT_VISTED;
	m_discovery = INT_MAX;
	m_parent = nullptr;
}


////////////////////////////////////////////////////////////
void Tile::addAdjacent(const std::pair<Direction, std::shared_ptr<Tile>>& adjacent)
{
	m_adjacencyList[adjacent.first] = adjacent.second;
}


////////////////////////////////////////////////////////////
sf::Vector2f Tile::getPosition() const
{
	return { m_rect.left, m_rect.top };
}


////////////////////////////////////////////////////////////
bool Tile::isEmpty() const
{
	return !m_staticObject;
}


////////////////////////////////////////////////////////////
void Tile::setObject(std::unique_ptr<StaticObject>&& object)
{
	if (!dynamic_cast<HardBrick*>(m_staticObject.get()))
		m_staticObject = std::move(object);
}


////////////////////////////////////////////////////////////
StaticObject* Tile::getObject() const
{
	return m_staticObject.get();
}


////////////////////////////////////////////////////////////
sf::FloatRect Tile::getRect() const
{
	return m_rect;
}


////////////////////////////////////////////////////////////
void Tile::draw(sf::RenderWindow& window)
{
	if (m_staticObject) {
		if (!m_staticObject->isExpired()) {
			m_staticObject->updateAnimation();
			window.draw(*m_staticObject);
		}
		else {
			auto explosion = dynamic_cast<CenterExplosion*>(m_staticObject.get());
			if (explosion && isPrime(random(1, 100))) {
				Factory<PowerUpsID, PowerUps> factory;
				m_staticObject = std::move(factory.makeObject(static_cast<PowerUpsID>(random(0, 5)), explosion->getPosition()));
			}
			else m_staticObject = nullptr;
		}
	}
}


////////////////////////////////////////////////////////////
bool Tile::isPrime(unsigned val)
{
	if (val < 2) return false;
	if (val == 2) return true;
	if (val % 2 == 0) return false;

	for (auto i = 3u; i <= val / 2; i += 2)
		if (val % i == 0) return false;

	return true;
}


