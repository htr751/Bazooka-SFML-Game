#include <stdexcept>
#include <utility>

#include <effolkronium/random.hpp>

#include "map_utils.h"
#include "EventsHandling.h"

EventsHandling::CallbackID EventsHandling::registerEventHandler(sf::Event::EventType eventType, EventCallback handler) {
	using Random = effolkronium::random_static;
	
	CallbackID generatedID = 0;
	do {
		generatedID = Random::get<CallbackID>(0, std::numeric_limits<CallbackID>::max());
	} while (this->idToHandlersMap.find(generatedID) != this->idToHandlersMap.end());

	if (map_utils::contains(this->keyboardEventHandlers, eventType)) {
		this->keyboardEventHandlers.at(eventType).insert(std::make_pair(generatedID, handler));
	}
	else {
		this->keyboardEventHandlers.insert({ eventType, std::unordered_map<CallbackID, EventCallback>() });
		this->keyboardEventHandlers.at(eventType).insert(std::make_pair(generatedID, handler));
	}

	this->idToHandlersMap.insert(std::make_pair(generatedID,
		std::ref(this->keyboardEventHandlers.at(eventType))));

	return generatedID;
}

void EventsHandling::handleEvents(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {

		if (map_utils::contains(this->keyboardEventHandlers, event.type)) {
			const auto& eventCallbacks = this->keyboardEventHandlers.at(event.type);
			for (const auto& [id, callback] : eventCallbacks) {
				callback(event.key);
			}
		}

		if (event.key.code == sf::Keyboard::Escape) {
			window.close();
		}
	}
}

void EventsHandling::removeEventHandler(CallbackID id) {
	if (this->idToHandlersMap.find(id) == this->idToHandlersMap.end()) {
		throw std::runtime_error("error - attempt to remove nonexisting callback");
	}

	this->idToHandlersMap.at(id).get().erase(id);
	this->idToHandlersMap.erase(id);
 }

 void EventsHandling::removeAllEventHandlers() {
	 this->keyboardEventHandlers.clear();
	 this->idToHandlersMap.clear();
 }