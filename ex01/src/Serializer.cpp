#include "../inc/Serializer.hpp"
#include "../inc/Data.hpp"

// ============================================
//  Orthodox Canonical Form - non-instantiable
// ============================================

/**
 * @brief Default constructor
 */
Serializer::Serializer() {}


/**
 * @brief Copy constructor
 */
Serializer::Serializer(const Serializer& other) { (void)other; }


/**
 * @brief Assignment operator
 */
Serializer& Serializer::operator=(const Serializer& other) {
	(void)other;
	return *this;
}

/**
 * @brief Destructor
 */
Serializer::~Serializer() {}

// ============
//  Converters
// ============

/**
 * @brief Reinterprets pointer value an unsigned integer.
 */
uintptr_t Serializer::serialize(Data* ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

/**
 * @brief Reinterprets unsigned integer value as Data pointer.
 */
Data* Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data*>(raw);
}

