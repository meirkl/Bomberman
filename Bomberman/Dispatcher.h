#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Brick.h"
#include "Robot.h"
#include "Enemies.h"
#include "Bomb.h"

#include <map>
#include <functional>

////////////////////////////////////////////////////////////
/// \brief The game collision handler
///
////////////////////////////////////////////////////////////
template <class T, class S>
class Dispatcher {
public:
	////////////////////////////////////////////////////////////
	/// \brief Function with two type object parameter
	///
	////////////////////////////////////////////////////////////
	using ColisionFunction = std::function<void(T&, S&)>;

	////////////////////////////////////////////////////////////
	/// \brief Collision map
	///
	/// The key is a pair of the object name
	/// The value is a collision function
	///
	////////////////////////////////////////////////////////////
	using HitMap = std::map<std::pair<std::string, std::string>, ColisionFunction>;

	////////////////////////////////////////////////////////////
	/// \brief Collision map initializer
	///
	////////////////////////////////////////////////////////////
	static void initializeCollisionMap();

	////////////////////////////////////////////////////////////
	/// \brief Find collision function 
	///
	////////////////////////////////////////////////////////////
	static ColisionFunction lookup(const std::string& class1, const std::string& class2);

private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	static HitMap m_hitMap; ///< Collision map
};


////////////////////////////////////////////////////////////
/// Static object initialization 
///
////////////////////////////////////////////////////////////
template <class T, class S>
typename Dispatcher<T, S>::HitMap Dispatcher<T, S>::m_hitMap;


