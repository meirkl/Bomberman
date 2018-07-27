#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "LevelLoader.h"
#include "Robot.h"
#include "Dispatcher.h"
#include "Tile.h"
#include "Explosion.h"
#include "Executable.h"

#include <SFML/Graphics.hpp>
#include <Thor/Time/Timer.hpp>
#include <memory>

////////////////////////////////////////////////////////////
/// \brief The game text information
///
////////////////////////////////////////////////////////////
struct GameInfo {

	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// Initializes the game members 
	////////////////////////////////////////////////////////////
	GameInfo();

	sf::Text m_stage; ///< Stage number
	sf::Text m_timer; ///< Current time
	sf::Text m_score; ///< Current Score
	sf::Text m_enemies; ///< Remaining enemies
	sf::Text m_powerUps; ///< Power up list 
	sf::Text m_level; ///< Current level
};

////////////////////////////////////////////////////////////
/// \brief The game engine
///
////////////////////////////////////////////////////////////
class GameBoard : public Executable {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// Initializes the game members 
	////////////////////////////////////////////////////////////
	explicit GameBoard(sf::RenderWindow& window);

	////////////////////////////////////////////////////////////
	/// \brief The game loop
	///
	/// Handles game events
	///
	////////////////////////////////////////////////////////////
	void run() override;


	////////////////////////////////////////////////////////////
	// Static member data
	////////////////////////////////////////////////////////////
	static thor::Timer m_timer;  ///< Stage timer
	static size_t m_robotLives;  ///< Robot remaining lives 
	static std::array<std::pair<bool, std::pair<sf::Sprite, sf::Sprite>>, 4> m_powerUpsSprites; ///< Power ups visual list

private:
	////////////////////////////////////////////////////////////
	/// \brief Displays stage number in the begging of the stage 
	///
	////////////////////////////////////////////////////////////
	void showStageEntry();

	////////////////////////////////////////////////////////////
	/// \brief Loads new level and initializes class members
	///
	////////////////////////////////////////////////////////////
	void loadLevel();

	////////////////////////////////////////////////////////////
	/// \brief Resets the level
	///
	////////////////////////////////////////////////////////////
	void resetLevel();

	////////////////////////////////////////////////////////////
	/// \brief Complete level
	///
	////////////////////////////////////////////////////////////
	void completeLevel();

	////////////////////////////////////////////////////////////
	/// \brief Process events 
	///
	////////////////////////////////////////////////////////////
	void processGameEvents();

	////////////////////////////////////////////////////////////
	/// \brief Handle arrow keys
	///
	////////////////////////////////////////////////////////////
	void handleMoveKeys(sf::Keyboard::Key key, const bool isPressed);

	////////////////////////////////////////////////////////////
	/// \brief Move the robot according to the key pressed 
	///
	////////////////////////////////////////////////////////////
	void moveRobot();

	////////////////////////////////////////////////////////////
	/// \brief Move the enemies randomly
	///
	////////////////////////////////////////////////////////////
	void moveEnemies();

	////////////////////////////////////////////////////////////
	/// \brief Checks for collisions
	///
	/// \param vector - collection of objects
	/// \param ptr - the object to check
	///
	////////////////////////////////////////////////////////////
	template <typename T, typename S>
	void checkCollisions(const std::vector<T>& vector, const S& ptr);

	////////////////////////////////////////////////////////////
	/// \brief Checks for collisions
	///
	/// \param vector - collection of objects
	/// \param ptr - the object to check
	///
	////////////////////////////////////////////////////////////
	template <typename T, typename S>
	void checkStaticCollisions(const std::vector<T>& vector, const S& ptr);

	////////////////////////////////////////////////////////////
	/// \brief Displays the game objects on the window
	///
	////////////////////////////////////////////////////////////
	void display();

	////////////////////////////////////////////////////////////
	/// \brief Displays the game board
	///
	////////////////////////////////////////////////////////////
	void drawStaticObjects();

	////////////////////////////////////////////////////////////
	/// \brief Sets the center of view
	///
	////////////////////////////////////////////////////////////
	void setCenter();

	////////////////////////////////////////////////////////////
	/// \brief Displays the information about the game state
	///
	////////////////////////////////////////////////////////////
	void displayHeader();

	////////////////////////////////////////////////////////////
	/// \brief Displays the information about the game state
	///
	////////////////////////////////////////////////////////////
	void displaySideBar();

	////////////////////////////////////////////////////////////
	/// \brief Displays the mini map
	///
	////////////////////////////////////////////////////////////
	void displayMiniMap();

	////////////////////////////////////////////////////////////
	/// \brief Displays the enemies
	///
	/// \param vector - collection of objects
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	void drawEnemies(const std::vector<T>& vector);

	////////////////////////////////////////////////////////////
	/// \brief Explodes the bombs
	///
	////////////////////////////////////////////////////////////
	void explodeBombs();

