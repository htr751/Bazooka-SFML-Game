#include <utility>
#include <iostream>

#include "Game.h"
#include "TreeWorldMap.h"
#include "Hero.h"
#include "Character.h"
#include "AssetsDefinitions.h"
#include "Enemy.h"
#include "Hero.h"
#include "Rocket.h"
#include "map_utils.h"

Game::Game(sf::RenderWindow& window) noexcept : m_window(window) {}

const Map& Game::getMap() const noexcept { return *this->m_map; }
const Hero& Game::getHero() const noexcept { return *this->m_hero; }

void Game::addCharacter(std::unique_ptr<Character> character) {
	character->registerEventHandlers(this->m_eventsHandling);
	character->registerSceneUpdater(this->m_sceneUpdater);

	this->m_characters[typeid(*character)].push_back(std::move(character));
}

std::vector<std::pair<Character*, Character*>> Game::detectCollisions() const {
	std::type_index enemyTypeIndex = typeid(Enemy);
	std::type_index rocketTypeIndex = typeid(Rocket);

	std::vector<std::pair<Character*, Character*>> collisions;

	// if there are not enemies, then collisions can't happen
	if (!map_utils::contains(this->m_characters, enemyTypeIndex)) {
		return collisions;
	}

	for (const auto& enemy : this->m_characters.at(enemyTypeIndex)) {
		const auto heroBounds = this->m_hero->getSprite().getSprite().getGlobalBounds();
		const auto enemyBounds = enemy->getSprite().getSprite().getGlobalBounds();

		if (heroBounds.intersects(enemyBounds)) {
			collisions.push_back(std::make_pair(this->m_hero, enemy.get()));
		}

		// check for collision between rocket and enemy only if there are rockets
		if (map_utils::contains(this->m_characters, rocketTypeIndex)) {
			for (const auto& rocket : this->m_characters.at(rocketTypeIndex)) {
				const auto rocketBounds = rocket->getSprite().getSprite().getGlobalBounds();

				if (rocketBounds.intersects(enemyBounds)) {
					collisions.push_back(std::make_pair(rocket.get(), enemy.get()));
				}
			}
		}
	}

	return collisions;
}

void Game::start() {

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
			std::cout << "thanks for playing";
			m_window.close();
			break;
		}

		m_eventsHandling.handleEvents(m_window);

		sf::Time timeSinceLastFrameDraw = time.restart();
		m_sceneUpdater.updateScene(timeSinceLastFrameDraw);

		m_window.clear(sf::Color::Red);

		m_window.draw(this->getMap().getMapSprite().getSprite());
		for (const auto& [typeIndex, charactersVec] : this->m_characters) {
			for (const auto& character : charactersVec) {
				if (character->isAlive()) {
					m_window.draw(character->getSprite().getSprite());
				}
			}
		}

		m_window.display();

		const auto& charactersCollisions = this->detectCollisions();
		for (const auto& [firstCharacter, secondCharacter] : charactersCollisions) {
			firstCharacter->handleCollision(secondCharacter);
			secondCharacter->handleCollision(firstCharacter);
		}
	}
}