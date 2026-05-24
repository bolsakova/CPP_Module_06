#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

#include <cstdint>
#include "Data.hpp"

/**
 * @brief Non-instantiable utility class for pointer serialization.
 */
class Serializer {
	private:
			// Orthodox Canonical Form
			// Private constructors - forbidden for users, to forbid instantiation
			Serializer();
			Serializer(const Serializer& other);
			Serializer& operator=(const Serializer& other);
			~Serializer();

	public:
			// Data pointer converter to uintptr_t
			static uintptr_t	serialize(Data* ptr);
			// uintptr_t converter back to Data pointer
			static Data*		deserialize(uintptr_t raw);
};

#endif
