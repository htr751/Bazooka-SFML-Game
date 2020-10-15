#ifndef MAP
#define MAP

#include "Sprite.h"

class Map
{
public:
	virtual float UpperLimitForMovement() const noexcept = 0;
	virtual float LowerLimitForMovement() const noexcept = 0;
	virtual float RightLimitForMovement() const noexcept = 0;
	virtual float LeftLimitForMovement() const noexcept = 0;

	virtual const Sprite& getMapSprite() const noexcept = 0;

	virtual ~Map() noexcept {}
};

#endif