////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "GameBoard.h"
#include "DynamicObject.h"
#include "Menu.h"
#include "Score.h"

////////////////////////////////////////////////////////////
thor::Timer GameBoard::m_timer;
size_t GameBoard::m_robotLives{ 3 };
std::array<std::pair<bool, std::pair<sf::Sprite, sf::Sprite>>, 4> GameBoard::m_powerUpsSprites;


////////////////////////////////////////////////////////////
GameInfo::GameInfo()
	: m_stage("", ResourceManager::getResource().getGameFont(), 80u)
	, m_timer("", ResourceManager::getResource().getGameFont(), 80u)
	, m_score("", ResourceManager::getResource().getGameFont(), 80u)
	, m_enemies("", ResourceManager::getResource().getSideBarFont(), 40u)
	, m_powerUps("", ResourceManager::getResource().getSideBarFont(), 40u)
	, m_level("", ResourceManager::getResource().getGameFont(), 100u)
{
	m_stage.setFillColor(sf::Color(0, 51, 102));
	m_stage.setOutlineThickness(2.f);
	m_stage.setOutlineColor(sf::Color::Black);
	m_timer.setFillColor(sf::Color(0, 51, 102));
	m_timer.setOutlineThickness(2.f);
	m_timer.setOutlineColor(sf::Color::Black);
	m_score.setFillColor(sf::Color(0, 51, 102));
	m_score.setOutlineThickness(2.f);
	m_score.setOutlineColor(sf::Color::Black);
	m_enemies.setFillColor(sf::Color(0, 51, 102));
	m_powerUps.setFillColor(sf::Color(0, 51, 102));
}


////////////////////////////////////////////////////////////
GameBoard::GameBoard(sf::RenderWindow& window) try
	: Executable(window)
	, m_view{}
	, m_timerIcon(ResourceManager::getResource().getTexture(SPRITE_SHEET), { 0,446, 50,52 })
	, m_leftExtremeCorner{}
	, m_rightExtremeCorner{}
	, m_clock{}
	, m_elapsedTime(sf::Time::Zero)
	, m_deltaTime(sf::Time::Zero)
	, m_timePerFrame(sf::seconds(1.f / 30.f))
	, m_robotDirection{ STAND }
	, m_loader{}
	, m_score{ 0 }
	, m_pause{ false }
	, m_door{ false }
	, m_flood{ false }
	, m_arrowKeyPressed{ false }
	, m_updateAnimation{ true } {

	loadLevel();

	m_window.create(sf::VideoMode::getDesktopMode(), "Bomberman", sf::Style::Fullscreen);
	m_window.setMouseCursorVisible(false);

	m_centerOfView = sf::Vector2f(m_window.getSize() / 2u);

	for (auto& life : m_robotLivesSprite) {
		life.setTexture(ResourceManager::getResource().getTexture(SPRITE_SHEET));
		life.setTextureRect({ 50,446, 45,50 });
		life.setScale(1.5f, 1.5);
	}

	for (size_t i = 0; i < m_powerUpsSprites.size(); ++i) {
		m_powerUpsSprites[i].second.first.setTexture(ResourceManager::getResource().getTexture(SPRITE_SHEET));
		m_powerUpsSprites[i].second.first.setScale(3.f, 3.f);
		m_powerUpsSprites[i].second.first.setTextureRect({ static_cast<int>(i) * 48 + 24,330,24,24 });
		m_powerUpsSprites[i].second.second.setTexture(ResourceManager::getResource().getTexture(SPRITE_SHEET));
		m_powerUpsSprites[i].second.second.setScale(3.f, 3.f);
		m_powerUpsSprites[i].second.second.setTextureRect({ static_cast<int>(i) * 48,330,24,24 });
	}
	m_timerIcon.setScale(1.5f, 1.5f);

} catch (...) {
	throw;
}


