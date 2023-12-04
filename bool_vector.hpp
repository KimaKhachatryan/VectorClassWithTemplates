//default contructor
Vector<bool>::Vector()
{
	this->m_size = 0;
	this->m_capacity = 0;
	this->m_false_capacity = 0;
	this->m_cleaner = 0;
	this->m_index = 0;
	this->m_shifter = (1 << (BIT_COUNT - 1));
	this->m_ptr = nullptr;
}

//parametrized constructor
Vector<bool>::Vector(size_t count, bool value)
{
	this->m_size = count;
	this->m_capacity = (count / BIT_COUNT + 1) * BIT_COUNT;
	this->m_false_capacity = this->m_capacity;
	this->m_cleaner = 0;
	this->m_index = this->m_size / BIT_COUNT;
	this->m_shifter = 1 << (BIT_COUNT - 1 - this->m_size % BIT_COUNT);
	this->m_ptr = new short unsigned int[this->m_index + 1];

	if (value) {
		for (size_t i = 0; i < this->m_index; ++i) {
			this->m_ptr[i] -= 1;
		}

		if (this->m_size % BIT_COUNT) {
			for (short unsigned int setter = 1 << (BIT_COUNT - 1); setter != this->m_shifter; shift_to_right(&setter)) {
				this->m_ptr[this->m_index] ^= setter;
			}
		}
	}
}

//initializer list constructor
Vector<bool>::Vector(std::initializer_list<bool> list)
{
	this->m_size = list.size();
	this->m_capacity = (m_size / BIT_COUNT + 1) * BIT_COUNT;
	this->m_false_capacity = this->m_capacity;
	this->m_cleaner = 0;
	this->m_index = this->m_size / BIT_COUNT;
	this->m_shifter = 1 << (BIT_COUNT - 1 - this->m_size % BIT_COUNT);
	this->m_ptr = new short unsigned int[this->m_index + 1];

	for (size_t i = 0; i <= this->m_index; ++i) {
		short unsigned int setter = 1 << (BIT_COUNT - 1); 
		for (size_t j = 0, k = i * BIT_COUNT + j; j < BIT_COUNT; ++j, ++k) {
			if (list.begin()[k]) {
				this->m_ptr[i] ^= setter;
			}
			shift_to_right(&setter);
		}
	}
}

//parametrized constructor for Reference class
Vector<bool>::Reference::Reference(unsigned short* m_ptr, size_t position):
	r_ptr(m_ptr),
	r_index(position) {
		r_value = m_ptr[position / BIT_COUNT] & (1 << BIT_COUNT - 1 - position % BIT_COUNT); 
	}

//copy contructor
Vector<bool>::Vector(const Vector<bool>& obj)
{
	if (this->m_ptr != obj.m_ptr) {
		this->m_size = obj.m_size;
		this->m_capacity = obj.m_capacity;
		this->m_false_capacity = obj.m_false_capacity;
		this->m_cleaner = 0;
		this->m_index = obj.m_index;
		this->m_shifter = obj.m_shifter;
		this->m_ptr = nullptr;
		if (obj.m_ptr) {
			m_ptr = new short unsigned int[this->m_capacity / BIT_COUNT];
		}

		for (size_t i = 0; i < this->m_capacity / BIT_COUNT; ++i) {
			this->m_ptr[i] = obj.m_ptr[i];
		}
	}
}

//move contructor
Vector<bool>::Vector(Vector<bool>&& obj)
{
	if (this->m_ptr != obj.m_ptr) {
		this->m_size = obj.m_size;
		this->m_capacity = obj.m_capacity;
		this->m_false_capacity = obj.m_false_capacity;
		this->m_cleaner = 0;
		this->m_index = obj.m_index;
		this->m_shifter = obj.m_shifter;
		this->m_ptr = obj.m_ptr;
		obj.m_ptr = nullptr;
	}
}
//destructor
Vector<bool>::~Vector()
{
	this->m_size = 0;
	this->m_capacity = 0;
	this->m_false_capacity = 0;
	this->m_cleaner = 0;
	this->m_index = 0;
	this->m_shifter = (1 << (BIT_COUNT - 1));
	delete[] this->m_ptr;
	this->m_ptr = nullptr;
}

