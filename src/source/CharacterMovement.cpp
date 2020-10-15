#include "CharacterMovement.h"

CharacterMovement::CharacterMovement(const std::unordered_map<Direction, MovementCallback, EnumHash<Direction>>& movementCallbacks) noexcept {
	this->isMovingDown = false;
	this->isMovingRight = false;
	this->isMovingLeft = false;
	this->isMovingUp = false;

	this->m_movementCallbacks[static_cast<std::underlying_type_t<Direction>>(Direction::Up)] = movementCallbacks.at(Direction::Up);
	this->m_movementCallbacks[static_cast<std::underlying_type_t<Direction>>(Direction::Down)] = movementCallbacks.at(Direction::Down);
	this->m_movementCallbacks[static_cast<std::underlying_type_t<Direction>>(Direction::Right)] = movementCallbacks.at(Direction::Right);
	this->m_movementCallbacks[static_cast<std::underlying_type_t<Direction>>(Direction::Left)] = movementCallbacks.at(Direction::Left);
}

void CharacterMovement::AddMoveDirection(Direction direction) noexcept {
	switch (direction) {
	case Direction::Right:
		this->isMovingRight = true;
		break;
	case Direction::Left:
		this->isMovingLeft = true;
		break;
	case Direction::Up:
		this->isMovingUp = true;
		break;
	case Direction::Down:
		this->isMovingDown = true;
		break;
	}
}

void CharacterMovement::RemoveMoveDirection(Direction direction) noexcept {
	switch (direction) {
	case Direction::Right:
		this->isMovingRight = false;
		break;
	case Direction::Left:
		this->isMovingLeft = false;
		break;
	case Direction::Up:
		this->isMovingUp = false;
		break;
	case Direction::Down:
		this->isMovingDown = false;
		break;
	}
}

std::pair<float, float> CharacterMovement::getHowToMove(const sf::Time& timeSinceLastFrameDraw) const noexcept {
	float verticalMovement = 0;
	float horizontalMovement = 0;

	if (this->isMovingUp) {
		verticalMovement += this->m_movementCallbacks[
			static_cast<std::underlying_type_t<Direction>>(Direction::Up)](timeSinceLastFrameDraw);
	}
	if (this->isMovingDown) {
		verticalMovement += this->m_movementCallbacks[
			static_cast<std::underlying_type_t<Direction>>(Direction::Down)](timeSinceLastFrameDraw);
	}
	if (this->isMovingLeft) {
		horizontalMovement += this->m_movementCallbacks[
			static_cast<std::underlying_type_t<Direction>>(Direction::Left)](timeSinceLastFrameDraw);
	}
	if (this->isMovingRight) {
		horizontalMovement += this->m_movementCallbacks[
			static_cast<std::underlying_type_t<Direction>>(Direction::Right)](timeSinceLastFrameDraw);
	}
	return { horizontalMovement, verticalMovement };
}