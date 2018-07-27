////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Robot.h"
#include "ResourceManager.h"
#include "Utilities.h"
#include "Bomb.h"
#include "Factory.h"
#include "GameBoard.h"

#include <Thor/Animations/FrameAnimation.hpp>

////////////////////////////////////////////////////////////
Robot::Robot(const sf::Vector2f& position)
	: DynamicObject(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 80,0,20,30 }, position)
	, m_canMove(true)
	, m_direction(STAND)
	, m_hit(false)
	, m_numOfBombs{ 1 }
	, m_bombStack{ 1 }
	, m_bombRadius{ 1 }
	, m_levelCompleted(false)
	, m_potion(false)
{
	thor::FrameAnimation stand;
	addAnimationFrame(stand, { 80,0,20,30 }, 1);
	m_animator.addAnimation("stand", stand, sf::seconds(0.8f));

	thor::FrameAnimation moveRight;
	addAnimationFrame(moveRight, { 180,0,20,30 }, 3);
	m_animator.addAnimation("moveRight", moveRight, sf::seconds(0.8f));

	thor::FrameAnimation moveLeft;
	addAnimationFrame(moveLeft, { 0,0,20,30 }, 3);
	m_animator.addAnimation("moveLeft", moveLeft, sf::seconds(0.8f));

	thor::FrameAnimation moveUp;
	addAnimationFrame(moveUp, { 120,0,20,30 }, 3);
	m_animator.addAnimation("moveUp", moveUp, sf::seconds(0.8f));

	thor::FrameAnimation moveDown;
	addAnimationFrame(moveDown, { 60,0,20,30 }, 3);
	m_animator.addAnimation("moveDown", moveDown, sf::seconds(0.8f));

	thor::FrameAnimation explode;
	addAnimationFrame(explode, { 0,30,20,30 }, 7);
	m_animator.addAnimation("explode", explode, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
void Robot::playAnimation(const int direction)
{
	switch (direction) {
		case UP: m_animator.playAnimation("moveUp", true); break;
		case DOWN: m_animator.playAnimation("moveDown", true); break;
		case RIGHT: m_animator.playAnimation("moveRight", true); break;
		case LEFT: m_animator.playAnimation("moveLeft", true); break;
		case STAND: m_animator.playAnimation("stand"); break;
		default:;
	}
}


////////////////////////////////////////////////////////////
void Robot::tryToMove(const sf::Vector2f& offset)
{
	if (m_canMove) {
		m_previousPosition = getPosition();
		move(offset);
	}
}


////////////////////////////////////////////////////////////
void Robot::collideWithBrick()
{
	setPosition(m_previousPosition);
}


////////////////////////////////////////////////////////////
void Robot::collideWithSoftBrick()
{
	if (!m_potion) setPosition(m_previousPosition);
}


////////////////////////////////////////////////////////////
void Robot::collideWithHardBrick()
{
	setPosition(m_previousPosition);
}


////////////////////////////////////////////////////////////
void Robot::collideWithDoor()
{
	m_levelCompleted = true;
}


////////////////////////////////////////////////////////////
void Robot::cillideWithBomb(const Bomb& bomb)
{
	//if (m_tile.lock()->m_rect.contains(bomb.getPosition()) && bomb.getElapsedTime().asSeconds() < 2.f) return;
	//if (bomb.getElapsedTime().asSeconds() > 1.f)
	//	collideWithBrick();
}


////////////////////////////////////////////////////////////
void Robot::collideWithEnemy()
{
	explode();
}


////////////////////////////////////////////////////////////
void Robot::resetTile() const
{
	m_tile.lock()->m_staticObject = nullptr;
}


////////////////////////////////////////////////////////////
void Robot::collideWithBombPower(BombPower& power)
{
	if (!power.isExpired()) {
		ResourceManager::getResource().playSound("coin");
		power.givePower();
		++m_bombRadius;
		GameBoard::m_powerUpsSprites[0].first = true;
		resetTile();
	}
}


////////////////////////////////////////////////////////////
void Robot::collideWithSkate(Skate& power)
{
	if (!power.isExpired()) {
		ResourceManager::getResource().playSound("coin");
		power.givePower();
		m_speed += 10.f;
		GameBoard::m_powerUpsSprites[2].first = true;
		resetTile();
	}
}


////////////////////////////////////////////////////////////
void Robot::collideWithBombIncrease(BombIncrease& power)
{
	if (!power.isExpired()) {
		ResourceManager::getResource().playSound("coin");
		power.givePower();
		++m_numOfBombs;
		++m_bombStack;
		GameBoard::m_powerUpsSprites[1].first = true;
		resetTile();
	}
}


////////////////////////////////////////////////////////////
void Robot::collideWithHeart(Heart& power) const
{
	if (!power.isExpired()) {
		ResourceManager::getResource().playSound("coin");
		power.givePower();
		if (GameBoard::m_robotLives < 3)
			++GameBoard::m_robotLives;
		resetTile();
	}
}


////////////////////////////////////////////////////////////
void Robot::collideWithClock(Clock& power) const
{
	if (!power.isExpired()) {
		ResourceManager::getResource().playSound("coin");
		power.givePower();
		if (GameBoard::m_timer.isRunning())
			GameBoard::m_timer.restart(sf::seconds(4 * 60.f));
		resetTile();
	}
}


void Robot::collideWithPotion(Potion& power)
{
	if (!power.isExpired()) {
		ResourceManager::getResource().playSound("coin");
		power.givePower();
		m_potion = true;
		GameBoard::m_powerUpsSprites[3].first = true;
		resetTile();
	}
}


////////////////////////////////////////////////////////////
void Robot::dropBomb()
{
	if (m_bombStack) {
		Factory<BombID, Bomb> factory;
		m_tile.lock()->setObject(factory.makeObject(BOMB, m_tile.lock()->getPosition()));
		m_bombStack -= 1;
	}
}


////////////////////////////////////////////////////////////
void Robot::updateNumOfBombs(const int value)
{
	m_bombStack += value;
}


////////////////////////////////////////////////////////////
int Robot::getNumOfBombs() const
{
	return m_numOfBombs;
}


////////////////////////////////////////////////////////////
void Robot::explode()
{
	if (m_animator.isPlayingAnimation() && m_animator.getPlayingAnimation() != "explode") {
		m_animator.playAnimation("explode", true);
		m_explodeClock.restart();
		m_hit = true;
		m_canMove = false;
	}
}

////////////////////////////////////////////////////////////
bool Robot::isDead()
{
	if (m_explodeClock.getElapsedTime().asSeconds() > 2.f && m_hit) {
		m_hit = false;
		return true;
	}
	return false;
}


////////////////////////////////////////////////////////////
bool Robot::levelCompleted() const
{
	return m_levelCompleted;
}


////////////////////////////////////////////////////////////
size_t Robot::getBombRadius() const
{
	return m_bombRadius;
}

