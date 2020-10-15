#ifndef JUMP_ACTION
#define JUMP_ACTION

#include <SFML/Graphics.hpp>

class JumpAction
{
public:
	void startJumpAction(float initialVelocity, float currentYPosition) noexcept;
	bool isInJumpAction() const noexcept;

	float getHowToMoveCharacter(const sf::Time& timeSinceLastFrameDraw, float currentYPosition) noexcept;
private:
	float velocity = 0.0f;
	float mass = 0.0f;
	bool isOnGround = true;
	float yPositionInJumpStart = 0.0f;

	static constexpr float gravity = 98.00f; // decimeter to second square
};

#endif
