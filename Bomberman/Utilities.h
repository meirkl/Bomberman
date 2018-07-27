#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <array>
#include <random>

enum BricksID {
	CONST_BRICK
	, TEMP_BRICK
};

enum RobotID { ROBOT };

enum BombID { BOMB };

enum DoorID { DOOR };

enum EnemyID {
	BAROM
	, ONIL
	, MINVO
	, PASS
	, PONTAN
	, ALTAIR
	, MASTER
};

enum PowerUpsID {
	SKATE
	, HEART
	, FIRE
	, CLOCK
	, BOMBUP
	, POTION
};


enum ExplosionID {
	CENTER_EXPLOSION
	, UP_EXPLOSION
	, DOWN_EXPLOSION
	, RIGHT_EXPLOSION
	, LEFT_EXPLOSION
	, VERTICAL_EXPLOSION
	, HORIZONTAL_EXPLOSION
};

enum Direction {
	INIT
	, UP
	, DOWN
	, RIGHT
	, LEFT
	, STAND
};

constexpr char* SPRITE_SHEET = "sprite_sheet";

////////////////////////////////////////////////////////////
/// \brief game button numbers
///
////////////////////////////////////////////////////////////
enum ButtonNumbers {
	START
	, HELP
	, HIGHSCORE
	, EXIT
	, MENU
};

////////////////////////////////////////////////////////////
/// \brief generates a random number in given range
///
/// \param min The smallest number
/// \param max The biggest number
/// \param exclusions The numbers that we don't want
///
/// \return a random number
///
/// \rd Will be used to obtain a seed for the random number engine
/// \gen Standard mersenne_twister_engine seeded with rd()
///
////////////////////////////////////////////////////////////
inline int random(int min = INT32_MIN, int max = INT32_MAX
	, const std::vector<int>&& exclusions = {})
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	int val;
	do {
		val = dis(gen);
	} while (std::find(exclusions.cbegin(), exclusions.cend(), val) != exclusions.cend());

	return val;
}