#ifndef ROCKET
#define ROCKET

#include "Character.h"
#include "Game.h"

class Rocket final : public Character
{
public:
	Rocket(Game& game, const std::string& textureFilePath, sf::Vector2f position, float rocketSpeed);

	void registerEventHandlers(EventsHandling& eventsHandling) override;
	void registerSceneUpdater(SceneUpdater& sceneUpdater) override;

	bool isAlive() const noexcept override;
	void handleCollision(Character* characterCollisionedWith) override;

	~Rocket() = default;
private:

	decltype(auto) updateLocation() noexcept {
		return [this](const sf::Time& timeSinceLastFrameDraw) {
			this->getSprite().getSprite().move(sf::Vector2f(timeSinceLastFrameDraw.asSeconds() * this->m_speed, 0));
		};
	}

	float m_speed = 400.0f;
	bool m_isAlive;
};

#endif