//allocator that allocates a new space 
void Vector<bool>::allocator(size_t new_capacity)
{
	this->m_capacity += new_capacity * BIT_COUNT;
	this->m_ptr = new unsigned short[this->m_capacity];
	this->m_false_capacity = this->m_capacity;
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
	return this->m_size > this->m_false_capacity ? this->m_capacity : this->m_false_capacity;
}

//function that changes vector size
void Vector<bool>::resize(size_t new_size, bool value)
{
	if (new_size == this->m_size) {
		return;
	} else if (this->m_ptr == nullptr) {
		this->allocator(new_size / BIT_COUNT + 1);
	} else if (new_size == 0) {
		this->clear();
	}
	
	if (new_size > this->m_size) {
		if (new_size > this->m_capacity) {
			if (new_size % BIT_COUNT) {
				this->reallocator((new_size - this->m_capacity) / BIT_COUNT + 1);
			} else {
				this->reallocator((new_size - this->m_capacity) / BIT_COUNT);
			}
		}
		if (value) {
			if (this->m_shifter != 1 << (BIT_COUNT - 1)) {
				while (this->m_size != new_size) {
					if (this->m_shifter == 1 << (BIT_COUNT - 1)) {
						break;
					}

					this->push_back(value);
				}
			}

			if (this->m_size != new_size) {	
				for (this->m_index = this->m_size / BIT_COUNT; this->m_index < new_size / BIT_COUNT; ++this->m_index) {
					this->m_ptr[this->m_index] -= 1;
				}

				this->m_size =  this->m_index * BIT_COUNT;

				if (this->m_size != new_size) {
					for (size_t i = 0; i < new_size % BIT_COUNT; ++i) {
						this->push_back(value);
					}
				}
			}
		} else {
			this->m_shifter = 1 << BIT_COUNT - 1 - (new_size % BIT_COUNT);
		}

		this->m_size = new_size;
	} else if (new_size < this->m_size) {
		this->m_index = this->m_size / BIT_COUNT;
		
		for (size_t i = this->m_index; i > new_size / BIT_COUNT; --i) {
			if (this->m_size % BIT_COUNT == 0) {
				--this->m_index;
				continue;
			}
			this->m_ptr[i] = 0;
			--this->m_index;
		}
		
		this->m_size = (this->m_index + 1) * BIT_COUNT;
		if (this->m_size != new_size) {
			for (size_t i = BIT_COUNT - 1; i >= new_size % BIT_COUNT; --i) {
				this->clear_bit(&m_ptr[new_size / BIT_COUNT], i);
			}

			this->m_shifter = 1 << (BIT_COUNT - 1 - (new_size % BIT_COUNT));
		}
	}
	
	this->m_size = new_size;
}

//function that reserves a space...
//the function call does not cause a reallocation 
//if new_capacity is not greater than the current vector capacity
void Vector<bool>::reserve(size_t new_capacity)
{
	if (new_capacity > this->m_capacity) {
		if (this->m_ptr == nullptr) {
			if (new_capacity % BIT_COUNT) {
				this->allocator(new_capacity / BIT_COUNT + 1);
			} else {
				this->allocator(new_capacity / BIT_COUNT);
			}
		} else { 
			if (new_capacity % BIT_COUNT) {
				this->reallocator(this->m_capacity / BIT_COUNT - (new_capacity / this->m_capacity + 1));
			} else {
				this->reallocator(this->m_capacity / BIT_COUNT -  new_capacity / this->m_capacity);
			}
		}
	} 
	
	this->m_false_capacity = new_capacity;
}

//returns whether the vector is empty 
bool Vector<bool>::empty()
{
	return this->m_size;
}

