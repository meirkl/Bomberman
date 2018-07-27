////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "LevelLoader.h"

#include <fstream>

////////////////////////////////////////////////////////////
size_t LevelLoader::m_stage{ 1 };
size_t LevelLoader::m_levels;


////////////////////////////////////////////////////////////
LevelLoader::LevelLoader() try {
	std::ifstream ifstr;
	ifstr.open("Text/files.txt");
	if (!ifstr.is_open())
		throw std::runtime_error("Unable to open: Text/files.txt");
	std::string line;
	std::getline(ifstr, line);
	m_levels = std::stoi(line);
	for (size_t i = 1; i <= m_levels; ++i) {
		std::getline(ifstr, line);
		m_stageFileNames[i] = line;
	}
	ifstr.close();
} catch (...) {
	throw;
}


////////////////////////////////////////////////////////////
void LevelLoader::loadLevel()
{
	std::ifstream ifstream;
	ifstream.open(m_stageFileNames[m_stage]);
	if (!ifstream.is_open())
		throw std::runtime_error("Unable to open: " + m_stageFileNames[m_stage]);
	std::string line;
	auto x = 0.f, y = 0.f;

	std::vector<std::shared_ptr<Tile>> tiles;
	while (getline(ifstream, line)) {
		for (const auto& character : line) {
			switch (character) {
				case '#':
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE),
						m_brickFactory.makeObject(CONST_BRICK, { x,y })));
					break;
				case '*':
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE),
						m_brickFactory.makeObject(TEMP_BRICK, { x,y })));
					break;
				case 'R':
					m_robot = m_robotFactory.makeObject(ROBOT, { x,y });
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE)));
					break;
				case 'B':
					m_enemies.push_back(m_enemyFactory.makeObject(BAROM, { x,y }));
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE)));
					break;
				case 'O':
					m_enemies.push_back(m_enemyFactory.makeObject(ONIL, { x,y }));
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE)));
					break;
				case 'M':
					m_enemies.push_back(m_enemyFactory.makeObject(MINVO, { x,y }));
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE)));
					break;
				case 'P':
					m_enemies.push_back(m_enemyFactory.makeObject(PASS, { x,y }));
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE)));
					break;
				case 'T':
					m_enemies.push_back(m_enemyFactory.makeObject(PONTAN, { x,y }));
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE)));
					break;
				case 'A':
					m_enemies.push_back(m_enemyFactory.makeObject(ALTAIR, { x,y }));
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE)));
					break;
				case '$':
					m_enemies.push_back(m_enemyFactory.makeObject(MASTER, { x,y }));
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE)));
					break;
				case '&':
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE),
						m_doorFactory.makeObject(DOOR, { x,y })));
					break;
				default:
					tiles.push_back(std::make_unique<Tile>(sf::FloatRect(x, y, 24.f*SCALE, 24.f*SCALE)));
					break;

			}
			x += 24.f * SCALE;
		}
		m_tiles.push_back(std::move(tiles));
		x = 0.f;
		y += 24.f * SCALE;
	}
}


////////////////////////////////////////////////////////////
std::shared_ptr<Robot> LevelLoader::getRobot()
{
	return std::move(m_robot);
}


////////////////////////////////////////////////////////////
std::vector<std::vector<std::shared_ptr<Tile>>> LevelLoader::getBoard()
{
	return std::move(m_tiles);
}


////////////////////////////////////////////////////////////
std::vector<std::unique_ptr<Enemies>> LevelLoader::getEnemies()
{
	return std::move(m_enemies);
}

