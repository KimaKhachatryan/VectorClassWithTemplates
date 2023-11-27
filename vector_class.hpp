//default contructor
template <typename T>
Vector<T>::Vector()
{
	this->m_size = 0;
	this->m_capacity = 0;
	this->m_ptr = nullptr;
}

//parameterized contructor
template <typename T>
Vector<T>::Vector(size_t count, T value)
{
	this->m_size = count;
	this->m_capacity = count;
	this->m_ptr = new T[count];
	
	for (size_t i = 0; i < count; ++i) {
		this->m_ptr[i] = value;
	}
}

//Initializer_list constructor
template <typename T>
Vector<T>::Vector(std::initializer_list<T> list)
{
	this->m_size = list.size();
	this->m_capacity = list.size();
	this->m_ptr = new T[m_capacity];
	
	for (size_t i = 0; i < this->m_size; ++i) {
		this->m_ptr[i] = list.begin()[i];
	}
}

//copy contructor
template <typename T>
Vector<T>::Vector(const Vector<T>& obj)
{
	if (this->m_ptr != &obj) {
		this->m_size = obj.m_size;
		this->m_capacity = obj.m_capacity;
		this->m_ptr = new T[obj.m_capacity];
	
		for (size_t i = 0; i < obj.m_size; ++i) {
			this->m_ptr[i] = obj.m_ptr[i];
		}
	}
}

//move contructor
template <typename T>
Vector<T>::Vector(Vector<T>&& obj)
{
	this->m_size = obj.m_size;
	this->m_capacity = obj.m_capacity;
	this->m_ptr = obj.m_ptr;

}

//destructor
template <typename T>
Vector<T>::~Vector()
{
	m_size = 0;
	m_capacity = 0;

	if (this->m_ptr) { 
		delete[] m_ptr;
	}
	m_ptr = nullptr;
}

//allocator that allocates a new space 
template <typename T> 
void Vector<T>::allocator(size_t new_capacity)
{
	this->m_ptr = new T[new_capacity];
	this->m_capacity = new_capacity;
}

//reallocator that allocates a new space and can take a size as an function argument
template <typename T>
void Vector<T>::reallocator(size_t new_capacity)
{
	this->m_capacity += new_capacity;
	
	T* tmp_ptr = new T[this->m_capacity];
	for (size_t i = 0; i < m_size; ++i) {
		tmp_ptr[i] = this->m_ptr[i];
	}
	
	delete[] this->m_ptr;
	this->m_ptr = tmp_ptr;
	tmp_ptr = nullptr;
}

//functions which return information about size and capacity
template <typename T>
size_t Vector<T>::size()
{
	return this->m_size;
}

template <typename T>
size_t Vector<T>::max_size()
{
	return 1073741823;
}

template <typename T>
size_t Vector<T>::capacity()
{
	return this->m_capacity;
}

//function that changes vector size
template <typename T>
void Vector<T>::resize(size_t new_size, T value)
{
	if (this->m_ptr == nullptr) {
		Vector<T>::allocator(new_size);
	} else if (new_size < this->m_size) {
		this->m_size = new_size;
	} else if (new_size > this->m_size) {
		if (new_size > this->m_capacity) {
			Vector<T>::reallocator(new_size);
		} 
	} else if (new_size == this->m_size) {
		return;
	}
	
	if (new_size > this->m_size) {
		for (size_t i = this->m_size; i < new_size; ++i) {
			this->m_ptr[i] = value;
		}
	}

	this->m_size = new_size;
}

//function that reserves a space...
//he function call does not cause a reallocation 
//if new_capacity is not greater than the current vector capacity

template<typename T>
void Vector<T>::reserve(size_t new_capacity)
{
	if (new_capacity > this->m_capacity) {
		if (this->m_ptr == nullptr) {
			Vector<T>::allocator(new_capacity);
		} else { 
			Vector<T>::reallocator(new_capacity);
		}
	} 

}

//returns whether the vector is empty 
template <typename T>
bool Vector<T>::empty()
{
	return this->m_size;
}

//requests the container to reduce its capacity to fit its size.
template <typename T>
void Vector<T>::shrink_to_fit()
{
	if (this->m_capacity > this->m_size) {
		T* tmp_ptr = new T[m_size];

		for (size_t i = 0; i < this->m_size; ++i) {
			tmp_ptr[i] = this->m_ptr[i];
		}

		delete[] m_ptr;
		m_ptr = tmp_ptr;
		tmp_ptr = nullptr;

		this->m_capacity = this->m_size;
	}
}

//functions which return references 
template <typename T>
T& Vector<T>::at(size_t index)
{
	if (index >= this->m_size) {
		std::cout << "Segmantation fault." << std::endl;
		exit(0);
	} 
	 return m_ptr[index];
}

template <typename T>
T& Vector<T>::front()
{
	if (!this->m_ptr) {
		std::cout << "Segmantation fault." << std::endl;
		exit(0);
	} 
	
	return m_ptr[0];	
}

template <typename T>
T& Vector<T>::back()
{
	if (!this->m_ptr) {
		std::cout << "Segmantation fault." << std::endl;
		exit(0);
	} 
	 return this->m_ptr[m_size - 1];
}