	////////////////////////////////////////////////////////////
	/// \brief Spreads the bomb explosion
	///
	/// Iterates over the tile adjacent
	///
	/// \param tile The tile to start from
	/// \param direction The explosion direction
	///
	////////////////////////////////////////////////////////////
	void spreadExplosion(std::shared_ptr<Tile>&& tile, const Direction direction);

	////////////////////////////////////////////////////////////
	/// \brief Remove expired objects
	///
	/// \param vector - collection of objects
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	void garbageCollector(std::vector<T>& vector);

	////////////////////////////////////////////////////////////
	/// \brief Sets the tile that is related to the object
	///
	/// \param ptr - movable object
	///
	////////////////////////////////////////////////////////////
	template <typename T>
	void setPlayersTile(const T& ptr);

	////////////////////////////////////////////////////////////
	/// \brief Sets the tile adjacents
	///
	/// \param i - tile row
	/// \param j - tile column
	///
	////////////////////////////////////////////////////////////
	void getAdjacents(const size_t i, const size_t j);

	////////////////////////////////////////////////////////////
	/// \brief Creates an exit door in an empty spot
	///
	////////////////////////////////////////////////////////////
	void createExit();

	////////////////////////////////////////////////////////////
	/// \brief End game
	///
	/// Opens high score window
	///
	////////////////////////////////////////////////////////////
	void endGame(const std::string& msg);

	////////////////////////////////////////////////////////////
	/// \brief Floods the board with enemies when the time is expired 
	///
	////////////////////////////////////////////////////////////
	void floodWithEnemies();

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::View m_view; ///< Game view
	std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles; ///< Game static object matrix
	std::vector<std::unique_ptr<Enemies>> m_enemies; ///< Game enemies
	std::shared_ptr<Robot> m_robot; ///< Main character
	std::array<sf::Sprite, 3> m_robotLivesSprite; ///< Lives visual list
	sf::Sprite m_timerIcon; ///< Timer icon
	sf::Vector2f m_centerOfView; ///< 
	sf::Vector2f m_leftExtremeCorner; ///<
	sf::Vector2f m_rightExtremeCorner; ///<
	sf::Clock m_clock; ///<
	sf::Time m_elapsedTime; ///<
	sf::Time m_deltaTime; ///<
	sf::Time m_timePerFrame; ///<
	Direction m_robotDirection; ///<
	LevelLoader m_loader; ///<
	Dispatcher<GameObject, GameObject> m_dispatcher; ///<
	Factory<ExplosionID, Explosion> m_explosionFactory; ///<
	Factory<DoorID, Door> m_doorFactory; ///<
	Factory<EnemyID, Enemies> m_enemyFactory; ///<
	GameInfo m_info; ///<
	size_t m_score; ///<
	bool m_pause; ///<
	bool m_door; ///<
	bool m_flood; ///<
	bool m_arrowKeyPressed; ///<
	bool m_updateAnimation; ///<
};


////////////////////////////////////////////////////////////
template <typename T, typename S>
void GameBoard::checkCollisions(const std::vector<T>& vector, const S& ptr)
{
	for (auto& object : vector) {
		if (ptr->collide(*object)) {
			auto colideFunc = m_dispatcher.lookup(typeid(*ptr).name(), typeid(*object).name());
			if (colideFunc)
				colideFunc(*ptr, *object);
			return;
		}
	}
}


////////////////////////////////////////////////////////////
template <typename T, typename S>
void GameBoard::checkStaticCollisions(const std::vector<T>& vector, const S& ptr)
{
	for (const auto& row : vector) {
		for (const auto& tile : row) {
			auto object = tile->getObject();
			if (object && ptr->collide(*object)) {
				auto colideFunc = m_dispatcher.lookup(typeid(*ptr).name(), typeid(*object).name());
				if (colideFunc)
					colideFunc(*ptr, *object);
				return;
			}
		}
	}
}


////////////////////////////////////////////////////////////
template<typename T>
void GameBoard::drawEnemies(const std::vector<T>& vector)
{
	for (auto& element : vector) {
		element->updateAnimation();
		m_window.draw(*element);
	}
}


////////////////////////////////////////////////////////////
template <typename T>
void GameBoard::garbageCollector(std::vector<T>& vector)
{
	vector.erase(std::remove_if(vector.begin(), vector.end(),
		[&](const auto& object)
	{
		if (object->isDead()) {
			m_score += object->getScore();
			return true;
		}
		return false;
	}), vector.end());
}


////////////////////////////////////////////////////////////
template <typename T>
void GameBoard::setPlayersTile(const T& ptr)
{
	auto x = static_cast<float>(ptr->getTextureRect().width);
	auto y = static_cast<float>(ptr->getTextureRect().height);
	for (const auto& row : m_tiles) {
		auto tile = std::find_if(row.cbegin(), row.cend(),
			[&](const auto& rect)
		{
			return rect->getRect().contains(ptr->getPosition() + sf::Vector2f(x, y));
		});
		if (tile != row.cend()) {
			ptr->setTile(*tile);
			break;
		}
	}
}