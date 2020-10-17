#ifndef GAME
#define GAME

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <type_traits>
#include <utility>
#include <functional>

#include <SFML/Graphics.hpp>

#include "class_utils.hpp"
#include "Map.h"
#include "Character.h"
#include "Sound.h"
#include "WindowText.h"

class Hero;

class Game final
{
public:
	enum class GameOverStatus { RestartGame, CloseGame };

	Game(sf::RenderWindow& window) noexcept;
	DEFAULT_MOVE_OPERATIONS(Game);
	DISALLOW_COPY_OPERATIONS(Game);

	GameOverStatus start();
	const Map& getMap() const noexcept;
	const Hero& getHero() const noexcept;
	void addCharacter(std::unique_ptr<Character> character);

	void playRocketShootSound();
	void playRocketHitEnemySound();

	~Game() = default;

private:
	using CharacterID = unsigned long long;

	CharacterID addCharacterAndGetID(std::unique_ptr<Character> character);
	void removeCharacter(CharacterID id);

	void addScore() noexcept;
	GameOverStatus gameOver();

	WindowText getGameHeadingText() const;
	WindowText getGameInstructionsText() const;
	WindowText getGameScoreText() const;

	void playBackgroundMusic(const std::string& musicFilePath) const;

	std::vector<std::pair<Character*, Character*>> detectCollisions() const;

	std::unique_ptr<Map> m_map;

	std::unordered_map<std::type_index, 
		std::unordered_map<CharacterID, std::unique_ptr<Character>>> m_characters;

	std::unordered_map<CharacterID,
		std::reference_wrapper<std::unordered_map<CharacterID, std::unique_ptr<Character>>>> idToCharactersMap;

	Hero* m_hero;
	sf::RenderWindow& m_window;

	EventsHandling m_eventsHandling;
	SceneUpdater m_sceneUpdater;

	Sound m_shootSound;
	Sound m_hitSound;

	unsigned int m_score;
	unsigned int m_score = 0;
};

#endif