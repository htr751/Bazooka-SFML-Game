#ifndef HERO
#define HERO

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Character.h"
#include "Game.h"
#include "CharacterMovement.h"
#include "JumpAction.h"
#include "class_utils.hpp"

class Hero final: public Character
{
public:

	Hero(Game& game, const std::string& textureFilePath, const sf::Vector2f& position);
	DEFAULT_MOVE_OPERATIONS(Hero);
	DISALLOW_COPY_OPERATIONS(Hero);

	void setHeroSpeed(float horizontalSpeed, float verticalSpeed) noexcept;

	void registerEventHandlers(EventsHandling& eventsHandling) override;
	void removeEventHandlers(EventsHandling& EventsHandling) override;

	void registerSceneUpdater(SceneUpdater& sceneUpdater) override;
	void removeSceneUpdater(SceneUpdater& SceneUpdater) override;

	bool isAlive() const noexcept override;
	void handleCollision(Character* characterCollisionedWith) override;

	~Hero() override {}

private:
	void shootRocket();

	void startJumpAction(float velocity) noexcept {
		if (!this->m_jumpAction.isInJumpAction()) {
			this->m_jumpAction.startJumpAction(velocity, this->m_sprite.getSprite().getPosition().y);
		}
	}

	decltype(auto) updateJumpState() noexcept {
		return [this](const sf::Time& timeSinceLastFrameDraw) {
			const auto yPositionMovement = this->m_jumpAction.getHowToMoveCharacter(timeSinceLastFrameDraw,
				this->m_sprite.getSprite().getPosition().y);
			this->getSprite().getSprite().move(sf::Vector2f(0.0f, yPositionMovement));
		};
	}

	decltype(auto) onMoveUp() noexcept {
		return [this](const sf::Time& timeSinceLastFrameDraw) {
			if (this->m_jumpAction.isInJumpAction()) { // if not on ground, player can't go up
				return 0.0f;
			}
			return -(this->m_verticalSpeed * timeSinceLastFrameDraw.asSeconds());
		};
	}

	decltype(auto) onMoveDown() noexcept {
		return [this](const sf::Time& timeSinceLastFrameDraw) {
			if (this->m_jumpAction.isInJumpAction()) { // if not on ground, player can't go down
				return 0.0f;
			}
			return this->m_verticalSpeed * timeSinceLastFrameDraw.asSeconds();
		};
	}

	decltype(auto) onMoveRight() noexcept {
		return [this](const sf::Time& timeSinceLastFrameDraw) {
			return this->m_horizontalSpeed * timeSinceLastFrameDraw.asSeconds();
		};
	}

	decltype(auto) onMoveLeft() noexcept {
		return [this](const sf::Time& timeSinceLastFrameDraw) {
			return -(this->m_horizontalSpeed * timeSinceLastFrameDraw.asSeconds());
		};
	}

	decltype(auto) onMove() noexcept {
		return [this](const sf::Time& timeSinceLastFrameDraw) {
			auto [xDirection, yDirection] = this->m_movement.getHowToMove(timeSinceLastFrameDraw);
			const auto& heroPosition = this->getSprite().getSprite().getPosition();
			const auto& heroSize = this->getSprite().getUnderlyingTexture().getSize();

			if (yDirection != 0) {
				if (heroPosition.y + yDirection < (this->m_game.getMap().UpperLimitForMovement())) {
					yDirection = (this->m_game.getMap().UpperLimitForMovement()) - heroPosition.y;
				}
				if (heroPosition.y + yDirection > (this->m_game.getMap().LowerLimitForMovement() - heroSize.y / 2)) {
					yDirection = (this->m_game.getMap().LowerLimitForMovement() - heroSize.y / 2) - heroPosition.y;
				}
			}
			if (xDirection != 0) {
				if (heroPosition.x + xDirection > (this->m_game.getMap().RightLimitForMovement() - heroSize.x / 2)) {
					xDirection = (this->m_game.getMap().RightLimitForMovement() - heroSize.x / 2) - heroPosition.x;
				}
				if (heroPosition.x + xDirection < (this->m_game.getMap().LeftLimitForMovement() + heroSize.x / 2)) {
					xDirection = (this->m_game.getMap().LeftLimitForMovement() + heroSize.x / 2) - heroPosition.x;
				}
			}

			this->m_sprite.getSprite().move(sf::Vector2f(xDirection, yDirection));
		};
	}

	decltype(auto) onKeyPressed() noexcept {
		return [this](sf::Event::KeyEvent event) {
			switch (event.code) {
			case sf::Keyboard::Right:
				m_movement.AddMoveDirection(CharacterMovement::Direction::Right);
				break;
			case sf::Keyboard::Left:
				m_movement.AddMoveDirection(CharacterMovement::Direction::Left);
				break;
			case sf::Keyboard::Up:
				m_movement.AddMoveDirection(CharacterMovement::Direction::Up);
				break;
			case sf::Keyboard::Down:
				m_movement.AddMoveDirection(CharacterMovement::Direction::Down);
				break;
			case sf::Keyboard::Space:
				this->startJumpAction(-100.0f);
				break;
			case sf::Keyboard::Z:
				this->shootRocket();;
				break;
			default:
				break;
			}
		};
	}

	decltype(auto) onKeyReleased() noexcept {
		return [this](sf::Event::KeyEvent event) {
			switch (event.code) {
			case sf::Keyboard::Right:
				m_movement.RemoveMoveDirection(CharacterMovement::Direction::Right);
				break;
			case sf::Keyboard::Left:
				m_movement.RemoveMoveDirection(CharacterMovement::Direction::Left);
				break;
			case sf::Keyboard::Up:
				m_movement.RemoveMoveDirection(CharacterMovement::Direction::Up);
				break;
			case sf::Keyboard::Down:
				m_movement.RemoveMoveDirection(CharacterMovement::Direction::Down);
				break;
			default:
				break;
			}
		};
	}

	CharacterMovement m_movement;
	JumpAction m_jumpAction;

	std::vector<EventsHandling::CallbackID> m_registeredEventHandlers;
	std::vector<SceneUpdater::CallbackID> m_registeredSceneUpdaterCallbacks;

	float m_horizontalSpeed = 100;
	float m_verticalSpeed = 100;

	bool m_isAlive;
};

#endif