#ifndef CHARACTER
#define CHARACTER

#include <string>

#include <SFML/Graphics.hpp>

#include "Sprite.h"
#include "EventsHandling.h"
#include "SceneUpdater.h"
#include "class_utils.hpp"

class Game;

class Character
{
public:
	Character(Game& game, const std::string& textureFilePath, const sf::Vector2f& position);
	DEFAULT_MOVE_OPERATIONS(Character);
	DISALLOW_COPY_OPERATIONS(Character);

	const Sprite& getSprite() const noexcept;
	Sprite& getSprite() noexcept;

	virtual void registerEventHandlers(EventsHandling& eventsHandling) = 0;
	virtual void registerSceneUpdater(SceneUpdater& sceneUpdater) = 0;

	virtual bool isAlive() const noexcept = 0;
	virtual void handleCollision(Character* characterCollisionedWith) = 0;

	virtual ~Character() noexcept {};
protected:
	Sprite m_sprite;
	Game& m_game;
};

#endif