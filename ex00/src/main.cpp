#include "../inc/ScalarConverter.hpp"

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
