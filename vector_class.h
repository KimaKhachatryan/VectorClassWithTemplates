template <typename T>
class Vector {
private:
	size_t m_size;
	T* m_ptr;
	size_t m_capacity;
public:
// constructors 
	Vector();
	Vector(size_t count, T value);
	Vector(std::initializer_list<T> list);
	Vector(const Vector<T>& obj);
	Vector(Vector<T>&& obj);
	
// destructor
	~Vector();
	
// member functions prototypes
	void allocator(size_t new_capacity = 1);
	void reallocator(size_t new_capacity = 2);
	size_t size();
	size_t max_size();
	size_t capacity();
	void resize(size_t new_size, T value = 0);
	void reserve(size_t new_capacity);
	bool empty();
	void shrink_to_fit();
	T& at(size_t index);
	T& front();
	T& back();
	T* data();
	void assign(size_t count, T value);
	void push_back(T value);
	void pop_back();
	void insert(size_t position, T value);
	void insert(size_t position, size_t count, T value);
	void erase(size_t position);
	void erase(size_t first, size_t last);
	void swap(Vector<T>& obj);
	void clear();
//	void emplace(T value);
//	void emplace_back(T value);
};

/*
template<>
class vector<bool> {
	
};
*/

#include "vector_class.hpp"





