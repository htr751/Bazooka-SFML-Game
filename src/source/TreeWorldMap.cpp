#include <utility>

#include "TreeWorldMap.h"
#include "AssetsDefinitions.h"

TreeWorldMap::TreeWorldMap(sf::Vector2f viewSize): m_sprite(treeWorldMapFilePath), m_viewSize(std::move(viewSize)) {}

float TreeWorldMap::UpperLimitForMovement() const noexcept {
	return 0.65f * m_viewSize.y;
}

float TreeWorldMap::LowerLimitForMovement() const noexcept {
	return 1.00f * m_viewSize.y;
}

float TreeWorldMap::RightLimitForMovement() const noexcept {
	return 1.00f * m_viewSize.x;
}

float TreeWorldMap::LeftLimitForMovement() const noexcept {
	return 0;
}

const Sprite& TreeWorldMap::getMapSprite() const noexcept {
	return this->m_sprite;
}