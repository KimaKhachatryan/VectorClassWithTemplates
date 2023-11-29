#include <iostream>
#include "vector_class.h"
#include <vector>

int main()
{
	Vector<bool> vec;
//	vec.reserve(20);

	for (size_t i = 0; i < 9; ++i) {
		vec.push_back(true);
	}
	vec.push_back(false);
	vec.push_back(false);
	
	for (size_t i = 0; i < 6; ++i) {
		vec.push_back(true);
	}
/*
	vec.pop_back();
	vec.push_back(true);	

	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();

	vec.resize(5);

	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();

	vec.resize(21, true);

	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();

	vec.clear();

	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();
	
	vec.bit_swap(vec.data(), 9, 10);
	vec.print();
*/
	std::cout << "vec[0]" << vec[0] << std::endl;
}
