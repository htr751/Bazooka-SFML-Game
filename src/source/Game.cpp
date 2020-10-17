#include <utility>
#include <iostream>
#include <numeric>

#include <effolkronium/random.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"
#include "TreeWorldMap.h"
#include "Hero.h"
#include "Character.h"
#include "AssetsDefinitions.h"
#include "Enemy.h"
#include "Hero.h"
#include "Rocket.h"
#include "map_utils.h"

Game::Game(sf::RenderWindow& window) noexcept : m_window(window),
 m_shootSound(shootSoundFilePath), m_hitSound(hitSoundFilePath) {}

const Map& Game::getMap() const noexcept { return *this->m_map; }
const Hero& Game::getHero() const noexcept { return *this->m_hero; }

void Game::addCharacter(std::unique_ptr<Character> character) {
	this->addCharacterAndGetID(std::move(character));
}

Game::CharacterID Game::addCharacterAndGetID(std::unique_ptr<Character> character) {
	using Random = effolkronium::random_static;

	CharacterID generatedID = 0;
	do {
		generatedID = Random::get<CharacterID>(0, std::numeric_limits<CharacterID>::max());
	} while (this->idToCharactersMap.find(generatedID) != this->idToCharactersMap.end());

	character->registerEventHandlers(this->m_eventsHandling);
	character->registerSceneUpdater(this->m_sceneUpdater);

	std::type_index characterTypeIndex = typeid(*character);

	this->m_characters[characterTypeIndex].insert(std::make_pair(generatedID, std::move(character)));
	this->idToCharactersMap.insert(std::make_pair(generatedID,
		 std::ref(this->m_characters[characterTypeIndex])));
	
	return generatedID;
}

void Game::removeCharacter(CharacterID id) {
	auto& character = this->idToCharactersMap.at(id).get().at(id);
	if (dynamic_cast<Enemy*>(character.get())) { //if we removed an enemy, count it to the score calculation
		addScore();
	}

	character->removeEventHandlers(this->m_eventsHandling);
	character->removeSceneUpdater(this->m_sceneUpdater);

	this->idToCharactersMap.at(id).get().erase(id);
	this->idToCharactersMap.erase(id);
}

void Game::addScore() noexcept {
	this->m_score++;
}

std::vector<std::pair<Character*, Character*>> Game::detectCollisions() const {
	std::type_index enemyTypeIndex = typeid(Enemy);
	std::type_index rocketTypeIndex = typeid(Rocket);

	std::vector<std::pair<Character*, Character*>> collisions;

	// if there are not enemies, then collisions can't happen
	if (!map_utils::contains(this->m_characters, enemyTypeIndex)) {
		return collisions;
	}

	for (const auto& [id, enemy] : this->m_characters.at(enemyTypeIndex)) {
		const auto heroBounds = this->m_hero->getSprite().getSprite().getGlobalBounds();
		const auto enemyBounds = enemy->getSprite().getSprite().getGlobalBounds();

		if (heroBounds.intersects(enemyBounds)) {
			collisions.push_back(std::make_pair(this->m_hero, enemy.get()));
		}

		// check for collision between rocket and enemy only if there are rockets
		if (map_utils::contains(this->m_characters, rocketTypeIndex)) {
			for (const auto& [id, rocket] : this->m_characters.at(rocketTypeIndex)) {
				const auto rocketBounds = rocket->getSprite().getSprite().getGlobalBounds();

				if (rocketBounds.intersects(enemyBounds)) {
					collisions.push_back(std::make_pair(rocket.get(), enemy.get()));
				}
			}
		}
	}

	return collisions;
}

WindowText Game::getGameHeadingText() const {
	const auto& viewSize = m_window.getView().getSize();
	return  WindowText(snackerComicFontFilePath, "Bazooka", 
				sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.1f), 80);
}

WindowText Game::getGameInstructionsText() const {
	const auto& viewSize = m_window.getView().getSize();
	return WindowText(snackerComicFontFilePath, 
				"Move using the arrows, jump with space and shoot on enemy with pressing Z", 
				sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.2f), 30);
}

