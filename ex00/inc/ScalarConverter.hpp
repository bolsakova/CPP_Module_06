#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <cerrno>

/**
 * Static Non-instantiable Class
 */
class ScalarConverter {
	private:
			// Orthodox Canonical Form
			// Private constructors - class cannot be instantiated
			ScalarConverter();
			ScalarConverter(const ScalarConverter& other);
			ScalarConverter& operator=(const ScalarConverter& other);
			~ScalarConverter();

			// static methods - called without objects
			// Helper methods for type detection
			static bool isChar(const std::string& literal);
			static bool isInt(const std::string& literal);
			static bool isFloat(const std::string& literal);
			static bool isDouble(const std::string& literal);

			// Helper methods for conversion and display
			static void convertFromChar(char c);
			static void convertFromInt(int n);
			static void convertFromFloat(float f);
			static void convertFromDouble(double d);

			// Helper to check if char is displayable
			static bool isDisplayable(char c);
	public:
			// main static method - converts and displays literal
			static void convert(const std::string& literal);
};

#endif
