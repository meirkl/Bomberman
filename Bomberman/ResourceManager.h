#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>

////////////////////////////////////////////////////////////
/// \brief Resource manger
///
////////////////////////////////////////////////////////////
class ResourceManager {

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Loads the game files
	///
	////////////////////////////////////////////////////////////
	ResourceManager();

	////////////////////////////////////////////////////////////
	/// \brief Disabled copy constructor
	///
	////////////////////////////////////////////////////////////
	ResourceManager(const ResourceManager&) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Disabled assignment operator
	///
	////////////////////////////////////////////////////////////
	ResourceManager& operator =(const ResourceManager&) = delete;

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::Music> m_sounds;
	sf::Font m_gameFont; ///< GameBoard font
	sf::Font m_scoreFont;
	sf::Font m_sideBarFont;
	sf::Music m_music;

public:

	////////////////////////////////////////////////////////////
	/// \brief Object instance
	///
	/// \return a ResourceManager object
	///
	/// This object can be created only once
	///
	////////////////////////////////////////////////////////////
	static ResourceManager& getResource();

	////////////////////////////////////////////////////////////
	/// \brief Get sprite sheet
	///
	/// \return The sprite sheet
	///
	////////////////////////////////////////////////////////////
	const sf::Texture& getTexture(const std::string& name) const;

	////////////////////////////////////////////////////////////
	/// \brief Get game font
	///
	/// \return The game font
	///
	////////////////////////////////////////////////////////////
	const sf::Font& getGameFont() const;

	const sf::Font& getScoreFont() const;

	const sf::Font& getSideBarFont() const;

	void playSound(const std::string& name);

	void stopSound(const std::string& name);

	void pauseSound(const std::string& name);
};