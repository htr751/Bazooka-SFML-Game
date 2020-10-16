#ifndef ROCKET
#define ROCKET

#include <vector>

#include "Character.h"
#include "Game.h"

class Rocket final : public Character
{
public:
	Rocket(Game& game, const std::string& textureFilePath, sf::Vector2f position, float rocketSpeed);

	void registerEventHandlers(EventsHandling& eventsHandling) override;
	void removeEventHandlers(EventsHandling& EventsHandling) override;

	void registerSceneUpdater(SceneUpdater& sceneUpdater) override;
	void removeSceneUpdater(SceneUpdater& sceneUpdater) override;

	bool isAlive() const noexcept override;
	void handleCollision(Character* characterCollisionedWith) override;

	~Rocket() = default;
private:

	decltype(auto) updateLocation() noexcept {
		return [this](const sf::Time& timeSinceLastFrameDraw) {
			auto xMovement = timeSinceLastFrameDraw.asSeconds() * this->m_speed;
			const auto& currentPosition = this->getSprite().getSprite().getPosition();

			if (currentPosition.x + xMovement > this->m_game.getMap().RightLimitForMovement()) {
				xMovement = this->m_game.getMap().RightLimitForMovement() - currentPosition.x;
				this->m_isAlive = false;
			}

			this->getSprite().getSprite().move(sf::Vector2f(xMovement, 0));
		};
	}

	std::vector<SceneUpdater::CallbackID> m_registeredSceneUpdaterCallbacks;

	float m_speed = 400.0f;
	bool m_isAlive;
};

#endif