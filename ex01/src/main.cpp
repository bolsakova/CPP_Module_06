#include "../inc/Serializer.hpp"
#include <iostream>

int main() {
	// Test object with real data members
	Data data;
	data.id = 42;
	data.value = 4.2;
	data.label = "serialization";

	// Original pointer to the object
	Data* original = &data;

	// Convert pointer to integer and back
	uintptr_t raw = Serializer::serialize(original);
	Data* restored = Serializer::deserialize(raw);

	// Print addresses and equality check result
	std::cout << "Original pointer: " << original << std::endl;
	std::cout << "Restored pointer: " << restored << std::endl;
	std::cout << "Pointers equal: "
	<< (original == restored ? "true" : "false") << std::endl;
	
	// Optional data check through restored pointer
	if (restored == original)
	{
		std::cout << "id: " << restored->id << std::endl;
		std::cout << "value: " << restored->value << std::endl;
		std::cout << "label: " << restored->label << std::endl;
	}
	
	return 0;
}
