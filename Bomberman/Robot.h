#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "DynamicObject.h"
#include "PowerUps.h"

#include <SFML/System/Vector2.hpp>

////////////////////////////////////////////////////////////
/// \brief The game main character
///
////////////////////////////////////////////////////////////
class Robot : public DynamicObject {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// Sets the position
	///
	////////////////////////////////////////////////////////////
	explicit Robot(const sf::Vector2f& position);
	////////////////////////////////////////////////////////////
	/// \brief Plays the object animation 
	///
	/// \param direction - the key of the direction
	///
	////////////////////////////////////////////////////////////
	void playAnimation(const int direction) override;

	void tryToMove(const sf::Vector2f& offset) override;
	void collideWithBrick() override;
	void collideWithSoftBrick();
	void collideWithHardBrick();
	void collideWithDoor() override;
	void cillideWithBomb(const Bomb& bomb) override;
	void collideWithEnemy();
	void resetTile() const;
	void collideWithBombPower(BombPower& power);
	void collideWithSkate(Skate& power);
	void collideWithBombIncrease(BombIncrease& power);
	void collideWithHeart(Heart& power) const;
	void collideWithClock(Clock& power) const;
	void collideWithPotion(Potion& power);
	void dropBomb();
	void updateNumOfBombs(const int value);
	int getNumOfBombs() const;
	void explode() override;
	bool isDead() override;
	bool levelCompleted() const;
	size_t getBombRadius() const;
private:
	bool m_canMove;
	Direction m_direction;
	bool m_hit;
	size_t m_numOfBombs;
	size_t m_bombStack;
	size_t m_bombRadius;
	bool m_levelCompleted;
	bool m_potion;
};
