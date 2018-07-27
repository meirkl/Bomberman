#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "DynamicObject.h"
#include "Utilities.h"
#include "SmartMove.h"
#include "Robot.h"
#include "SmartEnemy.h"

////////////////////////////////////////////////////////////
/// \brief The game enemies 
///
////////////////////////////////////////////////////////////
class Enemies : public DynamicObject {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// Sets the enemies texture size and position
	///
	////////////////////////////////////////////////////////////
	Enemies(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~Enemies() = default;

	////////////////////////////////////////////////////////////
	/// \brief Plays the object animation 
	///
	/// \param direction - the key of the direction
	///
	////////////////////////////////////////////////////////////
	void playAnimation(const int direction) override;

	void tryToMove(const sf::Vector2f& offset) override;
	void collideWithBrick() override;
	void collideWithDoor() override;
	void cillideWithBomb(const Bomb& bomb) override;
	bool isDead() override;
	size_t getScore() const;
	void explode() override;
protected:

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	Direction m_direction;
	sf::Clock m_directionClock;
	size_t m_score;
};

class Barom : public Enemies {

public:
	explicit Barom(const sf::Vector2f& position);
};

class Onil : public Enemies { 
public:
	explicit Onil(const sf::Vector2f& position);
};

class Minvo : public Enemies { 
public:
	explicit Minvo(const sf::Vector2f& position);
};

class Pass : public Enemies {
public:
	explicit Pass(const sf::Vector2f& position);
};

class Pontan : public Enemies {
public:
	explicit Pontan(const sf::Vector2f& position);
};

class Master : public Enemies {
public:
	explicit Master(const sf::Vector2f& position);
	void explode() override;
private:

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::Clock m_explosion;
	size_t m_lives;
};

class Altair : public Enemies, public SmartEnemy {
public:
	explicit Altair(const sf::Vector2f& position);
	void tryToMove(const sf::Vector2f& offset) override;
	void collideWithBrick() override;
};