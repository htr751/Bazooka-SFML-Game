#include "SceneUpdater.h"

void SceneUpdater::registerUpdateCallback(UpdateCallback callback) {
	this->update_callbacks.push_back(callback);
}

void SceneUpdater::updateScene(const sf::Time& timeSinceLastFrameDraw) const {
	for (const auto& callback : this->update_callbacks) {
		callback(timeSinceLastFrameDraw);
	}
}