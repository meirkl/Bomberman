#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ResourceManager.h"
#include "StaticObject.h"


////////////////////////////////////////////////////////////
/// \brief The game power ups
///
////////////////////////////////////////////////////////////
class PowerUps : public StaticObject {

public:

	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// Sets the power up texture size and position
	///
	////////////////////////////////////////////////////////////
	PowerUps(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position);

	////////////////////////////////////////////////////////////
	/// \brief  Destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~PowerUps() = default;

	////////////////////////////////////////////////////////////
	/// \brief Plays the object animation 
	///
	/// \param direction - the key of the direction
	///
	////////////////////////////////////////////////////////////
	void playAnimation(const int direction) override;

	virtual void givePower();
	bool isExpired() const override;
protected:
	bool m_power;
};

class BombPower : public PowerUps {
public:
	explicit BombPower(const sf::Vector2f& position);
};


class BombIncrease : public PowerUps {
public:
	explicit BombIncrease(const sf::Vector2f& position);
};


class Skate : public PowerUps {
public:
	explicit Skate(const sf::Vector2f& position);
};


class Heart : public PowerUps {
public:
	explicit Heart(const sf::Vector2f& position);

};

class Clock : public PowerUps {
public:
	explicit Clock(const sf::Vector2f& position);
};

class Potion : public PowerUps {
public:
	explicit Potion(const sf::Vector2f& position);
};