//requests the container to reduce its capacity to fit its size
void Vector<bool>::shrink_to_fit()
{
	if (this->m_capacity > this->m_size) {
		size_t deleted_count = this->m_capacity - (this->m_size / BIT_COUNT + 1) * BIT_COUNT;
		
		if (deleted_count) {
			this->m_capacity -= deleted_count;
			unsigned short* tmp_ptr = new unsigned short[this->m_capacity / BIT_COUNT];
			
			for (size_t i = 0; i < this->m_capacity / BIT_COUNT; ++i) {
				tmp_ptr[i] = this->m_ptr[i];
			}
			
			delete[] this->m_ptr;
			this->m_ptr = tmp_ptr;
			tmp_ptr = nullptr;
			
			this->m_false_capacity = this->m_size;
		}
	}
}

//functions which return references 
//
//function which return fake reference to given position
Vector<bool>::Reference Vector<bool>::at(size_t position)
{
	if (position >= this->m_size) {
		std::cout << "Segmentation fault" << std::endl;
	}

	return Vector<bool>::Reference(m_ptr, position);
}

//function which return fake reference to first element
Vector<bool>::Reference Vector<bool>::front()
{
	if (!m_size) {
		std::cout << "Segmentation fault" << std::endl;
	}
	
	return Vector<bool>::Reference(m_ptr, 0);
}	

//function which return fake reference to last selement
Vector<bool>::Reference Vector<bool>::back()
{
	if (!m_size) {
		std::cout << "Segmentation fault" << std::endl;
	}
	
	return Vector<bool>::Reference(m_ptr, m_size - 1);
}
//returns a direct pointer to the memory array used internally by the vector to store its owned elements
unsigned short* Vector<bool>::data()
{
	return this->m_ptr;
}

//assigns new contents to the vector
//the new contents are count elements, each initialized to a copy of value 

//adds a new element at the end of the vector
void Vector<bool>::push_back(bool value)
{
	if (this->m_ptr == nullptr) {
		this->allocator();
	} else if (this->m_size + 1 > this->m_capacity) {
		this->reallocator(1);
	}

	this->m_index = this->m_size / BIT_COUNT;
	
	if (value) {
		this->m_ptr[m_index] ^= m_shifter;
	}
	
	this->shift_to_right(&m_shifter);	
	if (!this->m_shifter) {
		this->m_shifter = (1 << (BIT_COUNT - 1));
	}
	
	++this->m_size;
}

//removes the last element in the vector
void Vector<bool>::pop_back()
{
	if (!this->m_size) {
		std::cout << "Segmantation fault." << std::endl;
		exit(0);
	} 
	
	this->m_index = this->m_size / BIT_COUNT;
	size_t BIT = this->m_size % BIT_COUNT - 1;
	this->clear_bit(&m_ptr[m_index], BIT); 
	
	--this->m_size;	
}

// functions extend the vector by inserting new elements before the element at the specified position
void Vector<bool>::insert(size_t position, bool value)
{

	if (position >= this->m_size) {
		if (position == 0 && this->m_size == 0) {
			if (this->m_ptr == nullptr) {
				this->allocator();
			}

			this->push_back(value);
			return;
		} else {
			std::cout << "Segmantation fault." << std::endl;
			exit(0);
		}
	} 
	
	if (m_size + 1 > m_capacity) {
		reallocator(1);
	}
	
	this->m_index = this->m_size / BIT_COUNT;
	size_t pos_index = position / BIT_COUNT;
	bool LSB = false;

	for (size_t i = 0; i < this->m_index - pos_index; ++i) {
		this->shift_to_right(&m_ptr[this->m_index - i]);
		
		LSB = bool(this->m_ptr[this->m_index - 1 - i] & 1);
		if(LSB) {
			this->m_ptr[this->m_index] ^= 1 << (BIT_COUNT - 1);
		} 
	}
	
	this->clear_bit(&this->m_ptr[pos_index], BIT_COUNT - 1);	
	for (int i = BIT_COUNT - 1; i >= position % BIT_COUNT; --i) {
		bit_swap(&m_ptr[pos_index], i, i - 1);
	}

	if(value) {
		this->m_ptr[pos_index] ^= 1 << (BIT_COUNT - 1 - position % BIT_COUNT);
	}
	
	++this->m_size;
	this->shift_to_right(&m_shifter);
}

//removes from the vector single element (position) 

//removes from the vector a range of elements

