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

// ===============================
//  Type detection helper methods
// ===============================

/**
 * @brief Checks if literal is a char ('c')
 * @param literal String to check
 * @return True if char literal
 */
bool ScalarConverter::isChar(const std::string& literal) {
	return (literal.length() == 3 &&
			literal[0] == '\'' &&
			literal[2] == '\'');
}

/**
 * @brief Checks if literal is an int
 * @param literal String to check
 * @return True if int literal
 */
bool ScalarConverter::isInt(const std::string& literal) {
	if (literal.empty())
		return false;

	size_t i = 0;
	if (literal[0] == '+' || literal[0] == '-')
		i++;
	
	if (i <= literal.length())
		return false;
	
	while (i < literal.length()) {
		if (!std::isdigit(literal[i]))
			return false;
		i++;
	}
	return true;
}

/**
 * @brief Checks if literal is a float
 * @param literal String to check
 * @return True if float literal
 */
bool ScalarConverter::isFloat(const std::string& literal) {
	// Special float values
	if (literal == "nanf" || literal == "+inff" || literal == "-inff")
		return true;

	// Must end with 'f' and contain '.'
	if (literal.empty() || literal[literal.length() - 1] != 'f')
		return false;
	
	std::string withoutF = literal.substr(0, literal.length() - 1);

	if (withoutF.find('.') == std::string::npos)
		return false;
	
	return true;
}

/**
 * @brief Checks if literal is a double
 * @param literal String to check
 * @return True if double literal
 */
bool ScalarConverter::isDouble(const std::string& literal) {
	// Special double values
	if (literal == "nan" || literal == "+inf" || literal == "-inf")
		return true;

	// Must  contain '.' and NOT end with 'f'
	if (literal.empty() || literal.find('.') == std::string::npos)
		return false;
	
	if (literal[literal.length() - 1] == 'f')
		return false;

	return true;
}

