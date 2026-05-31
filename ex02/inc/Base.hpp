#ifndef BASE_HPP
# define BASE_HPP

/**
 * @brief Base class with virtual destructor only.
 * Used as polymorphic root for A, B, C.
 */
class Base {
	public:
			// Virtual destructor to enable RTTI via dynamic_cast
			virtual ~Base() {}
};

#endif
