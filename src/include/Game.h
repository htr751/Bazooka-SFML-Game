#ifndef GAME
#define GAME

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <type_traits>
#include <utility>

#include <SFML/Graphics.hpp>

#include "class_utils.hpp"
#include "Map.h"
#include "Character.h"

class Hero;

class Game final
{
public:
	Game(sf::RenderWindow& window) noexcept;
	DEFAULT_MOVE_OPERATIONS(Game);
	DISALLOW_COPY_OPERATIONS(Game);

	void start();
	const Map& getMap() const noexcept;
	const Hero& getHero() const noexcept;
	void addCharacter(std::unique_ptr<Character> character);

	~Game() = default;

private:
	std::vector<std::pair<Character*, Character*>> detectCollisions() const;

	std::unique_ptr<Map> m_map;

	std::unordered_map<std::type_index, std::vector<std::unique_ptr<Character>>> m_characters;
	Hero* m_hero;
	sf::RenderWindow& m_window;

	EventsHandling m_eventsHandling;
	SceneUpdater m_sceneUpdater;
};

#endif