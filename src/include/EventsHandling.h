#ifndef EVENTS_HANDLING
#define EVENTS_HANDLING

#include <unordered_map>
#include <functional>

#include <SFML/Graphics.hpp>

namespace event_utils {
	inline bool isKeyEvent(sf::Event::EventType type) noexcept {
		return type == sf::Event::EventType::KeyPressed || type == sf::Event::EventType::KeyReleased;
	}
}

class EventsHandling {
public:
	using EventCallback = std::function<void(sf::Event::KeyEvent)>;
	using CallbackID = unsigned long long;

	//this method register an event handler of type eventType and returns its ID for future referencing
	CallbackID registerEventHandler(sf::Event::EventType eventType, EventCallback handler);
	void handleEvents(sf::RenderWindow& window);

	void removeEventHandler(CallbackID id);

private:
	std::unordered_map<sf::Event::EventType, 
		std::unordered_map<CallbackID, EventCallback>> keyboardEventHandlers;

	std::unordered_map<CallbackID, 
		std::reference_wrapper<std::unordered_map<CallbackID, EventCallback>>> idToHandlersMap;
};

#endif