////////////////////////////////////////////////////////////
void GameBoard::run()
{
	ResourceManager::getResource().playSound("music");
	while (m_window.isOpen()) {
		m_elapsedTime = m_clock.restart();
		m_deltaTime += m_elapsedTime;

		while (m_deltaTime > m_timePerFrame) {
			m_deltaTime -= m_timePerFrame;
			if (m_robot->isDead()) {
				ResourceManager::getResource().stopSound("music");
				if (m_robotLives == 1) {
					endGame("GAME - OVER");
					Menu::getInstance().activate();
					return;
				}
				resetLevel();
			}
			if (m_timer.isExpired() && !m_flood) {
				floodWithEnemies();
			}
			if (m_enemies.empty() && !m_door) {
				m_door = true;
				createExit();
			}
			if (m_robot->levelCompleted()) {
				if (LevelLoader::m_stage == LevelLoader::m_levels) {
					endGame("YOU WON!");
					Menu::getInstance().activate();
					return;
				}
				completeLevel();
			}
			processGameEvents();
			if (!m_pause) {
				moveRobot();
				setCenter();
				moveEnemies();
				explodeBombs();
				garbageCollector(m_enemies);
			}
			display();
		}
	}
}


////////////////////////////////////////////////////////////
void GameBoard::showStageEntry()
{
	m_window.clear();
	m_view.setViewport({ 0.f,0.f,1.f,1.f });
	m_window.setView(m_view);
	m_info.m_level.setString("STAGE " + std::to_string(LevelLoader::m_stage));
	m_info.m_level.setPosition(m_window.getView().getCenter() - sf::Vector2f(static_cast<float>(m_info.m_level.getString().getSize()) * 35, 100.f));
	m_window.draw(m_info.m_level);
	m_window.display();
	sf::sleep(sf::seconds(2.f));
}


////////////////////////////////////////////////////////////
void GameBoard::loadLevel()
{
	m_loader.loadLevel();
	showStageEntry();
	ResourceManager::getResource().playSound("music");
	for (auto& powerUpsSprite : m_powerUpsSprites) {
		powerUpsSprite.first = false;
	}
	m_robot = m_loader.getRobot();

	m_enemies = m_loader.getEnemies();

	for (auto& enemy : m_enemies) {
		auto smartEnemy = dynamic_cast<SmartEnemy*>(enemy.get());
		if (smartEnemy) {
			smartEnemy->setRobotPtr(m_robot);
		}
	}
	m_tiles = m_loader.getBoard();

	m_rightExtremeCorner = m_tiles.back().back()->getPosition() + sf::Vector2f(24.f*SCALE, 24.f*SCALE);

	for (size_t i = 0; i < m_tiles.size(); ++i)
		for (size_t j = 0; j < m_tiles.front().size(); ++j)
			getAdjacents(i, j);

	m_centerOfView = sf::Vector2f(m_window.getSize() / 2u);
	m_centerOfView.y += 13.f * SCALE;

	setCenter();
	m_timer.restart(sf::seconds(4.f * 60.f));
	m_flood = false;
}


////////////////////////////////////////////////////////////
void GameBoard::resetLevel()
{
	loadLevel();
	--m_robotLives;
	ResourceManager::getResource().playSound("music");
}


////////////////////////////////////////////////////////////
void GameBoard::completeLevel()
{
	ResourceManager::getResource().stopSound("music");
	++LevelLoader::m_stage;
	m_door = false;
	loadLevel();
}


////////////////////////////////////////////////////////////
void GameBoard::processGameEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed: m_window.close(); break;
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape) {
					m_robotLives = 3;
					Menu::getInstance().activate();
					return;
				}
				if (event.key.code == sf::Keyboard::X) m_robot->dropBomb();
				else if (event.key.code == sf::Keyboard::Up
					|| event.key.code == sf::Keyboard::Down
					|| event.key.code == sf::Keyboard::Right
					|| event.key.code == sf::Keyboard::Left)
					handleMoveKeys(event.key.code, true);
			}
			break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::X) break;
				if (event.key.code == sf::Keyboard::Space) {
					if (m_timer.isRunning()) {
						ResourceManager::getResource().pauseSound("music");
						for (auto& enemy : m_enemies) {
							enemy->stopAnimation();
						}
						m_timer.stop();
						m_pause = true;
						m_robotDirection = STAND;
					}
					else {
						ResourceManager::getResource().playSound("music");
						m_timer.start();
						m_pause = false;
					}
					break;
				}
				if (event.key.code == sf::Keyboard::Up
					|| event.key.code == sf::Keyboard::Down
					|| event.key.code == sf::Keyboard::Right
					|| event.key.code == sf::Keyboard::Left)
					handleMoveKeys(event.key.code, false);
				m_updateAnimation = true;
				m_robot->playAnimation(STAND);
				break;
			default:;
		}
	}
}


