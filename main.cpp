#include <iostream>
#include "vector_class.h"
#include <vector>

int main()
{
	Vector<bool> vec;
	vec.reserve(20);

	for (size_t i = 0; i < 9; ++i) {
		vec.push_back(true);
	}
	vec.push_back(false);
	vec.push_back(false);
	
	for (size_t i = 0; i < 16; ++i) {
		vec.push_back(true);
	}
		vec.push_back(0);
		vec.push_back(true);
		vec.push_back(true);
	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();

	vec.resize(5);
/*
	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();

	vec.resize(21, true);

	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();
*/
	vec.shrink_to_fit();
	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();

}
