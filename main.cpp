#include <iostream>
#include "vector_class.h"

int main()
{
	Vector<bool> vec;
	for (size_t i = 0; i < 9; ++i) {
		vec.push_back(true);
	}
	vec.push_back(false);
	vec.push_back(false);
	
	for (size_t i = 0; i < 4; ++i) {
		vec.push_back(true);
	}
	
	vec.pop_back();
	vec.push_back(true);	

	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();

	vec.resize(5);

	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();

	vec.resize(19, true);

	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();

	vec.clear();

	std::cout << vec.capacity() << " " << vec.size() << std::endl;
	vec.print();

}
