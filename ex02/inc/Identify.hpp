#ifndef IDENTIFY_HPP
# define IDENTIFY_HPP

#include "Base.hpp"
#include <cstdint>

/**
 * @brief Randomly instantiate A, B or C and return as Base*.
 */
Base* generate(void);

/** 
 * @brief Identify actual type from Base pointer and print "A", "B" or "C".
 */
void identify(Base* p);

/**
 * @brief Identify actual type from Base reference and print "A", "B" or "C".
 * 
 * Note: using a pointer inside this function is forbidden by the task,
 * so this implementation uses reference dynamic_cast with try/catch.
 */
void identify(Base& p);


#endif
