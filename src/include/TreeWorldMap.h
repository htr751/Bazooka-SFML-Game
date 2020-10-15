#ifndef TREE_WORLD_MAP
#define TREE_WORLD_MAP

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "class_utils.hpp"

class TreeWorldMap : public Map
{
public:
	TreeWorldMap(sf::Vector2f viewSize);
	DEFAULT_MOVE_OPERATIONS(TreeWorldMap);
	DISALLOW_COPY_OPERATIONS(TreeWorldMap);

	float UpperLimitForMovement() const noexcept override;
	float LowerLimitForMovement() const noexcept override;
	float RightLimitForMovement() const noexcept override;
	float LeftLimitForMovement() const noexcept override;

	const Sprite& getMapSprite() const noexcept override;
private:
	Sprite m_sprite;
	sf::Vector2f m_viewSize;
};

#endif