WindowText Game::getGameScoreText() const {
	const auto& viewSize = m_window.getView().getSize();
	return WindowText(arialFontFilePath, 
				"Score: " + std::to_string(this->m_score), 
				sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.3), 70);
}

void Game::playBackgroundMusic(const std::string& musicFilePath) const {
	sf::Music backgroundMusic;
	backgroundMusic.openFromFile(musicFilePath);
	backgroundMusic.play();
}

void Game::playRocketShootSound() {
	this->m_shootSound.playSound();
}

void Game::playRocketHitEnemySound() {
	this->m_hitSound.playSound();
}

Game::GameOverStatus Game::start() {
	const auto& viewSize = m_window.getView().getSize();
	this->m_map = std::make_unique<TreeWorldMap>(viewSize);

	auto hero = std::make_unique<Hero>(*this, heroFilePath, sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.65f));
	auto enemy = std::make_unique<Enemy>(*this, enemyFilePath, sf::Vector2f(viewSize.x * 0.75f, viewSize.y * 0.65f));

	m_hero = hero.get();
	this->addCharacter(std::move(hero));
	this->addCharacter(std::move(enemy));

	sf::Clock time;

	while (m_window.isOpen()) {
		if (!this->m_hero->isAlive()) {
			return this->gameOver();
		}
		m_eventsHandling.handleEvents(m_window);

		sf::Time timeSinceLastFrameDraw = time.restart();
		m_sceneUpdater.updateScene(timeSinceLastFrameDraw);

		m_window.clear(sf::Color(0xAD, 0xD8, 0xE6));
		m_window.draw(this->getMap().getMapSprite().getSprite());

		m_window.draw(getGameHeadingText().getText());
		m_window.draw(getGameInstructionsText().getText());
		m_window.draw(getGameScoreText().getText());

		std::vector<CharacterID> charactersToRemove;
		for (const auto& [typeIndex, characters] : this->m_characters) {
			for (const auto& [id, character] : characters) {
				if (character->isAlive()) {
					m_window.draw(character->getSprite().getSprite());
				}
				else {
					charactersToRemove.push_back(id);
				}
			}
		}

		for (const auto& id : charactersToRemove) {
			removeCharacter(id);
		}

		m_window.display();
		const auto& charactersCollisions = this->detectCollisions();
		for (const auto& [firstCharacter, secondCharacter] : charactersCollisions) {
			firstCharacter->handleCollision(secondCharacter);
			secondCharacter->handleCollision(firstCharacter);
		}
	}
	return Game::GameOverStatus::CloseGame;
}

Game::GameOverStatus Game::gameOver() {
	const auto resetGame = [this](){
		this->m_characters.clear();
		this->idToCharactersMap.clear();
		this->m_hero = nullptr;
		this->m_sceneUpdater.removeAllUpdateCallbacks();
		this->m_eventsHandling.removeAllEventHandlers();
	};

	resetGame();

	this->m_window.clear(sf::Color(0xAD, 0xD8, 0xE6));
	this->m_window.draw(this->getMap().getMapSprite().getSprite());

	this->m_window.draw(getGameInstructionsText().getText());
	this->m_window.draw(getGameHeadingText().getText());
	this->m_window.draw(getGameScoreText().getText());

	this->m_window.display();

	bool restartGame = false;

	this->m_eventsHandling.registerEventHandler(sf::Event::EventType::KeyPressed, 
		[&restartGame](sf::Event::KeyEvent event) mutable {
			if (event.code == sf::Keyboard::Enter) {
				restartGame = true;
			}
		}
	);

	while (!restartGame && this->m_window.isOpen()) {
		this->m_eventsHandling.handleEvents(this->m_window);
	}

	if (!restartGame) {
		return Game::GameOverStatus::CloseGame;
	}

	resetGame();
	this->m_map.reset();
	this->m_score = 0;

	return Game::GameOverStatus::RestartGame;
}