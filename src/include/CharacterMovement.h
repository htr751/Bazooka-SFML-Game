#ifndef CHARACTER_MOVEMENT
#define CHARACTER_MOVEMENT

#include <utility>
#include <functional>
#include <array>
#include <unordered_map>
#include <type_traits>

#include <SFML/Graphics.hpp>

#include "EnumClassHash.h"
#include "class_utils.hpp"

class CharacterMovement
{
public:
	enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3};
	using MovementCallback = std::function<float(const sf::Time&)>;

	CharacterMovement(const std::unordered_map<Direction, MovementCallback, EnumHash<Direction>>& movementCallbacks) noexcept;
	DEFAULT_MOVE_OPERATIONS(CharacterMovement);
	DISALLOW_COPY_OPERATIONS(CharacterMovement);

	void AddMoveDirection(Direction direction) noexcept;
	void RemoveMoveDirection(Direction direction) noexcept;

	std::pair<float, float> getHowToMove(const sf::Time& timeSinceLastFrameDraw) const noexcept;

private:
	bool isMovingRight;
	bool isMovingLeft;
	bool isMovingUp;
	bool isMovingDown;

	std::array<MovementCallback, 4> m_movementCallbacks;
};

#endif