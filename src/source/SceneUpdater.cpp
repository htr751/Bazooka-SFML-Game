#include <numeric>
#include <utility>
#include <stdexcept>

#include <effolkronium/random.hpp>

#include "SceneUpdater.h"

SceneUpdater::CallbackID SceneUpdater::registerUpdateCallback(UpdateCallback callback) {
	using Random = effolkronium::random_static;

	CallbackID generatedID = 0;
	do {
		generatedID = Random::get<CallbackID>(0, std::numeric_limits<CallbackID>::max());
	} while (this->updateCallbacks.find(generatedID) != this->updateCallbacks.end());
	
	this->updateCallbacks.insert(std::make_pair(generatedID, callback));
	return generatedID;
}

void SceneUpdater::updateScene(const sf::Time& timeSinceLastFrameDraw) const {
	for (const auto& [id, callback] : this->updateCallbacks) {
		callback(timeSinceLastFrameDraw);
	}
}

void SceneUpdater::removeCallback(CallbackID id) {
	if (this->updateCallbacks.find(id) == this->updateCallbacks.end()) {
		throw std::runtime_error("error - attempt to remove nonexisting callback");
	}

	this->updateCallbacks.erase(id);
}