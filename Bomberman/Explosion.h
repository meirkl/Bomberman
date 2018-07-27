#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "StaticObject.h"

////////////////////////////////////////////////////////////
/// \brief The game explosions 
///
////////////////////////////////////////////////////////////
class Explosion : public StaticObject {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// Sets the explosion texture size and position
	///
	////////////////////////////////////////////////////////////
	Explosion(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~Explosion() = default;

	////////////////////////////////////////////////////////////
	/// \brief Plays the object animation 
	///
	/// \param direction - the key of the direction
	///
	////////////////////////////////////////////////////////////
	void playAnimation(const int direction) override;
	bool isExpired() const override;

protected:

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::Clock m_explosionClock;
};

class CenterExplosion : public Explosion {
public:
	explicit CenterExplosion(const sf::Vector2f& position);
};
class UpExplosion : public Explosion {
public:
	explicit UpExplosion(const sf::Vector2f& position);
};

class DownExplosion : public Explosion {
public:
	explicit DownExplosion(const sf::Vector2f& position);
};

class RightExplosion : public Explosion {
public:
	explicit RightExplosion(const sf::Vector2f& position);
};

class LeftExplosion : public Explosion {
public:
	explicit LeftExplosion(const sf::Vector2f& position);
};

class VerticalExplosion : public Explosion {
public:
	explicit VerticalExplosion(const sf::Vector2f& position);
};

class HorizontalExplosion : public Explosion {
public:
	explicit HorizontalExplosion(const sf::Vector2f& position);
};
