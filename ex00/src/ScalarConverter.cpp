#include "../inc/ScalarConverter.hpp"

// ============================================
//  Orthodox Canonical Form - non-instantiable
// ============================================

/**
 * @brief Default constructor
 */
ScalarConverter::ScalarConverter() {}


/**
 * @brief Copy constructor
 */
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }


/**
 * @brief Assignment operator
 */
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return *this;
}

/**
 * @brief Destructor
 */
ScalarConverter::~ScalarConverter() {}
