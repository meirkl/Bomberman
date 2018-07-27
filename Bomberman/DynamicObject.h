#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "GameObject.h"
#include "Tile.h"

////////////////////////////////////////////////////////////
class Bomb;

////////////////////////////////////////////////////////////
/// \brief The game movable objects 
///
////////////////////////////////////////////////////////////
class DynamicObject : public GameObject {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// Sets the object texture size and position
	///
	////////////////////////////////////////////////////////////
	DynamicObject(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~DynamicObject() = default;
	virtual float getSpped();
	virtual void setSpeed(float speed);
	virtual void tryToMove(const sf::Vector2f& offset) = 0;
	sf::Vector2f getPreviousPosition() const;
	sf::FloatRect getGlobalBounds() const override;
	virtual void collideWithBrick() = 0;
	virtual void collideWithDoor() = 0;
	virtual void cillideWithBomb(const Bomb& bomb) = 0;
	virtual void explode() = 0;
	void setTile(const std::weak_ptr<Tile>& tile);
	const std::weak_ptr<Tile>& getTile() const;
	virtual bool isDead() = 0;
protected:

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	float m_speed;
	sf::Vector2f m_previousPosition;
	std::weak_ptr<Tile> m_tile;
	sf::Clock m_explodeClock;
	bool m_explode;
};
