#include <utility>

#include "Sprite.h"

Sprite::Sprite(const std::string& textureFilePath) {
	const auto success = this->m_texture.loadFromFile(textureFilePath);
	this->m_sprite.setTexture(this->m_texture);
}

const sf::Sprite& Sprite::getSprite() const noexcept {
	return this->m_sprite;
}

sf::Sprite& Sprite::getSprite() noexcept {
	return this->m_sprite;
}

const sf::Texture& Sprite::getUnderlyingTexture() const noexcept {
	return this->m_texture;
}