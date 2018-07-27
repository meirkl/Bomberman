////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Enemies.h"

#include <Thor/Animations/FrameAnimation.hpp>

////////////////////////////////////////////////////////////
Enemies::Enemies(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position)
	: DynamicObject(texture, rectangle, position)
	, m_direction{ UP }
	, m_directionClock{}
	, m_score(0)
{
}


////////////////////////////////////////////////////////////
void Enemies::playAnimation(const int direction)
{
	switch (direction) {
		case UP: m_animator.playAnimation("moveRight", true); break;
		case DOWN: m_animator.playAnimation("moveLeft", true); break;
		case RIGHT: m_animator.playAnimation("moveRight", true); break;
		case LEFT: m_animator.playAnimation("moveLeft", true); break;
		default:;
	}
}


////////////////////////////////////////////////////////////
void Enemies::tryToMove(const sf::Vector2f& offset)
{
	if (!m_explode) {
		m_previousPosition = getPosition();
		if (m_directionClock.getElapsedTime().asSeconds() > 4.f) {
			m_direction = static_cast<Direction>(random(1, 4));
			playAnimation(m_direction);
			m_directionClock.restart();
		}

		switch (m_direction) {
			case UP:
				move({ 0.f,-offset.y * m_speed });
				break;
			case DOWN:
				move({ 0.f,offset.y * m_speed });
				break;
			case RIGHT:
				move({ offset.x * m_speed ,0.f });
				break;
			case LEFT:
				move({ -offset.x * m_speed,0.f });
				break;
			default:;
		}
	}
}


////////////////////////////////////////////////////////////
void Enemies::collideWithBrick()
{
	setPosition(m_previousPosition);
	m_direction = static_cast<Direction>(random(1, 4, { m_direction }));
	playAnimation(m_direction);
}


////////////////////////////////////////////////////////////
void Enemies::collideWithDoor()
{
	collideWithBrick();
}


////////////////////////////////////////////////////////////
void Enemies::cillideWithBomb(const Bomb& bomb)
{
	collideWithBrick();
}


////////////////////////////////////////////////////////////
bool Enemies::isDead()
{
	return m_explodeClock.getElapsedTime().asSeconds() > 2.f && m_explode;
}


////////////////////////////////////////////////////////////
size_t Enemies::getScore() const
{
	return m_score;
}


////////////////////////////////////////////////////////////
void Enemies::explode()
{
	m_animator.playAnimation("explode", true);
	m_explodeClock.restart();
	m_explode = true;
}