//returns a direct pointer to the memory array used internally by the vector to store its owned elements
template <typename T>
T* Vector<T>::data()
{
	return this->m_ptr;
}

//assigns new contents to the vector
//the new contents are count elements, each initialized to a copy of value 
template <typename T>
void Vector<T>::assign(size_t count, T value)
{
	if (this->m_ptr == nullptr) {
		Vector<T>::allocator(count);
	} else if (count > this->m_capacity) {
		Vector<T>::reallocator(count);
	}
	
	for (size_t i = 0; i < count; ++i) {
		this->m_ptr[i] = value;
	}
	
	this->m_size = count;
}

//adds a new element at the end of the vector
template <typename T>
void Vector<T>::push_back(T value)
{
	if (this->m_ptr == nullptr) {
		Vector<T>::allocator();
	} else if (this->m_size + 1 > this->m_capacity) {
		Vector<T>::reallocator(1);
	}
	
	this->m_ptr[m_size] = value;
	this->m_size += 1;
}

//removes the last element in the vector
template <typename T>
void Vector<T>::pop_back()
{
	if (!this->m_size) {
		std::cout << "Segmantation fault." << std::endl;
		exit(0);
	} 
	
	--(this->m_size);	
}

// functions extend the vector by inserting new elements before the element at the specified position
template <typename T>
void Vector<T>::insert(size_t position, T value)
{
	if (position >= this->m_size) {
		if (this->m_size != 0 && position != 0) {
			std::cout << "Segmantation fault." << std::endl;
			exit(0);
		}
	} 
	
	if (this->m_size + 1 > this->m_capacity) {
		Vector<T>::reallocator(1);
	}
	
	for (int i = this->m_size - 1; i >= position; --i) {
		this->m_ptr[i + 1] =  this->m_ptr[i];
	}
	
	this->m_ptr[position] = value;
		
}

template <typename T>
void Vector<T>::insert(size_t position, size_t count, T value)
{
	if (position >= this->m_size) {
		if (this->m_size != 0 && position != 0) {
			std::cout << "Segmantation fault." << std::endl;
			exit(0);
		}
	} 
	
	if (this->m_size + count > this->m_capacity) {
		Vector<T>::reallocator(count);
	}
	
	for (int i = this->m_size + count; i >= position + count; --i) {
		this->m_ptr[i] =  this->m_ptr[i - count];
	}
	
	for (size_t i = position; i < position + count; ++i) {
		this->m_ptr[position] = value;
	}
		
}

//removes from the vector single element (position) 
template <typename T>
void Vector<T>::erase(size_t position)
{
	if (position >= this->m_size) {
		std::cout << "Segmantation fault." << std::endl;
		exit(0);
	} 
	
	for (size_t i = position; i <= this->m_size; ++i) {
		this->m_ptr[i] =  this->m_ptr[i + 1];
	}
	
	this->m_size -= 1;
}

//removes from the vector a range of elements
template <typename T>
void Vector<T>::erase(size_t first, size_t last)
{
	if (first >= last) {
		std::cout << "Invalid input" << std::endl;
		return;
	}
	if (first >= this->m_size || last >= this->m_size) {
		std::cout << "Segmantation fault." << std::endl;
		exit(0);
	} 
	
	size_t count = last - first;

	for (size_t i = first; i <= last; ++i) {
		this->m_ptr[i] =  this->m_ptr[i + count];
	}
	
	this->m_size -= count;
}

//exchanges the content of the container by the content of obj, which is another vector object of the same type 
template <typename T>
void Vector<T>::swap(Vector<T>& obj)
{
	std::swap(this->m_size, obj.m_size);
	std::swap(this->m_capacity, obj.m_capacity);
	std::swap(this->m_ptr, obj.m_ptr);
}

//removes all elements from the vector 
template <typename T>
void Vector<T>::clear()
{
	if (this->m_size) {
		m_size = 0;
	}
}

//operator overloding functions

//subscrip operator
template <typename T>
T& Vector<T>::operator[](size_t index)
{
	if (index >= this->m_size) {
		std::cout << "Segmantation fault." << std::endl;
		exit(0);
	} 
	 return this->m_ptr[index];
}
//assignment operator
template <typename T>
Vector<T>& Vector<T>::operator= (const Vector& obj)
{
	if (this->m_ptr != &obj) {
		if (this->m_ptr) {
			delete[] this->m_ptr;
		}

		this->m_size = obj.m_size;
		this->m_capacity = obj.m_capacity;
		this->m_ptr = new T[obj.m_capacity];
	
		for (size_t i = 0; i < obj.m_size; ++i) {
			this->m_ptr[i] = obj.m_ptr[i];
		}
	}
}

//move assignment operator
template <typename T>
Vector<T>& Vector<T>::operator= (Vector&& obj)
{
	this->m_size = obj.m_size;
	this->m_capacity = obj.m_capacity;
	this->m_ptr = obj.m_ptr;

	obj.m_size = 0;
	obj.m_capacity = 0;
	obj.m_ptr = nullptr;
}

//operator << 
template<typename T>
std::ostream& operator<< (std::ostream& os, Vector<T>& obj)
{
	return obj.operator<<(os);
}





