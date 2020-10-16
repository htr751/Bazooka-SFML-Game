#ifndef ENEMY
#define ENEMY

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Character.h"
#include "Game.h"
#include "Hero.h"
#include "class_utils.hpp"

class Enemy final: public Character
{
public:
	Enemy(Game& game, const std::string& textureFilePath, const sf::Vector2f& position);
	DEFAULT_MOVE_OPERATIONS(Enemy);
	DISALLOW_COPY_OPERATIONS(Enemy);

	void setVelocity(const float newVelocity) noexcept;

	void registerSceneUpdater(SceneUpdater& sceneUpdater) override;
	void removeSceneUpdater(SceneUpdater& SceneUpdater) override;

	void registerEventHandlers(EventsHandling& eventsHandling) override;
	void removeEventHandlers(EventsHandling& eventsHandling) override;

	bool isAlive() const noexcept override;
	void handleCollision(Character* characterCollisionedWith) override;

	~Enemy() override {}

private:
	decltype(auto) updatePosition() noexcept {
		return [this](const sf::Time& timeSinceLastFrameDraw) {
			const auto& heroPosition = this->m_game.getHero().getSprite().getSprite().getPosition();
			const auto& enemyPosition = this->getSprite().getSprite().getPosition();

			const auto distanceSlopeBetweenHeroToEnemy = (heroPosition.y - enemyPosition.y) / (heroPosition.x - enemyPosition.x);

			const auto xMovement = heroPosition.x > enemyPosition.x ? std::abs(this->m_velocity * timeSinceLastFrameDraw.asSeconds()) :
				-std::abs(this->m_velocity * timeSinceLastFrameDraw.asSeconds());

			const auto yMovement = heroPosition.y > enemyPosition.y ?
				std::abs(this->m_velocity * timeSinceLastFrameDraw.asSeconds() * distanceSlopeBetweenHeroToEnemy) :
				-std::abs(this->m_velocity * timeSinceLastFrameDraw.asSeconds() * distanceSlopeBetweenHeroToEnemy);

			this->getSprite().getSprite().move(sf::Vector2f(xMovement, yMovement));
		};
	}
	
	std::vector<SceneUpdater::CallbackID> m_registeredSceneUpdaterCallbacks;

	float m_velocity = 100.0f; // default velocity
	bool m_isAlive;
};

#endif