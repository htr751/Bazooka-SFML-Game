#ifndef EVENTS_HANDLING
#define EVENTS_HANDLING

#include <unordered_map>
#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

namespace event_utils {
	inline bool isKeyEvent(sf::Event::EventType type) noexcept {
		return type == sf::Event::EventType::KeyPressed || type == sf::Event::EventType::KeyReleased;
	}
}

class EventsHandling {
public:
	using EventCallback = std::function<void(sf::Event::KeyEvent)>;

	void registerEventHandler(sf::Event::EventType eventType, EventCallback handler);
	void handleEvents(sf::RenderWindow& window);

private:
	std::unordered_map<sf::Event::EventType, std::vector<EventCallback>> keyboard_event_handlers;
};

#endif