////////////////////////////////////////////////////////////
void GameBoard::handleMoveKeys(sf::Keyboard::Key key, const bool isPressed)
{
	if (!m_pause) {
		switch (key) {
			case sf::Keyboard::Up: m_robotDirection = UP; break;
			case sf::Keyboard::Down: m_robotDirection = DOWN; break;
			case sf::Keyboard::Right: m_robotDirection = RIGHT; break;
			case sf::Keyboard::Left: m_robotDirection = LEFT; break;
			default:;
		}
		m_arrowKeyPressed = isPressed;
	}
}


////////////////////////////////////////////////////////////
void GameBoard::moveRobot()
{
	sf::Vector2f movement;
	if (m_arrowKeyPressed) {
		switch (m_robotDirection) {
			case UP: movement.y -= m_robot->getSpped(); break;
			case DOWN: movement.y += m_robot->getSpped(); break;
			case RIGHT: movement.x += m_robot->getSpped(); break;
			case LEFT: movement.x -= m_robot->getSpped(); break;
			default:;
		}
		if (m_updateAnimation) {
			m_robot->playAnimation(m_robotDirection);
			m_updateAnimation = false;
		}
	}
	m_robot->tryToMove(movement * m_timePerFrame.asSeconds());

	checkStaticCollisions(m_tiles, m_robot);
	checkCollisions(m_enemies, m_robot);
	setPlayersTile(m_robot);
}


////////////////////////////////////////////////////////////
void GameBoard::moveEnemies()
{
	for (const auto& enemy : m_enemies) {
		setPlayersTile(enemy);
		enemy->tryToMove(sf::Vector2f(1.f, 1.f) * m_timePerFrame.asSeconds());
		auto smartEnemy = dynamic_cast<SmartEnemy*>(enemy.get());
		if (smartEnemy) {
			for (auto& tile : m_tiles)
				std::for_each(tile.cbegin(), tile.cend(), [](const auto& tile) { tile->resetTile(); });
		}
		checkStaticCollisions(m_tiles, enemy);
	}
}


////////////////////////////////////////////////////////////
void GameBoard::display()
{

	m_window.clear(sf::Color(204, 204, 153));

	sf::RectangleShape background(m_window.getView().getSize());
	background.setPosition(m_window.getView().getCenter() - background.getSize() / 2.f);
	background.setFillColor(sf::Color(51, 131, 52));
	m_window.draw(background);

	drawStaticObjects();
	displayMiniMap();
	displayHeader();
	displaySideBar();

	m_view.setViewport(sf::FloatRect(0.f, 0.087f, 0.75f, 1.f - 0.085f));
	m_window.setView(m_view);

	if (m_pause) {
		m_info.m_level.setString("PAUSE");
		m_info.m_level.setPosition(m_window.getView().getCenter() - sf::Vector2f(static_cast<float>(m_info.m_level.getString().getSize()) * 35, 100.f));
		m_window.draw(m_info.m_level);
	}

	m_window.display();
}

////////////////////////////////////////////////////////////
void GameBoard::drawStaticObjects()
{
	for (const auto& row : m_tiles)
		std::for_each(row.cbegin(), row.cend(),
			[&](const auto& tile)
	{
		tile->draw(m_window);
	});

	drawEnemies(m_enemies);
	m_robot->updateAnimation(STAND);
	m_window.draw(*m_robot);
}


