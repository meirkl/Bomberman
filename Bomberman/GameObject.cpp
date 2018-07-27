////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "GameObject.h"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


////////////////////////////////////////////////////////////
GameObject::GameObject()
	: m_texture{ nullptr }
	, m_textureRect()
{
}


////////////////////////////////////////////////////////////
GameObject::GameObject(const sf::Texture& texture)
	: m_texture{ nullptr }
	, m_textureRect()
{
	setTexture(texture);
}


////////////////////////////////////////////////////////////
GameObject::GameObject(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position)
	: m_texture{ nullptr }
	, m_textureRect()
{
	setTexture(texture);
	setTextureRect(rectangle);
	setPosition(position);
}


////////////////////////////////////////////////////////////
void GameObject::setTexture(const sf::Texture& texture, bool resetRect)
{
	// Recompute the texture area if requested, or if there was no valid texture & rect before
	if (resetRect || (!m_texture && (m_textureRect == sf::IntRect())))
		setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));

	// Assign the new texture
	m_texture = &texture;
}


////////////////////////////////////////////////////////////
void GameObject::setTextureRect(const sf::IntRect& rectangle)
{
	if (rectangle != m_textureRect) {
		m_textureRect = rectangle;
		updatePositions();
		updateTexCoords();
	}
}


////////////////////////////////////////////////////////////
const sf::IntRect& GameObject::getTextureRect() const
{
	return m_textureRect;
}


////////////////////////////////////////////////////////////
sf::FloatRect GameObject::getLocalBounds() const
{
	auto width = static_cast<float>(std::abs(m_textureRect.width));
	auto height = static_cast<float>(std::abs(m_textureRect.height));

	return sf::FloatRect(0.f, 0.f, width, height);
}


////////////////////////////////////////////////////////////
sf::FloatRect GameObject::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////
void GameObject::stopAnimation()
{
	m_animator.stopAnimation();
}


////////////////////////////////////////////////////////////
void GameObject::updateAnimation(const int id)
{
	if (!m_animator.isPlayingAnimation())
		playAnimation(id);

	m_animator.update(m_frameClock.restart());
	m_animator.animate(*this);
}


////////////////////////////////////////////////////////////
bool GameObject::collide(GameObject& object)
{
	return getGlobalBounds().intersects(object.getGlobalBounds());
}


////////////////////////////////////////////////////////////
void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_texture) {
		states.transform *= getTransform();
		states.texture = m_texture;
		target.draw(m_vertices, 4, sf::TriangleStrip, states);
	}
}


////////////////////////////////////////////////////////////
void GameObject::updatePositions()
{
	auto bounds = getLocalBounds();

	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(0, bounds.height);
	m_vertices[2].position = sf::Vector2f(bounds.width, 0);
	m_vertices[3].position = sf::Vector2f(bounds.width, bounds.height);
}


////////////////////////////////////////////////////////////
void GameObject::updateTexCoords()
{
	auto left = static_cast<float>(m_textureRect.left);
	auto right = left + m_textureRect.width;
	auto top = static_cast<float>(m_textureRect.top);
	auto bottom = top + m_textureRect.height;

	m_vertices[0].texCoords = sf::Vector2f(left, top);
	m_vertices[1].texCoords = sf::Vector2f(left, bottom);
	m_vertices[2].texCoords = sf::Vector2f(right, top);
	m_vertices[3].texCoords = sf::Vector2f(right, bottom);
}


////////////////////////////////////////////////////////////
void GameObject::addAnimationFrame(thor::FrameAnimation& frame, const sf::IntRect& subrect, const int frames, const float relativeDuration)
{
	for (auto i = subrect.left; i < subrect.left + frames * subrect.width; i += subrect.width)
		frame.addFrame(relativeDuration, { i, subrect.top, subrect.width,subrect.height });
}

