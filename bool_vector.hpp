//default contructor
Vector<bool>::Vector()
{
	this->m_size = 0;
	this->m_capacity = 0;
	this->m_ptr = nullptr;
}

//parameterized contructor
//Initializer_list constructor
//copy contructor
//move contructor


//destructor
Vector<bool>::~Vector()
{
	m_size = 0;
	m_capacity = 0;
	delete[] m_ptr;
	m_ptr = nullptr;
}

//allocator that allocates a new space 
void Vector<bool>::allocator()
{
	this->m_ptr = new unsigned short[1];
	this->m_capacity = BIT_COUNT;
}

//reallocator that allocates a new space and can take a size as an function argument
void Vector<bool>::reallocator(size_t new_capacity)
{
	this->m_capacity += new_capacity * BIT_COUNT;
	
	unsigned short* tmp_ptr = new unsigned short[this->m_capacity / BIT_COUNT];
	for (size_t i = 0; i < this->m_capacity / BIT_COUNT - 1; ++i) {
		tmp_ptr[i] = this->m_ptr[i];
	}
	
	delete[] this->m_ptr;
	this->m_ptr = tmp_ptr;
	tmp_ptr = nullptr;
}

//functions which return information about size and capacity

size_t Vector<bool>::size()
{
	return this->m_size;
}

size_t Vector<bool>::max_size()
{
	return 1073741823;
}

size_t Vector<bool>::capacity()
{
	return this->m_capacity;
}

//function that changes vector size

//function that reserves a space...
//he function call does not cause a reallocation 
//if new_capacity is not greater than the current vector capacity

//returns whether the vector is empty 
bool Vector<bool>::empty()
{
	return this->m_size;
}

//requests the container to reduce its capacity to fit its size

//functions which return references 

//returns a direct pointer to the memory array used internally by the vector to store its owned elements

//assigns new contents to the vector
//the new contents are count elements, each initialized to a copy of value 

//adds a new element at the end of the vector
void Vector<bool>::push_back(bool value)
{
	if (this->m_ptr == nullptr) {
		Vector<bool>::allocator();
	} else if (this->m_size + 1 > this->m_capacity) {
		Vector<bool>::reallocator(1);
	}

	int index = this->m_capacity / (sizeof(unsigned short) * 8) - 1;
	this->m_ptr[index] ^= value;
	this->m_ptr[index] <<= 1; 
	++this->m_size;
}

//removes the last element in the vector

// functions extend the vector by inserting new elements before the element at the specified position

//removes from the vector single element (position) 

//removes from the vector a range of elements

//exchanges the content of the container by the content of obj, which is another vector object of the same type 

//removes all elements from the vector 












