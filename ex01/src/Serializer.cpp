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
