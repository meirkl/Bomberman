#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Thor/Animations/Animator.hpp>
#include <SFML/System/Clock.hpp>
#include <Thor/Animations/FrameAnimation.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>

////////////////////////////////////////////////////////////
constexpr float SCALE{ 2.5f };

////////////////////////////////////////////////////////////
/// \brief Drawable representation of a texture, with its
///        own transformations, color, etc.
///
////////////////////////////////////////////////////////////
class GameObject : public sf::Drawable, public sf::Transformable {
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates an empty object with no source texture.
	///
	////////////////////////////////////////////////////////////
	GameObject();

	////////////////////////////////////////////////////////////
	/// \brief Construct the object from a source texture
	///
	/// \param texture Source texture
	///
	////////////////////////////////////////////////////////////
	explicit GameObject(const sf::Texture& texture);

	////////////////////////////////////////////////////////////
	/// \brief Construct the object from a sub-rectangle of a source texture
	///
	/// \param texture   Source texture
	/// \param rectangle Sub-rectangle of the texture to assign to the sprite
	/// \param position  The object position 
	///
	////////////////////////////////////////////////////////////
	GameObject(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& position);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~GameObject() = default;

	////////////////////////////////////////////////////////////
	/// \brief Change the source texture of the sprite
	///
	/// The \a texture argument refers to a texture that must
	/// exist as long as the sprite uses it. Indeed, the sprite
	/// doesn't store its own copy of the texture, but rather keeps
	/// a pointer to the one that you passed to this function.
	/// If the source texture is destroyed and the sprite tries to
	/// use it, the behavior is undefined.
	/// If \a resetRect is true, the TextureRect property of
	/// the sprite is automatically adjusted to the size of the new
	/// texture. If it is false, the texture rect is left unchanged.
	///
	/// \param texture   New texture
	/// \param resetRect Should the texture rect be reset to the size of the new texture?
	///
	////////////////////////////////////////////////////////////
	void setTexture(const sf::Texture& texture, bool resetRect = false);

	////////////////////////////////////////////////////////////
	/// \brief Set the sub-rectangle of the texture that the sprite will display
	///
	/// The texture rect is useful when you don't want to display
	/// the whole texture, but rather a part of it.
	/// By default, the texture rect covers the entire texture.
	///
	/// \param rectangle Rectangle defining the region of the texture to display
	///
	////////////////////////////////////////////////////////////
	void setTextureRect(const sf::IntRect& rectangle);

	////////////////////////////////////////////////////////////
	/// \brief Get the sub-rectangle of the texture displayed by the sprite
	///
	/// \return Texture rectangle of the sprite
	///
	////////////////////////////////////////////////////////////
	const sf::IntRect& getTextureRect() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the local bounding rectangle of the entity
	///
	/// The returned rectangle is in local coordinates, which means
	/// that it ignores the transformations (translation, rotation,
	/// scale, ...) that are applied to the entity.
	/// In other words, this function returns the bounds of the
	/// entity in the entity's coordinate system.
	///
	/// \return Local bounding rectangle of the entity
	///
	////////////////////////////////////////////////////////////
	virtual sf::FloatRect getLocalBounds() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the global bounding rectangle of the entity
	///
	/// The returned rectangle is in global coordinates, which means
	/// that it takes into account the transformations (translation,
	/// rotation, scale, ...) that are applied to the entity.
	/// In other words, this function returns the bounds of the
	/// sprite in the global 2D world's coordinate system.
	///
	/// \return Global bounding rectangle of the entity
	///
	////////////////////////////////////////////////////////////
	virtual sf::FloatRect getGlobalBounds() const;

	////////////////////////////////////////////////////////////
	/// \brief Plays the object animation 
	///
	/// \param direction - the key of the direction
	///
	////////////////////////////////////////////////////////////
	virtual void playAnimation(const int direction) = 0;

	////////////////////////////////////////////////////////////
	/// \brief Stops the object animation 
	///
	////////////////////////////////////////////////////////////
	void stopAnimation();

	////////////////////////////////////////////////////////////
	/// \brief Update the object animation 
	///
	/// \param direction - the key of the direction
	///
	////////////////////////////////////////////////////////////
	void updateAnimation(const int direction = 0);

	////////////////////////////////////////////////////////////
	/// \brief Checks for collision between  objects
	///
	/// \param object - the key of the direction
	///
	////////////////////////////////////////////////////////////
	virtual bool collide(GameObject& object);

	////////////////////////////////////////////////////////////
	/// \brief Checks for collision between  objects
	///
	/// \param frame - thor FrameAnimation object
	/// \param subrect - the sub rectangle in the sprite sheet
	/// \param frames - the amount of frames
	/// \param relativeDuration - the time duration to play
	///
	////////////////////////////////////////////////////////////
	static void addAnimationFrame(thor::FrameAnimation& frame
		, const sf::IntRect& subrect, const int frames, const float relativeDuration = 1.f);

protected:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	thor::Animator<GameObject, std::string> m_animator; ///< Object animator
	sf::Clock m_frameClock; ///< Animation frame clock

private:
	////////////////////////////////////////////////////////////
	/// \brief Draw the sprite to a render target
	///
	/// \param target Render target to draw to
	/// \param states Current render states
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	////////////////////////////////////////////////////////////
	/// \brief Update the vertices' positions
	///
	////////////////////////////////////////////////////////////
	void updatePositions();

	////////////////////////////////////////////////////////////
	/// \brief Update the vertices' texture coordinates
	///
	////////////////////////////////////////////////////////////
	void updateTexCoords();

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::Vertex m_vertices[4];    	///< Vertices defining the sprite's geometry
	const sf::Texture* m_texture;	///< Texture of the sprite
	sf::IntRect m_textureRect;		///< Rectangle defining the area of the source texture to display
};

