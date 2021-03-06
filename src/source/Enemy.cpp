#include <cmath>

#include "Enemy.h"
#include "Rocket.h"

Enemy::Enemy(Game& game, const std::string& textureFilePath, const sf::Vector2f& position)
	: Character(game, textureFilePath, position) {
	this->m_sprite.getSprite().setPosition(position);
	this->m_sprite.getSprite().setOrigin(sf::Vector2f(this->m_sprite.getUnderlyingTexture().getSize().x / 2,
		this->m_sprite.getUnderlyingTexture().getSize().y / 2));
	this->m_isAlive = true;
}

bool Enemy::isAlive() const noexcept {
	return this->m_isAlive;
}

void Enemy::handleCollision(Character* characterCollisionedWith) {
	Rocket* rocketCollisionedWith = dynamic_cast<Rocket*>(characterCollisionedWith);
	if (!rocketCollisionedWith) {
		// collisioned with other character type (hero)
		return;
	}

	this->m_isAlive = false;
}

void Enemy::setVelocity(const float newVelocity) noexcept {
	this->m_velocity = newVelocity;
}

float Enemy::getVelocity() const noexcept {
	return this->m_velocity;
}

void Enemy::registerSceneUpdater(SceneUpdater& sceneUpdater) {
	this->m_registeredSceneUpdaterCallbacks.push_back(
		sceneUpdater.registerUpdateCallback(this->updatePosition()));
}

void Enemy::removeSceneUpdater(SceneUpdater& SceneUpdater) {
	for (const auto& id : this->m_registeredSceneUpdaterCallbacks) {
		SceneUpdater.removeCallback(id);
	}
}

void Enemy::registerEventHandlers(EventsHandling& eventsHandling) {}
void Enemy::removeEventHandlers(EventsHandling& eventsHandling) {}