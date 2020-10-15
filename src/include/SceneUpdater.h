#ifndef SCENE_UPDATER
#define SCENE_UPDATER

#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>


class SceneUpdater
{
public:
	using UpdateCallback = std::function<void(const sf::Time&)>;
	SceneUpdater() = default;
	void registerUpdateCallback(UpdateCallback callback);
	void updateScene(const sf::Time& timeSinceLastFrameDraw) const;

private:
	std::vector<UpdateCallback> update_callbacks;
};

#endif