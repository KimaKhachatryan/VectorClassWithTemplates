template<> 
class Vector<bool> {
private:
	unsigned short* m_ptr;
	unsigned short m_shifter;
	unsigned short m_cleaner;
	size_t m_size;
	size_t m_capacity;
	size_t m_false_capacity;
	size_t m_index;
	enum {
		BIT_COUNT = sizeof(unsigned short) * 8
	};

public:
//constructors
	Vector();
	Vector(size_t count, bool value);
	Vector(std::initializer_list<bool> list);
	Vector(const Vector<bool>& obj);
	Vector(Vector<bool>&& obj);

//destructor
	~Vector();

//class reference fot facking reference returning functions
class Reference {
private:
	unsigned short* r_ptr;
	size_t r_index;
	bool r_value;

public:
//constructors
	Reference(unsigned short* m_ptr, size_t m_index);
	
//helper functon
	void flip();

//operator overloading functions
	void operator=(const Reference& obj);
	void operator=(bool value);
	operator bool();
	
};
	
// member functions prototypes
	void allocator(size_t new_capacity = 1);
	void reallocator(size_t new_capacity = 1);
	size_t size();
	size_t max_size();
	size_t capacity();
	void resize(size_t new_size, bool value = 0);
	void reserve(size_t new_capacity);
	bool empty();
	void shrink_to_fit();
	Reference at(size_t position);
	Reference front();
	Reference back();
	short unsigned int* data();
//	void assign(size_t count, bool value);
	void push_back(bool value);
	void pop_back();
	void insert(size_t position, bool value);
//	void insert(size_t position, size_t count, bool value);
//	void erase(size_t position);
//	void erase(size_t first, size_t last);
	void swap(Vector<bool>& obj);
	void bit_swap(unsigned short* ptr, unsigned short i, unsigned short j);
	void clear();

//helper functions
//
//print for my tests
	void print();
//shift function for doing one shift to right 
	void shift_to_right(short unsigned int* ptr);
//clean_bit function which reser current bit
	void clear_bit(short unsigned int* ptr, size_t position = 0);
//fill function for setting bits (given count)
	void fill(size_t count, bool value);


//operator overloading functions
	Reference operator[](size_t position);
};

#include "bool_vector.hpp"

