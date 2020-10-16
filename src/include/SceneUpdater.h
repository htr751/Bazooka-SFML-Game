#ifndef SCENE_UPDATER
#define SCENE_UPDATER

#include <unordered_map>
#include <functional>

#include <SFML/Graphics.hpp>


class SceneUpdater
{
public:
	using UpdateCallback = std::function<void(const sf::Time&)>;
	using CallbackID = unsigned long long; 
	SceneUpdater() = default;
	
	//this method register callback and returns its ID for future referencing
	CallbackID registerUpdateCallback(UpdateCallback callback);
	void updateScene(const sf::Time& timeSinceLastFrameDraw) const;

	//given callback id, this method removes the callback
	void removeCallback(CallbackID id);

	void removeAllUpdateCallbacks();

private:
	std::unordered_map<CallbackID, UpdateCallback> updateCallbacks;
};

#endif