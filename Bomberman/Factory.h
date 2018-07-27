#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Utilities.h"
#include "Brick.h"
#include "Enemies.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Door.h"

#include <memory>
#include <functional>
#include <map>

////////////////////////////////////////////////////////////
/// \brief The game factory 
///
////////////////////////////////////////////////////////////
template <typename ID, class T>
class Factory {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	////////////////////////////////////////////////////////////
	Factory();

	std::unique_ptr<T> makeObject(const ID& id, const sf::Vector2f& position);
private:

	void registerit(const ID& id, std::function<std::unique_ptr<T>(const sf::Vector2f&)> func);

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	std::map<ID, std::function<std::unique_ptr<T>(const sf::Vector2f&)>> m_map;
};

inline Factory<BricksID, Brick>::Factory()
{
	registerit(CONST_BRICK, [](const auto& position) -> std::unique_ptr<Brick> { return std::make_unique<HardBrick>(position); });
	registerit(TEMP_BRICK, [](const auto& position) -> std::unique_ptr<Brick> { return std::make_unique<SoftBrick>(position); });
}

inline Factory<RobotID, Robot>::Factory()
{
	registerit(ROBOT, [](const auto& position) -> std::unique_ptr<Robot> { return std::make_unique<Robot>(position); });
}

inline Factory<BombID, Bomb>::Factory()
{
	registerit(BOMB, [](const auto& position) -> std::unique_ptr<Bomb> { return std::make_unique<Bomb>(position); });
}

inline Factory<EnemyID, Enemies>::Factory()
{
	registerit(BAROM, [](const auto& position) -> std::unique_ptr<Enemies> { return std::make_unique<Barom>(position); });
	registerit(MINVO, [](const auto& position) -> std::unique_ptr<Enemies> { return std::make_unique<Minvo>(position); });
	registerit(ONIL, [](const auto& position) -> std::unique_ptr<Enemies> { return std::make_unique<Onil>(position); });
	registerit(PASS, [](const auto& position) -> std::unique_ptr<Enemies> { return std::make_unique<Pass>(position); });
	registerit(PONTAN, [](const auto& position) -> std::unique_ptr<Enemies> { return std::make_unique<Pontan>(position); });
	registerit(ALTAIR, [](const auto& position) -> std::unique_ptr<Enemies> { return std::make_unique<Altair>(position); });
	registerit(MASTER, [](const auto& position) -> std::unique_ptr<Enemies> { return std::make_unique<Master>(position); });

}


inline Factory<ExplosionID, Explosion>::Factory()
{
	registerit(CENTER_EXPLOSION, [](const auto& position) -> std::unique_ptr<Explosion> { return std::make_unique<CenterExplosion>(position); });
	registerit(UP_EXPLOSION, [](const auto& position) -> std::unique_ptr<Explosion> { return std::make_unique<UpExplosion>(position); });
	registerit(DOWN_EXPLOSION, [](const auto& position) -> std::unique_ptr<Explosion> { return std::make_unique<DownExplosion>(position); });
	registerit(RIGHT_EXPLOSION, [](const auto& position) -> std::unique_ptr<Explosion> { return std::make_unique<RightExplosion>(position); });
	registerit(LEFT_EXPLOSION, [](const auto& position) -> std::unique_ptr<Explosion> { return std::make_unique<LeftExplosion>(position); });
	registerit(VERTICAL_EXPLOSION, [](const auto& position) -> std::unique_ptr<Explosion> { return std::make_unique<VerticalExplosion>(position); });
	registerit(HORIZONTAL_EXPLOSION, [](const auto& position) -> std::unique_ptr<Explosion> { return std::make_unique<HorizontalExplosion>(position); });
}

inline Factory<DoorID, Door>::Factory()
{
	registerit(DOOR, [](const auto& position) -> std::unique_ptr<Door> { return std::make_unique<Door>(position); });
}

inline Factory<PowerUpsID, PowerUps>::Factory()
{
	registerit(SKATE, [](const auto& position) -> std::unique_ptr<PowerUps> { return std::make_unique<Skate>(position); });
	registerit(HEART, [](const auto& position) -> std::unique_ptr<PowerUps> { return std::make_unique<Heart>(position); });
	registerit(FIRE, [](const auto& position) -> std::unique_ptr<PowerUps> { return std::make_unique<BombPower>(position); });
	registerit(CLOCK, [](const auto& position) -> std::unique_ptr<PowerUps> { return std::make_unique<Clock>(position); });
	registerit(BOMBUP, [](const auto& position) -> std::unique_ptr<PowerUps> { return std::make_unique<BombIncrease>(position); });
	registerit(POTION, [](const auto& position) -> std::unique_ptr<PowerUps> { return std::make_unique<Potion>(position); });
}


template <typename ID, class T>
std::unique_ptr<T> Factory<ID, T>::makeObject(const ID& id, const sf::Vector2f& position)
{
	auto it = m_map.find(id);
	if (it == m_map.end())
		return nullptr;
	return it->second(position);
}

template <typename ID, class T>
void Factory<ID, T>::registerit(const ID& id, std::function<std::unique_ptr<T>(const sf::Vector2f&)> func)
{
	m_map.emplace(id, func);
}