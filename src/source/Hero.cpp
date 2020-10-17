#include <memory>
#include <stdexcept>

#include "Hero.h"
#include "Rocket.h"
#include "Enemy.h"
#include "AssetsDefinitions.h"

Hero::Hero(Game& game, const std::string& textureFilePath, const sf::Vector2f& position):
	Character(game, textureFilePath, position), m_movement({
		{CharacterMovement::Direction::Left, this->onMoveLeft()},
		{CharacterMovement::Direction::Right, this->onMoveRight()},
		{CharacterMovement::Direction::Up, this->onMoveUp()},
		{CharacterMovement::Direction::Down, this->onMoveDown()}
		}) {

	this->m_sprite.getSprite().setPosition(position);
	this->m_sprite.getSprite().setOrigin(sf::Vector2f(this->m_sprite.getUnderlyingTexture().getSize().x / 2,
		this->m_sprite.getUnderlyingTexture().getSize().y / 2));
	this->m_isAlive = true;
}

void Hero::shootRocket() {
	const auto& currentPosition = this->getSprite().getSprite().getPosition();
	auto rocket = std::make_unique<Rocket>(m_game, rocketFilePath,
		sf::Vector2f(currentPosition.x + 10, currentPosition.y), 400.0f);

	this->m_game.addCharacter(std::move(rocket));
	this->m_game.playRocketShootSound();
}

bool Hero::isAlive() const noexcept {
	return m_isAlive;
}

void Hero::handleCollision(Character* characterCollisionedWith) {
	Enemy* enemyCollisionedWith = dynamic_cast<Enemy*>(characterCollisionedWith);
	if (!enemyCollisionedWith) {
		throw std::runtime_error("error - hero collisioned with non enemy character type");
	}

	this->m_isAlive = false;
}

void Hero::setHeroSpeed(float horizontalSpeed, float verticalSpeed) noexcept {
	this->m_horizontalSpeed = horizontalSpeed;
	this->m_verticalSpeed = verticalSpeed;
}

void Hero::registerEventHandlers(EventsHandling& eventsHandling) {
	this->m_registeredEventHandlers.push_back(
		eventsHandling.registerEventHandler(sf::Event::EventType::KeyPressed, this->onKeyPressed()));

	this->m_registeredEventHandlers.push_back(
		eventsHandling.registerEventHandler(sf::Event::EventType::KeyReleased, this->onKeyReleased()));
}

void Hero::removeEventHandlers(EventsHandling& EventsHandling) {
	for (const auto& id : m_registeredEventHandlers) {
		EventsHandling.removeEventHandler(id);
	}
	this->m_registeredEventHandlers.clear();
}

void Hero::registerSceneUpdater(SceneUpdater& sceneUpdater) {
	this->m_registeredSceneUpdaterCallbacks.push_back(
		sceneUpdater.registerUpdateCallback(this->onMove()));

	this->m_registeredSceneUpdaterCallbacks.push_back(
		sceneUpdater.registerUpdateCallback(this->updateJumpState()));
}

void Hero::removeSceneUpdater(SceneUpdater& sceneUpdater) {
	for (const auto& id : m_registeredSceneUpdaterCallbacks) {
		sceneUpdater.removeCallback(id);
	}
	this->m_registeredSceneUpdaterCallbacks.clear();
}