////////////////////////////////////////////////////////////
template <class T, class S>
void Dispatcher<T, S>::initializeCollisionMap()
{
	static auto initialized = false; // initialization lock

	if (!initialized) {
		// robot collide with enemy
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Barom).name())] = [](auto& robot, auto& barom) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Onil).name())] = [](auto& robot, auto& onil) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Minvo).name())] = [](auto& robot, auto& minvo) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Pass).name())] = [](auto& robot, auto& pass) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Pontan).name())] = [](auto& robot, auto& pontan) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Altair).name())] = [](auto& robot, auto& altair) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Master).name())] = [](auto& robot, auto& master) { static_cast<Robot&>(robot).collideWithEnemy(); };

		// enemy collide with robot
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(Robot).name())] = [](auto& barom, auto& robot) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(Robot).name())] = [](auto& onil, auto& robot) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(Robot).name())] = [](auto& minvo, auto& robot) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(Robot).name())] = [](auto& pass, auto& robot) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(Robot).name())] = [](auto& pontan, auto& robot) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(Robot).name())] = [](auto& altair, auto& robot) { static_cast<Robot&>(robot).collideWithEnemy(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(Robot).name())] = [](auto& master, auto& robot) { static_cast<Robot&>(robot).collideWithEnemy(); };

		// dynamic collide with brick
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(HardBrick).name())] = [](auto& robot, auto& brick) { static_cast<Robot&>(robot).collideWithHardBrick(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(SoftBrick).name())] = [](auto& robot, auto& brick) { static_cast<Robot&>(robot).collideWithSoftBrick(); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(HardBrick).name())] = [](auto& barom, auto& brick) { static_cast<DynamicObject&>(barom).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(SoftBrick).name())] = [](auto& barom, auto& brick) { static_cast<DynamicObject&>(barom).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(HardBrick).name())] = [](auto& onil, auto& brick) { static_cast<DynamicObject&>(onil).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(SoftBrick).name())] = [](auto& onil, auto& brick) { static_cast<DynamicObject&>(onil).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(HardBrick).name())] = [](auto& minvo, auto& brick) { static_cast<DynamicObject&>(minvo).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(SoftBrick).name())] = [](auto& minvo, auto& brick) { static_cast<DynamicObject&>(minvo).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(HardBrick).name())] = [](auto& pass, auto& brick) { static_cast<DynamicObject&>(pass).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(SoftBrick).name())] = [](auto& pass, auto& brick) { static_cast<DynamicObject&>(pass).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(HardBrick).name())] = [](auto& pontan, auto& brick) { static_cast<DynamicObject&>(pontan).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(SoftBrick).name())] = [](auto& pontan, auto& brick) { static_cast<DynamicObject&>(pontan).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(HardBrick).name())] = [](auto& altair, auto& brick) { static_cast<DynamicObject&>(altair).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(SoftBrick).name())] = [](auto& altair, auto& brick) { static_cast<DynamicObject&>(altair).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(HardBrick).name())] = [](auto& master, auto& brick) { static_cast<DynamicObject&>(master).collideWithBrick(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(SoftBrick).name())] = [](auto& master, auto& brick) { static_cast<DynamicObject&>(master).collideWithBrick(); };

		// dynamic collide with bomb
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Bomb).name())] = [](auto& robot, auto& bomb) { static_cast<DynamicObject&>(robot).cillideWithBomb(static_cast<Bomb&>(bomb)); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(Bomb).name())] = [](auto& barom, auto& bomb) { static_cast<DynamicObject&>(barom).cillideWithBomb(static_cast<Bomb&>(bomb)); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(Bomb).name())] = [](auto& onil, auto& bomb) { static_cast<DynamicObject&>(onil).cillideWithBomb(static_cast<Bomb&>(bomb)); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(Bomb).name())] = [](auto& minvo, auto& bomb) { static_cast<DynamicObject&>(minvo).cillideWithBomb(static_cast<Bomb&>(bomb)); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(Bomb).name())] = [](auto& pass, auto& bomb) { static_cast<DynamicObject&>(pass).cillideWithBomb(static_cast<Bomb&>(bomb)); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(Bomb).name())] = [](auto& pontan, auto& bomb) { static_cast<DynamicObject&>(pontan).cillideWithBomb(static_cast<Bomb&>(bomb)); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(Bomb).name())] = [](auto& altair, auto& bomb) { static_cast<DynamicObject&>(altair).cillideWithBomb(static_cast<Bomb&>(bomb)); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(Bomb).name())] = [](auto& master, auto& bomb) { static_cast<DynamicObject&>(master).cillideWithBomb(static_cast<Bomb&>(bomb)); };

		// dynamic collide with explosion
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(CenterExplosion).name())] = [](auto& robot, auto& explosion) { static_cast<DynamicObject&>(robot).explode(); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(CenterExplosion).name())] = [](auto& barom, auto& explosion) { static_cast<DynamicObject&>(barom).explode(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(CenterExplosion).name())] = [](auto& onil, auto& explosion) { static_cast<DynamicObject&>(onil).explode(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(CenterExplosion).name())] = [](auto& minvo, auto& explosion) { static_cast<DynamicObject&>(minvo).explode(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(CenterExplosion).name())] = [](auto& pass, auto& explosion) { static_cast<DynamicObject&>(pass).explode(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(CenterExplosion).name())] = [](auto& pontan, auto& explosion) { static_cast<DynamicObject&>(pontan).explode(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(CenterExplosion).name())] = [](auto& altair, auto& explosion) { static_cast<DynamicObject&>(altair).explode(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(CenterExplosion).name())] = [](auto& master, auto& explosion) { static_cast<DynamicObject&>(master).explode(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(UpExplosion).name())] = [](auto& robot, auto& explosion) { static_cast<DynamicObject&>(robot).explode(); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(UpExplosion).name())] = [](auto& barom, auto& explosion) { static_cast<DynamicObject&>(barom).explode(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(UpExplosion).name())] = [](auto& onil, auto& explosion) { static_cast<DynamicObject&>(onil).explode(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(UpExplosion).name())] = [](auto& minvo, auto& explosion) { static_cast<DynamicObject&>(minvo).explode(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(UpExplosion).name())] = [](auto& pass, auto& explosion) { static_cast<DynamicObject&>(pass).explode(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(UpExplosion).name())] = [](auto& pontan, auto& explosion) { static_cast<DynamicObject&>(pontan).explode(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(UpExplosion).name())] = [](auto& altair, auto& explosion) { static_cast<DynamicObject&>(altair).explode(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(UpExplosion).name())] = [](auto& master, auto& explosion) { static_cast<DynamicObject&>(master).explode(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(DownExplosion).name())] = [](auto& robot, auto& explosion) { static_cast<DynamicObject&>(robot).explode(); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(DownExplosion).name())] = [](auto& barom, auto& explosion) { static_cast<DynamicObject&>(barom).explode(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(DownExplosion).name())] = [](auto& onil, auto& explosion) { static_cast<DynamicObject&>(onil).explode(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(DownExplosion).name())] = [](auto& minvo, auto& explosion) { static_cast<DynamicObject&>(minvo).explode(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(DownExplosion).name())] = [](auto& pass, auto& explosion) { static_cast<DynamicObject&>(pass).explode(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(DownExplosion).name())] = [](auto& pontan, auto& explosion) { static_cast<DynamicObject&>(pontan).explode(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(DownExplosion).name())] = [](auto& altair, auto& explosion) { static_cast<DynamicObject&>(altair).explode(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(DownExplosion).name())] = [](auto& master, auto& explosion) { static_cast<DynamicObject&>(master).explode(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(RightExplosion).name())] = [](auto& robot, auto& explosion) { static_cast<DynamicObject&>(robot).explode(); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(RightExplosion).name())] = [](auto& barom, auto& explosion) { static_cast<DynamicObject&>(barom).explode(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(RightExplosion).name())] = [](auto& onil, auto& explosion) { static_cast<DynamicObject&>(onil).explode(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(RightExplosion).name())] = [](auto& minvo, auto& explosion) { static_cast<DynamicObject&>(minvo).explode(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(RightExplosion).name())] = [](auto& pass, auto& explosion) { static_cast<DynamicObject&>(pass).explode(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(RightExplosion).name())] = [](auto& pontan, auto& explosion) { static_cast<DynamicObject&>(pontan).explode(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(RightExplosion).name())] = [](auto& altair, auto& explosion) { static_cast<DynamicObject&>(altair).explode(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(RightExplosion).name())] = [](auto& master, auto& explosion) { static_cast<DynamicObject&>(master).explode(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(LeftExplosion).name())] = [](auto& robot, auto& explosion) { static_cast<DynamicObject&>(robot).explode(); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(LeftExplosion).name())] = [](auto& barom, auto& explosion) { static_cast<DynamicObject&>(barom).explode(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(LeftExplosion).name())] = [](auto& onil, auto& explosion) { static_cast<DynamicObject&>(onil).explode(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(LeftExplosion).name())] = [](auto& minvo, auto& explosion) { static_cast<DynamicObject&>(minvo).explode(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(LeftExplosion).name())] = [](auto& pass, auto& explosion) { static_cast<DynamicObject&>(pass).explode(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(LeftExplosion).name())] = [](auto& pontan, auto& explosion) { static_cast<DynamicObject&>(pontan).explode(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(LeftExplosion).name())] = [](auto& altair, auto& explosion) { static_cast<DynamicObject&>(altair).explode(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(LeftExplosion).name())] = [](auto& master, auto& explosion) { static_cast<DynamicObject&>(master).explode(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(HorizontalExplosion).name())] = [](auto& robot, auto& explosion) { static_cast<DynamicObject&>(robot).explode(); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(HorizontalExplosion).name())] = [](auto& barom, auto& explosion) { static_cast<DynamicObject&>(barom).explode(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(HorizontalExplosion).name())] = [](auto& onil, auto& explosion) { static_cast<DynamicObject&>(onil).explode(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(HorizontalExplosion).name())] = [](auto& minvo, auto& explosion) { static_cast<DynamicObject&>(minvo).explode(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(HorizontalExplosion).name())] = [](auto& pass, auto& explosion) { static_cast<DynamicObject&>(pass).explode(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(HorizontalExplosion).name())] = [](auto& pontan, auto& explosion) { static_cast<DynamicObject&>(pontan).explode(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(HorizontalExplosion).name())] = [](auto& altair, auto& explosion) { static_cast<DynamicObject&>(altair).explode(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(HorizontalExplosion).name())] = [](auto& master, auto& explosion) { static_cast<DynamicObject&>(master).explode(); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(VerticalExplosion).name())] = [](auto& robot, auto& explosion) { static_cast<DynamicObject&>(robot).explode(); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(VerticalExplosion).name())] = [](auto& barom, auto& explosion) { static_cast<DynamicObject&>(barom).explode(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(VerticalExplosion).name())] = [](auto& onil, auto& explosion) { static_cast<DynamicObject&>(onil).explode(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(VerticalExplosion).name())] = [](auto& minvo, auto& explosion) { static_cast<DynamicObject&>(minvo).explode(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(VerticalExplosion).name())] = [](auto& pass, auto& explosion) { static_cast<DynamicObject&>(pass).explode(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(VerticalExplosion).name())] = [](auto& pontan, auto& explosion) { static_cast<DynamicObject&>(pontan).explode(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(VerticalExplosion).name())] = [](auto& altair, auto& explosion) { static_cast<DynamicObject&>(altair).explode(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(VerticalExplosion).name())] = [](auto& master, auto& explosion) { static_cast<DynamicObject&>(master).explode(); };

		// dynamic collide with door
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Door).name())] = [](auto& robot, auto& door) { static_cast<DynamicObject&>(robot).collideWithDoor(); };
		m_hitMap[std::make_pair(typeid(Barom).name(), typeid(Door).name())] = [](auto& barom, auto& door) { static_cast<DynamicObject&>(barom).collideWithDoor(); };
		m_hitMap[std::make_pair(typeid(Onil).name(), typeid(Door).name())] = [](auto& onil, auto& door) { static_cast<DynamicObject&>(onil).collideWithDoor(); };
		m_hitMap[std::make_pair(typeid(Minvo).name(), typeid(Door).name())] = [](auto& minvo, auto& door) { static_cast<DynamicObject&>(minvo).collideWithDoor(); };
		m_hitMap[std::make_pair(typeid(Pass).name(), typeid(Door).name())] = [](auto& pass, auto& door) { static_cast<DynamicObject&>(pass).collideWithDoor(); };
		m_hitMap[std::make_pair(typeid(Pontan).name(), typeid(Door).name())] = [](auto& pontan, auto& door) { static_cast<DynamicObject&>(pontan).collideWithDoor(); };
		m_hitMap[std::make_pair(typeid(Altair).name(), typeid(Door).name())] = [](auto& altair, auto& door) { static_cast<DynamicObject&>(altair).collideWithDoor(); };
		m_hitMap[std::make_pair(typeid(Master).name(), typeid(Door).name())] = [](auto& master, auto& door) { static_cast<DynamicObject&>(master).collideWithDoor(); };

		// robot collide with power ups
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(BombIncrease).name())] = [](auto& robot, auto& power) { static_cast<Robot&>(robot).collideWithBombIncrease(static_cast<BombIncrease&>(power)); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Skate).name())] = [](auto& robot, auto& power) { static_cast<Robot&>(robot).collideWithSkate(static_cast<Skate&>(power)); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(BombPower).name())] = [](auto& robot, auto& power) { static_cast<Robot&>(robot).collideWithBombPower(static_cast<BombPower&>(power)); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Heart).name())] = [](auto& robot, auto& power) { static_cast<Robot&>(robot).collideWithHeart(static_cast<Heart&>(power)); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Clock).name())] = [](auto& robot, auto& power) { static_cast<Robot&>(robot).collideWithClock(static_cast<Clock&>(power)); };
		m_hitMap[std::make_pair(typeid(Robot).name(), typeid(Potion).name())] = [](auto& robot, auto& power) { static_cast<Robot&>(robot).collideWithPotion(static_cast<Potion&>(power)); };

		initialized = true;
	}
}


////////////////////////////////////////////////////////////
template<class T, class S>
typename Dispatcher<T, S>::ColisionFunction Dispatcher<T, S>::lookup(const std::string& class1, const std::string& class2)
{
	initializeCollisionMap();
	auto mapEntry = m_hitMap.find(make_pair(class1, class2));
	if (mapEntry == m_hitMap.end())
		return nullptr;
	return mapEntry->second;
}
