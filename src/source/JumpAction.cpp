#include "JumpAction.h"

void JumpAction::startJumpAction(float initialVelocity, float currentYPosition) noexcept {
	this->velocity = initialVelocity;
	this->isOnGround = false;
	this->yPositionInJumpStart = currentYPosition;
}

bool JumpAction::isInJumpAction() const noexcept {
	return !this->isOnGround;
}

float JumpAction::getHowToMoveCharacter(const sf::Time& timeSinceLastFrameDraw, float currentYPosition) noexcept {
	if (this->isInJumpAction()) {
		float yDirectionMovement = this->velocity * timeSinceLastFrameDraw.asSeconds() + 
			0.50f * JumpAction::gravity * timeSinceLastFrameDraw.asSeconds() * timeSinceLastFrameDraw.asSeconds();

		if (currentYPosition + yDirectionMovement > this->yPositionInJumpStart) {
			yDirectionMovement = this->yPositionInJumpStart - currentYPosition;
			this->isOnGround = true;
		}

		this->velocity += JumpAction::gravity * timeSinceLastFrameDraw.asSeconds();
		return yDirectionMovement;
	}
	return 0.0f;
}