#include <stdexcept>

#include "map_utils.h"
#include "EventsHandling.h"

void EventsHandling::registerEventHandler(sf::Event::EventType eventType, EventCallback handler) {
	if (map_utils::contains(this->keyboard_event_handlers, eventType)) {
		this->keyboard_event_handlers.at(eventType).push_back(handler);
	}
	else {
		this->keyboard_event_handlers.insert({ eventType, std::vector<EventCallback>() });
		this->keyboard_event_handlers.at(eventType).push_back(handler);
	}
}

void EventsHandling::handleEvents(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {

		if (map_utils::contains(this->keyboard_event_handlers, event.type)) {
			const auto& eventCallbacks = this->keyboard_event_handlers.at(event.type);
			for (const auto& callback : eventCallbacks) {
				callback(event.key);
			}
		}

		if (event.key.code == sf::Keyboard::Escape) {
			window.close();
		}
	}
}