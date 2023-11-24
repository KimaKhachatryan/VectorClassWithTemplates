#include <iostream>
#include "vector_class.h"

int main()
{
	Vector<bool> vec;
	for (size_t i = 0; i < 18; ++i) {
		vec.push_back(true);
	}
//	vec.push_back(false);
	std::cout << vec.capacity() << " " << vec.size() << std::endl;

}
