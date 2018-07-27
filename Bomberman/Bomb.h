#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ResourceManager.h"
#include "StaticObject.h"
#include "DynamicObject.h"

////////////////////////////////////////////////////////////
/// \brief The game bomb
///
////////////////////////////////////////////////////////////
class Bomb : public StaticObject {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// Sets the brick texture size and position
	///
	////////////////////////////////////////////////////////////
	explicit Bomb(const sf::Vector2f& position);

	////////////////////////////////////////////////////////////
	/// \brief Plays the object animation 
	///
	/// \param direction - the key of the direction
	///
	////////////////////////////////////////////////////////////
	void playAnimation(const int direction) override;
	void exlpode();
	bool exploded() const;
	bool isExpired() const override;
	sf::Time getElapsedTime() const;
private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::Clock m_explosionClock; ///<
	bool m_explode; ///<
};