//exchanges the content of the container by the content of obj, which is another vector object of the same type 
void Vector<bool>::swap(Vector<bool>& obj) 
{
	std::swap(this->m_size, obj.m_size);
	std::swap(this->m_capacity, obj.m_capacity);
	std::swap(this->m_false_capacity, obj.m_false_capacity);
	std::swap(this->m_index, obj.m_index);
	std::swap(this->m_shifter, obj.m_shifter);
	std::swap(this->m_cleaner, obj.m_cleaner);
	std::swap(this->m_ptr, obj.m_ptr);

}

//exchanges bits at positions i and j
void Vector<bool>::bit_swap(unsigned short* ptr, unsigned short i, unsigned short j)
{
	i = BIT_COUNT - 1 - i;
	j = BIT_COUNT - 1 - j;

	bool i_bit = bool(*ptr & (1 << i));
	bool j_bit = bool(*ptr & (1 << j));
	
	if (i_bit != j_bit) {
		*ptr ^= (1 << i);
		*ptr ^= (1 << j);
	}
}

//removes all elements from the vector 
void Vector<bool>::clear()
{
	if (this->m_ptr) {
		this->m_index = this->m_size / BIT_COUNT;
		
		for (int i = this->m_index; i >= 0; --i) {
			this->m_ptr[i] = 0;
		}
		
		this->m_size = 0;
		this->m_shifter = 1 << (BIT_COUNT - 1);
	}
}

//print function for my tests
void Vector<bool>::print()
{	
	unsigned short printer = 1 << (BIT_COUNT - 1);
	size_t i = 0;
	for (; this->m_size % BIT_COUNT ? i < this->m_size / BIT_COUNT : i < this->m_capacity / BIT_COUNT + 1; ++i) {
		printer = 1 << (BIT_COUNT - 1);
		
		for (size_t j = BIT_COUNT; j > 0; --j) {
			std::cout << bool(this->m_ptr[i] & printer) << " ";
			this->shift_to_right(&printer);
 		}
 		std::cout << " ";
 	}
 		printer = 1 << (BIT_COUNT - 1);

		if(printer != this->m_shifter) {
 			for (unsigned short j = this->m_shifter << 1; j > 0; j <<= 1) {
 				std::cout << bool(this->m_ptr[i] & printer) << " ";
				this->shift_to_right(&printer);
			}
		}
	std::cout << std::endl;
}
//shifter function for doing one shift to right and guarantees that MSB is 0
void Vector<bool>::shift_to_right(unsigned short int* ptr)
{
	*ptr >>= 1;
	short unsigned int MSB = 1 << (BIT_COUNT - 1);
	-- this->m_cleaner;
	this->m_cleaner ^= MSB;
	*ptr &= this->m_cleaner;
	this->m_cleaner = 0;
}

//clean_bit function which reset current bit
void Vector<bool>::clear_bit(unsigned short int* ptr, size_t position)
{	
	short unsigned int BIT = 1 << (BIT_COUNT - 1 - position);
	--this->m_cleaner;
	this->m_cleaner ^= BIT;
	*ptr &= this->m_cleaner;
	this->m_cleaner = 0;
}

//flip funchtion for assignment operator
void Vector<bool>::Reference::flip()
{
	r_ptr[r_index / BIT_COUNT] ^= 1 << (BIT_COUNT - (r_index % BIT_COUNT) - 1);
}

//fill function for setting given bits
void Vector<bool>::fill(size_t count, bool value)
{
	for (size_t i = 0; i < count; ++i) {
		this->push_back(value);	
	}
}

//operator overloading functions
//
//subscript operator
Vector<bool>::Reference Vector<bool>::operator[](size_t position)
{
	return Vector<bool>::Reference(m_ptr, position);
}

//bool cast operator ()
Vector<bool>::Reference::operator bool()
{
	return r_value;
}

//bool assgnment operator
void Vector<bool>::Reference::operator=(const Reference& obj)
{
	if (this->r_value != obj.r_value) {
		return flip();
	}
}

void Vector<bool>::Reference::operator=(const bool value)
{
	if (this->r_value != value) {
		return flip();
	}
}






