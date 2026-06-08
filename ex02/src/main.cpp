#include "../inc/Identify.hpp"
#include <iostream>

/**
 * @brief Creates several random objects via generate(), then identifies them
 * using both pointer and reference overloads.
 */
int main() {
	// Create and test a few instances
	for (int i = 0; i < 6; ++i)
	{
		Base* obj = generate();

		// identify by pointer
		std::cout << "identify(Base*): ";
		identify(obj);

		// identify by reference (no pointers allowed inside)
		std::cout << "identify(Base&): ";
		identify(*obj);

		// cleanup
		delete obj;
		std::cout << "----" << std::endl;
	}
	
	return 0;
}
