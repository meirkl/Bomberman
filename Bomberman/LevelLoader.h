#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Utilities.h"
#include "Robot.h"
#include "Factory.h"
#include "Tile.h"

#include <memory>

////////////////////////////////////////////////////////////
/// \brief The game level loader
///
////////////////////////////////////////////////////////////
class LevelLoader {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	////////////////////////////////////////////////////////////
	LevelLoader();
	void loadLevel();
	std::shared_ptr<Robot> getRobot();
	std::vector<std::unique_ptr<Enemies>> getEnemies();
	std::vector<std::vector<std::shared_ptr<Tile>>> getBoard();
	static size_t m_stage;
	static size_t m_levels;
private:
	std::map<size_t, std::string> m_stageFileNames;
	std::shared_ptr<Robot> m_robot;
	std::vector<std::unique_ptr<Enemies>> m_enemies;
	std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
	Factory<BricksID, Brick> m_brickFactory;
	Factory<RobotID, Robot> m_robotFactory;
	Factory<EnemyID, Enemies> m_enemyFactory;
	Factory<DoorID, Door> m_doorFactory;
};