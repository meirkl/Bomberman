#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "StaticObject.h"
#include "Utilities.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

enum Status {
	NOT_VISTED
	, IN_PROGRES
	, VISTED
};

////////////////////////////////////////////////////////////
/// \brief The game tiles suitable for BFS 
///
////////////////////////////////////////////////////////////
struct Tile {
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// Sets the tile size and initialize the static pointer
	///
	////////////////////////////////////////////////////////////
	explicit Tile(const sf::FloatRect& rect, std::unique_ptr<StaticObject>&& object = nullptr);
	void addAdjacent(const std::pair<Direction, std::shared_ptr<Tile>>& adjacent);
	sf::Vector2f getPosition() const;
	void resetTile();
	bool isEmpty() const;
	void setObject(std::unique_ptr<StaticObject>&& object);
	StaticObject* getObject() const;
	sf::FloatRect getRect() const;
	void draw(sf::RenderWindow& window);
	static bool isPrime(unsigned val);
	sf::FloatRect m_rect;
	Status m_status;
	size_t m_discovery;
	std::unique_ptr<StaticObject> m_staticObject;
	std::map<Direction, std::weak_ptr<Tile>> m_adjacencyList;
	std::shared_ptr<Tile> m_parent;
};