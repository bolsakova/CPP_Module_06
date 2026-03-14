#include "../inc/ScalarConverter.hpp"

static void runOne(const std::string& literal) {
	std::cout << "Input: " << literal << std::endl;
	ScalarConverter::convert(literal);
	std::cout << "----------------------------------------" << std::endl;
}

/**
 * @brief Runs a broad test suite for all supported literal kinds
 */
static void runAllTests() {
	const std::string tests[] = {
		// char
		"'a'",
		"'*'",
		"'0'",
		
		// int
		"0",
		"-42",
		"42",
		"127",
		"128",
		"2147483647",
		"-2147483648",

		// float
		"0.0f",
		"-4.2f",
		"4.2f",
		"42.0f",
		"nanf",
		"+inff",
		"-inff",

		// double
		"0.0",
		"-4.2",
		"4.2",
		"42.0",
		"nan",
		"+inf",
		"-inf",

		// invalid, edge cases
		"",
		"abc"
		"42ff"
		"--1"
		"+-1"
		"."
		".f"
		"1."
		"1.f"
		"9999999999999999999999999999999999999"
		"-9999999999999999999999999999999999999"
	};

	const std::size_t count = sizeof(tests) / sizeof(tests[0]);
	for (std::size_t i = 0; i < count; ++i)
		runOne(tests[i]);
}

int main(int ac, char *av[]) {
	if (ac == 2)
	{
		const std::string arg = av[1];
		if (arg == "--test")
		{
			runAllTests();
			return 0;
		}
		ScalarConverter::convert(arg);
		return 0;
	}

	std::cerr << "Usage: ./convert <literal>" << std::endl;
	std::cerr << "   or: ./convert --test" << std::endl;
	return 1;
}