////////////////////////////////////////////////////////////
void GameBoard::setCenter()
{
	auto windowSize = m_window.getView().getSize();

	if (m_robot->getPosition().x > windowSize.x / 2.f)
		m_centerOfView.x = m_rightExtremeCorner.x - m_robot->getPosition().x < windowSize.x / 2.f ?
		m_rightExtremeCorner.x - windowSize.x / 2.f : m_robot->getPosition().x;

	if (m_robot->getPosition().y > windowSize.y / 2.f)
		m_centerOfView.y = m_rightExtremeCorner.y - m_robot->getPosition().y < windowSize.y / 2.f ?
		m_rightExtremeCorner.y - windowSize.y / 2.f : m_robot->getPosition().y;

	m_view.setCenter(m_centerOfView);
	m_view.setSize(windowSize);
}


////////////////////////////////////////////////////////////
void GameBoard::displayHeader()
{
	sf::View header({ 0.f,0.f }, m_window.getView().getSize());
	header.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	m_window.setView(header);

	m_info.m_stage.setString("STAGE - " + std::to_string(LevelLoader::m_stage));
	m_info.m_stage.setPosition(m_window.getView().getCenter() - m_window.getView().getSize() / 2.f + sf::Vector2f(50.f, 0.f));
	auto s = static_cast<int>(m_timer.getRemainingTime().asSeconds()) % 60;
	auto seconds = s < 10 ? '0' + std::to_string(s) : std::to_string(s);
	auto minuts = std::to_string(static_cast<int>(m_timer.getRemainingTime().asSeconds()) / 60);
	m_timerIcon.setPosition(m_window.getView().getCenter() - sf::Vector2f(230.f, m_window.getView().getSize().y / 2.f - 20.f));
	m_info.m_timer.setString(minuts + ':' + seconds);
	m_info.m_timer.setPosition(m_timerIcon.getPosition() + sf::Vector2f(100.f, -20.f));
	m_info.m_score.setString("SCORE : " + std::to_string(m_score));
	m_info.m_score.setPosition(m_info.m_timer.getPosition() + sf::Vector2f(500.f, 0.f));

	m_window.draw(m_info.m_stage);
	m_window.draw(m_timerIcon);
	m_window.draw(m_info.m_timer);
	m_window.draw(m_info.m_score);
}


////////////////////////////////////////////////////////////
void GameBoard::displaySideBar()
{
	for (size_t i = 0; i < m_robotLives; ++i) {
		m_robotLivesSprite[i].setPosition(-30 + m_window.getView().getSize().x / 3 + i * 70, -200.f);
		m_window.draw(m_robotLivesSprite[i]);
	}
	m_info.m_enemies.setString("REMAINING ENEMIES - " + std::to_string(m_enemies.size()));
	m_info.m_enemies.setPosition(10 + m_window.getView().getSize().x / 4, -100.f);

	m_info.m_powerUps.setString("POWERUPS :");
	m_info.m_powerUps.setPosition(-20 + m_window.getView().getSize().x / 3, -40.f);

	m_window.draw(m_info.m_enemies);
	m_window.draw(m_info.m_powerUps);

	for (size_t i = 0; i < m_powerUpsSprites.size(); ++i) {
		m_powerUpsSprites[i].second.first.setPosition(60 + m_window.getView().getSize().x / 3, static_cast<float>(i) * 96 + 20);
		m_powerUpsSprites[i].second.second.setPosition(60 + m_window.getView().getSize().x / 3, static_cast<float>(i) * 96 + 20);
		m_window.draw(m_powerUpsSprites[i].first ? m_powerUpsSprites[i].second.second : m_powerUpsSprites[i].second.first);
	}
}


////////////////////////////////////////////////////////////
void GameBoard::displayMiniMap()
{
	sf::View miniMap(
		(m_rightExtremeCorner - m_leftExtremeCorner) / 2.f + m_leftExtremeCorner
		, (m_rightExtremeCorner - m_leftExtremeCorner));
	miniMap.setViewport(sf::FloatRect(0.75f, 0.087f, 0.25f, 0.25f));
	m_window.setView(miniMap);
	sf::RectangleShape background(m_window.getView().getSize());
	background.setPosition(m_window.getView().getCenter() - background.getSize() / 2.f);
	background.setFillColor(sf::Color::Black);
	m_window.draw(background);
	drawStaticObjects();
}


