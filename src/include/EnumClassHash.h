#ifndef ENUM_CLASS_HASH
#define ENUM_CLASS_HASH

#include <type_traits>

template<typename EnumType>
struct EnumHash {
	decltype(auto) operator()(EnumType e) const noexcept {
		return static_cast<std::underlying_type_t<EnumType>>(e);
	}
};

#endif