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
	void allocator(size_t new_capacity = 2);
	void reallocator(size_t new_capacity = 0);
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

// operator overloading
	T& operator[] (size_t index);
	Vector<T>& operator= (const Vector&);
	Vector<T>& operator= (Vector&&);
	std::ostream& operator<< (std::ostream& obj)
	{
		for (size_t i = 0; i < m_size; ++i) {
			obj << m_ptr[i] << " ";
		}

		return obj;
	}
};

#include "bool_vector.h"
#include "vector_class.hpp"





