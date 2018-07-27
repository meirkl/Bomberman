////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ResourceManager.h"

////////////////////////////////////////////////////////////
ResourceManager::ResourceManager() try {
	if (!m_textures["sprite_sheet"].loadFromFile("Media/sprite_sheet.png")
		|| !m_textures["menu_background"].loadFromFile("Media/menu_backgruond.png")
		|| !m_textures["buttons"].loadFromFile("Media/buttons.png")
		|| !m_textures["help_background"].loadFromFile("Media/instructions_background.png")
		|| !m_textures["master"].loadFromFile("Media/master.png")
		|| !m_textures["instructions"].loadFromFile("Media/instructions_text.png"))
		throw std::exception();

	if (!m_sounds["click"].openFromFile("Music/click.ogg")
		|| !m_sounds["explosion"].openFromFile("Music/explosion.ogg")
		|| !m_sounds["music"].openFromFile("Music/music.ogg")
		|| !m_sounds["coin"].openFromFile("Music/coin.ogg"))
		throw std::exception();

	m_sounds["explosion"].setVolume(20.f);
	m_sounds["music"].setLoop(true);
	m_sounds["music"].setVolume(5.f);
	m_sounds["coin"].setVolume(30.f);


	if (!m_gameFont.loadFromFile("Fonts/hangthedj.ttf")
		|| !m_scoreFont.loadFromFile("Fonts/highscore.ttf")
		|| !m_sideBarFont.loadFromFile("Fonts/Rubik-Bold.ttf"))
		throw std::exception();
} catch (...) {
	throw;
}


////////////////////////////////////////////////////////////
ResourceManager& ResourceManager::getResource()
{
	static ResourceManager resource;
	return resource;
}


////////////////////////////////////////////////////////////
const sf::Texture& ResourceManager::getTexture(const std::string& name) const
{
	auto texture = m_textures.find(name);
	if (texture == m_textures.cend())
		throw std::runtime_error("No such texture: " + name);
	return texture->second;
}


////////////////////////////////////////////////////////////
const sf::Font& ResourceManager::getGameFont() const
{
	return m_gameFont;
}


////////////////////////////////////////////////////////////
const sf::Font& ResourceManager::getScoreFont() const
{
	return m_scoreFont;
}


////////////////////////////////////////////////////////////
const sf::Font& ResourceManager::getSideBarFont() const
{
	return m_sideBarFont;
}


////////////////////////////////////////////////////////////
void ResourceManager::playSound(const std::string& name)
{
	auto sound = m_sounds.find(name);
	if (sound != m_sounds.cend())
		if (sound->second.getStatus() == sf::Music::Status::Paused || sound->second.getStatus() == sf::Music::Status::Stopped)
			sound->second.play();
}


////////////////////////////////////////////////////////////
void ResourceManager::stopSound(const std::string& name)
{
	auto sound = m_sounds.find(name);
	if (sound != m_sounds.cend()) {
		if (sound->second.getStatus() == sf::Music::Status::Playing)
			sound->second.stop();
	}
}


////////////////////////////////////////////////////////////
void ResourceManager::pauseSound(const std::string& name)
{
	auto sound = m_sounds.find(name);
	if (sound != m_sounds.cend()) {
		if (sound->second.getStatus() == sf::Music::Status::Playing)
			sound->second.pause();
	}
}