////////////////////////////////////////////////////////////
void GameBoard::explodeBombs()
{
	for (size_t i = 0; i < m_tiles.size(); ++i) {
		for (size_t j = 0; j < m_tiles.front().size(); ++j) {
			auto bomb = dynamic_cast<Bomb*>(m_tiles[i][j]->getObject());
			if (bomb && bomb->exploded()) {
				m_robot->updateNumOfBombs(m_robot->getNumOfBombs());
				auto psition = bomb->getPosition();
				m_tiles[i][j]->setObject(m_explosionFactory.makeObject(CENTER_EXPLOSION, psition));
				for (const auto& v : m_tiles[i][j]->m_adjacencyList) {
					spreadExplosion(v.second.lock(), v.first);
				}
				return;
			}
		}
	}
}


////////////////////////////////////////////////////////////
void GameBoard::spreadExplosion(std::shared_ptr<Tile>&& tile, const Direction direction)
{
	auto id = direction == UP || direction == DOWN ? VERTICAL_EXPLOSION : HORIZONTAL_EXPLOSION;
	for (size_t i = 0; i < m_robot->getBombRadius(); ++i) {
		if (i == m_robot->getBombRadius() - 1) {
			tile->setObject(m_explosionFactory.makeObject(static_cast<ExplosionID>(direction), tile->getPosition()));
			break;
		}
		auto it = tile->m_adjacencyList.find(direction);
		if (it != tile->m_adjacencyList.end()) {
			auto hardBlock = dynamic_cast<HardBrick*>(tile->getObject());
			if (hardBlock) break;
			tile->setObject(m_explosionFactory.makeObject(id, tile->getPosition()));
			tile = tile->m_adjacencyList[direction].lock();
		}
	}
}


////////////////////////////////////////////////////////////
void GameBoard::getAdjacents(const size_t i, const size_t j)
{
	if (j > 0)
		m_tiles[i][j]->addAdjacent({ LEFT,m_tiles[i][j - 1] });
	if (j < m_tiles.front().size() - 1)
		m_tiles[i][j]->addAdjacent({ RIGHT,m_tiles[i][j + 1] });
	if (i > 0)
		m_tiles[i][j]->addAdjacent({ UP,m_tiles[i - 1][j] });
	if (i < m_tiles.size() - 1)
		m_tiles[i][j]->addAdjacent({ DOWN,m_tiles[i + 1][j] });
}


////////////////////////////////////////////////////////////
void GameBoard::createExit()
{
	while (true) {
		auto y = random(0, m_tiles.size() - 1);
		auto x = random(0, m_tiles.front().size() - 1);
		if (m_tiles[y][x]->isEmpty()) {
			m_tiles[y][x]->setObject(m_doorFactory.makeObject(DOOR, m_tiles[y][x]->getPosition()));
			break;
		}
	}
}


////////////////////////////////////////////////////////////
void GameBoard::endGame(const std::string& msg)
{
	ResourceManager::getResource().stopSound("music");
	m_window.clear();
	m_view.setViewport({ 0.f,0.f,1.f,1.f });
	m_window.setView(m_view);
	m_info.m_level.setString(msg);
	m_robotLives = 3;
	m_info.m_level.setPosition(m_window.getView().getCenter() - sf::Vector2f(static_cast<float>(m_info.m_level.getString().getSize()) * 35, 0.f));
	m_window.draw(m_info.m_level);
	m_window.display();
	sf::sleep(sf::seconds(2.f));
	Score score(m_score);
	score.run();
}


////////////////////////////////////////////////////////////
void GameBoard::floodWithEnemies()
{
	m_flood = true;
	auto floodNumber = random(10, 20);
	while (floodNumber) {
		auto y = random(0, m_tiles.size() - 1);
		auto x = random(0, m_tiles.front().size() - 1);
		if (m_tiles[y][x]->isEmpty()) {
			m_enemies.push_back(m_enemyFactory.makeObject(PONTAN, m_tiles[y][x]->getPosition()));
			--floodNumber;
		}
	}
}

