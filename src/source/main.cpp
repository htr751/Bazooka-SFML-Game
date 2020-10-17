#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	sf::Vector2f viewSize(1024, 768);
	sf::VideoMode viewMode(viewSize.x, viewSize.y);
	sf::RenderWindow window(viewMode, "Bazooka", sf::Style::Default);
	
	Game game{ window };
	while (game.start(2) == Game::GameOverStatus::RestartGame);
	return 0;
}