////////////////////////////////////////////////////////////
Barom::Barom(const sf::Vector2f& position)
	: Enemies(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,90,20,30 }, { position.x, position.y - 10 })
{
	m_score = 100;
	thor::FrameAnimation moveLeft;
	addAnimationFrame(moveLeft, { 80,90,20,30 }, 4);
	m_animator.addAnimation("moveLeft", moveLeft, sf::seconds(0.8f));

	thor::FrameAnimation moveRight;
	addAnimationFrame(moveRight, { 0,90,20,30 }, 4);
	m_animator.addAnimation("moveRight", moveRight, sf::seconds(0.8f));

	thor::FrameAnimation explode;
	addAnimationFrame(explode, { 160,90,20,30 }, 5);
	m_animator.addAnimation("explode", explode, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
Onil::Onil(const sf::Vector2f& position)
	: Enemies(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,120,20,30 }, { position.x, position.y - 10 })
{
	m_score = 200;
	thor::FrameAnimation moveLeft;
	addAnimationFrame(moveLeft, { 80,120,20,30 }, 4);
	m_animator.addAnimation("moveLeft", moveLeft, sf::seconds(0.8f));

	thor::FrameAnimation moveRight;
	addAnimationFrame(moveRight, { 0,120,20,30 }, 4);
	m_animator.addAnimation("moveRight", moveRight, sf::seconds(0.8f));

	thor::FrameAnimation explode;
	addAnimationFrame(explode, { 160,120,20,30 }, 5);
	m_animator.addAnimation("explode", explode, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
Minvo::Minvo(const sf::Vector2f& position)
	: Enemies(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,150,20,30 }, { position.x, position.y - 10 })
{
	m_score = 800;
	thor::FrameAnimation moveLeft;
	addAnimationFrame(moveLeft, { 80,150,20,30 }, 4);
	m_animator.addAnimation("moveLeft", moveLeft, sf::seconds(0.8f));

	thor::FrameAnimation moveRight;
	addAnimationFrame(moveRight, { 0,150,20,30 }, 4);
	m_animator.addAnimation("moveRight", moveRight, sf::seconds(0.8f));

	thor::FrameAnimation explode;
	addAnimationFrame(explode, { 160,150,20,30 }, 5);
	m_animator.addAnimation("explode", explode, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
Pass::Pass(const sf::Vector2f& position)
	: Enemies(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,180,20,30 }, { position.x, position.y - 10 })
{
	m_score = 4000;
	thor::FrameAnimation moveLeft;
	addAnimationFrame(moveLeft, { 80,180,20,30 }, 4);
	m_animator.addAnimation("moveLeft", moveLeft, sf::seconds(0.8f));

	thor::FrameAnimation moveRight;
	addAnimationFrame(moveRight, { 0,180,20,30 }, 4);
	m_animator.addAnimation("moveRight", moveRight, sf::seconds(0.8f));

	thor::FrameAnimation explode;
	addAnimationFrame(explode, { 160,180,20,30 }, 5);
	m_animator.addAnimation("explode", explode, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
Pontan::Pontan(const sf::Vector2f& position)
	: Enemies(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,210,20,30 }, { position.x, position.y - 10 })
{
	m_score = 8000;
	thor::FrameAnimation moveLeft;
	addAnimationFrame(moveLeft, { 0,210,20,30 }, 2);
	m_animator.addAnimation("moveLeft", moveLeft, sf::seconds(0.8f));

	thor::FrameAnimation moveRight;
	addAnimationFrame(moveRight, { 0,210,20,30 }, 2);
	m_animator.addAnimation("moveRight", moveRight, sf::seconds(0.8f));

	thor::FrameAnimation explode;
	addAnimationFrame(explode, { 40,210,20,30 }, 5);
	m_animator.addAnimation("explode", explode, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
Master::Master(const sf::Vector2f& position)
	: Enemies(ResourceManager::getResource().getTexture("master"), { 0,0,50,50 }, { position.x, position.y - 10 })
	, m_lives(3)
{
	m_score = 12000;
	thor::FrameAnimation moveLeft;
	addAnimationFrame(moveLeft, { 0,0,50,50 }, 15);
	m_animator.addAnimation("moveLeft", moveLeft, sf::seconds(3.f));

	thor::FrameAnimation moveRight;
	addAnimationFrame(moveRight, { 0,0,50,50 }, 15);
	m_animator.addAnimation("moveRight", moveRight, sf::seconds(3.f));

	thor::FrameAnimation explode;
	addAnimationFrame(explode, { 0,50,50,50 }, 7);
	m_animator.addAnimation("explode", explode, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
void Master::explode()
{
	if (m_explosion.getElapsedTime().asSeconds() > 3.f) {
		m_explosion.restart();
		m_animator.playAnimation("explode");
		--m_lives;
		if (!m_lives) {
			Enemies::explode();
		}
	}
}


////////////////////////////////////////////////////////////
Altair::Altair(const sf::Vector2f& position)
	: Enemies(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,240,20,30 }, { position.x, position.y - 10 })
{
	m_score = 10000;
	thor::FrameAnimation moveLeft;
	addAnimationFrame(moveLeft, { 80,240,20,30 }, 4);
	m_animator.addAnimation("moveLeft", moveLeft, sf::seconds(0.8f));

	thor::FrameAnimation moveRight;
	addAnimationFrame(moveRight, { 0,240,20,30 }, 4);
	m_animator.addAnimation("moveRight", moveRight, sf::seconds(0.8f));

	thor::FrameAnimation explode;
	addAnimationFrame(explode, { 160,240,20,30 }, 5);
	m_animator.addAnimation("explode", explode, sf::seconds(0.8f));
}


////////////////////////////////////////////////////////////
void Altair::tryToMove(const sf::Vector2f& offset)
{
	if (!m_explode) {
		m_previousPosition = getPosition();
		m_move.BFS(m_robot.lock()->getTile().lock(), getTile().lock());

		if (m_move.pathExist()) {
			m_pathExist = true;
			m_direction = m_move.getDirection();
			m_directions.push_back(m_direction);
			if (m_collision) {
				if (m_directions.size() > 15) {
					m_direction = m_directions.at(m_directions.size() - 15);
					m_directions.clear();
					std::vector<Direction> temp(15, m_direction);
					std::copy(temp.begin(), temp.end(), std::back_inserter(m_directions));
				}
				m_collision = false;
			}
			switch (m_direction) {
				case UP: move({ 0.f,-offset.y * m_speed }); break;
				case DOWN: move({ 0.f,offset.y * m_speed }); break;
				case RIGHT: move({ offset.x * m_speed ,0.f }); break;
				case LEFT: move({ -offset.x * m_speed,0.f }); break;
				default:;
			}
		}
		else {
			m_pathExist = false;
			Enemies::tryToMove(offset);
			m_directions.push_back(m_direction);
			if (m_directions.size() > 15) {
				m_directions.clear();
				std::vector<Direction> temp(15, m_direction);
				std::copy(temp.begin(), temp.end(), std::back_inserter(m_directions));
			}
		}
	}
}


////////////////////////////////////////////////////////////
void Altair::collideWithBrick()
{
	if (m_pathExist) {
		m_collision = true;
		setPosition(m_previousPosition);
		playAnimation(m_direction);
	}
	else { Enemies::collideWithBrick(); }
}



