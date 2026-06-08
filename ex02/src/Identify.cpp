#include "../inc/Identify.hpp"
#include "../inc/A.hpp"
#include "../inc/B.hpp"
#include "../inc/C.hpp"
#include <cstdlib>	// rand, srand
#include <ctime>	// time
#include <iostream>

/**
 * @brief Seed RNG on first call and return a new instance of A, B, C.
 */
Base* generate(void) {
	// Seed once (use time-based seed)
	static bool seeded = false;
	if (!seeded) {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		seeded = true;
	}

	int r = std::rand() % 3;	// 0,1,2
	if (r == 0)
		return new A();
	else if (r == 1)
		return new B();
	else
		return new C();
}

/**
 * @brief Identify actual type using pointer dynamic_cast checks.
 */
void identify(Base* p) {
	// null check
	if (!p) {
		std::cout << "Null pointer" << std::endl;
		return;
	}
	// Try each cast, pointer cast returns nullptr on failure
	if (dynamic_cast<A*>(p) != nullptr) {
		std::cout << "A" << std::endl;
		return;
	}
	if (dynamic_cast<B*>(p) != nullptr) {
		std::cout << "B" << std::endl;
		return;
	}
	if (dynamic_cast<C*>(p) != nullptr) {
		std::cout << "C" << std::endl;
		return;
	}
	// Fallback (shouldn't happen for this task)
	std::cout << "Unknown" << std::endl;
}

/**
 * @brief Identify actual type using reference dynamic_cast and exceptions.
 * Doesn't use any7 pointer inside this function.
 */
void identify(Base& p) {
	// Try to dynamic_cast to reference types
	// dynamic_cast<T&> throws if fails
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	} catch (...) {
		// not A
	}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	} catch (...) {
		// not B
	}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	} catch (...) {
		// not C
	}
	
	// Fallback (shouldn't happen)
	std::cout << "Unknown" << std::endl;
}
