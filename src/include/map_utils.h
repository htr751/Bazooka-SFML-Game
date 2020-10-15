#ifndef MAP_UTILS
#define MAP_UTILS

#include <unordered_map>
#include <stdexcept>

namespace map_utils {
	template<typename Key, typename Value>
	bool contains(const std::unordered_map<Key, Value>& map, const Key& key) noexcept {
		try {
			map.at(key);
			return true;
		}
		catch (const std::out_of_range& err) {
			return false;
		}
	}
}
#endif