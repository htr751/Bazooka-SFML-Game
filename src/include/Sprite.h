#ifndef SPRITE
#define SPRITE

#include <string.h>

#include <SFML/Graphics.hpp>

#include "SceneUpdater.h"
#include "CharacterMovement.h"
#include "class_utils.hpp"

class Sprite
{
public:
	Sprite(const std::string& textureFilePath);
	DEFAULT_MOVE_OPERATIONS(Sprite);
	DISALLOW_COPY_OPERATIONS(Sprite);

	const sf::Sprite& getSprite() const noexcept;
	sf::Sprite& getSprite() noexcept;

	const sf::Texture& getUnderlyingTexture() const noexcept;
	~Sprite() = default;

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif