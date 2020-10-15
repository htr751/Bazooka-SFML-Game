#include <stdexcept>

#include "Rocket.h"
#include "Enemy.h"

Rocket::Rocket(Game& game, const std::string& textureFilePath, sf::Vector2f position, float rocketSpeed)
	:Character(game, textureFilePath, position), m_speed(rocketSpeed), m_isAlive(true) {}

void Rocket::registerEventHandlers(EventsHandling& eventsHandling) {}

void Rocket::registerSceneUpdater(SceneUpdater& sceneUpdater) {
	sceneUpdater.registerUpdateCallback(this->updateLocation());
}

bool Rocket::isAlive() const noexcept {
	return this->m_isAlive;
}

void Rocket::handleCollision(Character* characterCollisionedWith) {
	Enemy* enemyCollisionedWith = dynamic_cast<Enemy*>(characterCollisionedWith);

	if (!enemyCollisionedWith) {
		throw std::runtime_error("error - collisioned with non enemy character type");
	}

	this->m_isAlive = false;
}