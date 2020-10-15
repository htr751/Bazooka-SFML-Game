#include "Character.h"

Character::Character(Game& game, const std::string& textureFilePath, const sf::Vector2f& position) :
	m_game(game), m_sprite(textureFilePath) {
	
	this->m_sprite.getSprite().setPosition(position);
	this->m_sprite.getSprite().setOrigin(sf::Vector2f(this->m_sprite.getUnderlyingTexture().getSize().x / 2,
		this->m_sprite.getUnderlyingTexture().getSize().y / 2));
}

const Sprite& Character::getSprite() const noexcept {
	return this->m_sprite;
}

Sprite& Character::getSprite() noexcept {
	return this->m_sprite;
}