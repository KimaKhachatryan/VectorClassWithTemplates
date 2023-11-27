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
//	Vector(size_t count, T value);
//	Vector(std::initializer_list<T> list);
//	Vector(const Vector<T>& obj);
//	Vector(Vector<T>&& obj);

//destructor
	~Vector();
	
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
//	unsigned short& at(size_t index);
//	unsigned short& front();
//	unsigned short& back();
//	unsigned short* data();
//	void assign(size_t count, bool value);
	void push_back(bool value);
	void pop_back();
//	void insert(size_t position, bool value);
//	void insert(size_t position, size_t count, bool value);
//	void erase(size_t position);
//	void erase(size_t first, size_t last);
//	void swap(Vector<bool>& obj);
	void clear();
//	void emplace(bool value);
//	void emplace_back(bool value);
	void print();
};

#include "bool_vector.hpp"

