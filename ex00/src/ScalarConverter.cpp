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
	
	if (i >= literal.length())
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

/**
 * @brief Checks if char is displayable (ASCII 32-126)
 * @param c Character to check
 * @return True if displayable
 */
bool ScalarConverter::isDisplayable(char c) {
	return (c >= 32 && c <= 126);
}

// ====================
//  Conversion methods
// ====================

/**
 * @brief Converts from char and displays all types
 * @param c Character value
 */
void ScalarConverter::convertFromChar(char c) {
	// char
	if (isDisplayable(c))
		std::cout << "char: '" << c << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
		
	// int
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	
	// float
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
	
	// double
	std::cout << "double: " << static_cast<double>(c) << std::endl;
}

/**
 * @brief Converts from int and displays all types
 * @param n Integer value
 */
void ScalarConverter::convertFromInt(int n) {
	// char
	if (n < 0 || n > 127)
		std::cout << "char: impossible" << std::endl;
	else if (isDisplayable(static_cast<char>(n)))
		std::cout << "char: '" << static_cast<char>(n) << "'" << std::endl;
	else	
		std::cout << "char: Non displayable" << std::endl;
		
	// int
	std::cout << "int: " << n << std::endl;
	
	// float
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << static_cast<float>(n) << "f" << std::endl;
	
	// double
	std::cout << "double: " << static_cast<double>(n) << std::endl;
}

/**
 * @brief Converts from float and displays all types
 * @param f Float value
 */
void ScalarConverter::convertFromFloat(float f) {
	// char
	if (std::isnan(f) || std::isinf(f))
		std::cout << "char: impossible" << std::endl;
	else if (f < 0 || f > 127)
		std::cout << "char: impossible" << std::endl;
	else if (isDisplayable(static_cast<char>(f)))
		std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
	else	
		std::cout << "char: Non displayable" << std::endl;
		
	// int
	if (std::isnan(f) || std::isinf(f))
		std::cout << "int: impossible" << std::endl;
	else if (f > INT_MAX || f < INT_MIN)
		std::cout << "int: impossible" << std::endl;
	else	
		std::cout << "int: " << static_cast<int>(f) << std::endl;
	
	// float
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << f << "f" << std::endl;
	
	// double
	std::cout << "double: " << static_cast<double>(f) << std::endl;
}

/**
 * @brief Converts from double and displays all types
 * @param d Double value
 */
void ScalarConverter::convertFromDouble(double d) {
	// char
	if (std::isnan(d) || std::isinf(d))
		std::cout << "char: impossible" << std::endl;
	else if (d < 0 || d > 127)
		std::cout << "char: impossible" << std::endl;
	else if (isDisplayable(static_cast<char>(d)))
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
	else	
		std::cout << "char: Non displayable" << std::endl;
		
	// int
	if (std::isnan(d) || std::isinf(d))
		std::cout << "int: impossible" << std::endl;
	else if (d > INT_MAX || d < INT_MIN)
		std::cout << "int: impossible" << std::endl;
	else	
		std::cout << "int: " << static_cast<int>(d) << std::endl;
	
	// float
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << static_cast<int>(d) << "f" << std::endl;
	
	// double
	std::cout << "double: " << d << std::endl;
}
