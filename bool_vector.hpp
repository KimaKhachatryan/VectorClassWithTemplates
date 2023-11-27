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

//parameterized contructor
//Initializer_list constructor
//copy contructor
//move contructor


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
		std::cout << "Segmentation fault" << std::endl;
		exit(0);
	} else if (new_size == 0) {
		Vector<bool>::clear();
	}
	
	if (new_size > this->m_size) {
		if (new_size > this->m_capacity) {
			if ((this->m_capacity - this->m_size) % BIT_COUNT != 0) {
				this->m_index = this->m_size / BIT_COUNT;
				
				if (value) {
					for(size_t i = (this->m_capacity - this->m_size) % BIT_COUNT; i > 0; --i) {
						Vector<bool>::push_back(true);
					}
				}
				
				Vector<bool>::reallocator((new_size - this->m_capacity) / BIT_COUNT + 1);
				
				if (value) {
					if (this->m_capacity % new_size) {
						for (size_t i = this->m_index + 1; i < this->m_capacity / BIT_COUNT - 1; ++i) {
							this->m_ptr[i] -= 1;
							this->m_index += 1;
						}
						
						this->m_shifter = (1 << (BIT_COUNT - 1));
						for(size_t i = BIT_COUNT - (this->m_capacity - new_size) % BIT_COUNT; i > 0; --i) {
							Vector<bool>::push_back(true);
						}
					} else {
						for (size_t i = this->m_index + 1; i < this->m_capacity / BIT_COUNT - 1; ++i) {
							this->m_ptr[i] -= 1;
							this->m_index += 1;
						}
						
						this->m_shifter = (1 << (BIT_COUNT - 1));
					}
				}
				
			} else {
				this->m_index = this->m_size / BIT_COUNT;
				
				Vector<bool>::reallocator((new_size - this->m_capacity) / BIT_COUNT + 1);
				
				if (value) {
					if (this->m_capacity % new_size) {
						for (size_t i = this->m_index + 1; i < this->m_capacity / BIT_COUNT - 1; ++i) {
							this->m_ptr[i] -= 1;
							this->m_index += 1;
						}
						
						this->m_shifter = (1 << (BIT_COUNT - 1));
						for(size_t i = BIT_COUNT - (this->m_capacity - new_size) % BIT_COUNT; i > 0; --i) {
							Vector<bool>::push_back(true);
						}
					} else {
						for (size_t i = this->m_index + 1; i < this->m_capacity / BIT_COUNT - 1; ++i) {
							this->m_ptr[i] -= 1;
							this->m_index += 1;
						}
						
						this->m_shifter = (1 << (BIT_COUNT - 1));
					}
				}
			}
		} else {
			this->m_index = this->m_size / BIT_COUNT;
				
			if (value) {
				for(size_t i = BIT_COUNT - (this->m_capacity - new_size); i > 0; --i) {
					Vector<bool>::push_back(true);
				}
			}
		}	
	} else if (new_size < this->m_size) {
		this->m_index = this->m_size / BIT_COUNT;
		
		for (size_t i = this->m_index; i > new_size / BIT_COUNT; --i) {
			this->m_ptr[i] = 0;
			this->m_index -= 1;
		}
		
		this->m_shifter = 0;
		this->m_size = (this->m_index + 1) * BIT_COUNT;
		
		for (size_t i = 0; i < this->m_size - new_size; ++i) {
			if (!this->m_shifter) {
				this->m_shifter = 1;
			} else {
				this->m_shifter <<= 1;
			}
			
			--this->m_cleaner;
			this->m_cleaner ^= this->m_shifter;
			
			this->m_ptr[this->m_index] &= this->m_cleaner; 
			this->m_cleaner = 0;
		}
	}
	
	this->m_size = new_size;
	this->m_cleaner = 0;
}

//function that reserves a space...
//he function call does not cause a reallocation 
//if new_capacity is not greater than the current vector capacity
void Vector<bool>::reserve(size_t new_capacity)
{
	if (new_capacity > this->m_capacity) {
		if (this->m_ptr == nullptr) {
			if (new_capacity % BIT_COUNT) {
				Vector<bool>::allocator(new_capacity / BIT_COUNT + 1);
			} else {
				Vector<bool>::allocator(new_capacity / BIT_COUNT);
			}
		} else { 
			if (new_capacity % BIT_COUNT) {
				Vector<bool>::reallocator(this->m_capacity / BIT_COUNT - (new_capacity / this->m_capacity + 1));
			} else {
				Vector<bool>::reallocator(this->m_capacity / BIT_COUNT -  new_capacity / this->m_capacity);
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
		size_t deleted_count = this->m_capacity - (this->m_size % BIT_COUNT + 1) * BIT_COUNT;
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

	this->m_index = this->m_size / BIT_COUNT;
	
	if (value) {
		this->m_ptr[m_index] ^= m_shifter;
	}
	
	--this->m_cleaner;
	this->m_cleaner ^= this->m_shifter;
	this->m_shifter >>= 1;
	this->m_shifter &= this->m_cleaner;
	this->m_cleaner = 0;
	
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
	
	this->m_shifter <<= 1;
	--this->m_cleaner;
	this->m_cleaner ^= this->m_shifter;
	this->m_index = this->m_size / BIT_COUNT;
	this->m_ptr[m_index] &= this->m_cleaner;
	
	--this->m_size;	
	this->m_cleaner = 0;
}

// functions extend the vector by inserting new elements before the element at the specified position

//removes from the vector single element (position) 

//removes from the vector a range of elements

//exchanges the content of the container by the content of obj, which is another vector object of the same type 

//removes all elements from the vector 
void Vector<bool>::clear()
{
	if (this->m_ptr) {
		this->m_index = this->m_size / BIT_COUNT;
		
		for (int i = this->m_index; i >= 0; --i) {
			this->m_ptr[i] = 0;
		}
		
		this->m_size = 0;
	}
}

//print function for my testes
void Vector<bool>::print()
{	
	unsigned short printer = 1 << (BIT_COUNT - 1);
	size_t i = 0;
	for (; this->m_size % BIT_COUNT ? i < this->m_size / BIT_COUNT : i < this->m_capacity / BIT_COUNT + 1; ++i) {
		printer = 1 << (BIT_COUNT - 1);
		
		for (size_t j = BIT_COUNT; j > 0; --j) {
			std::cout << bool(this->m_ptr[i] & printer) << " ";
			printer >>= 1;
 		}
 		
 	}
 		printer = 1 << (BIT_COUNT - 1);
 		for (unsigned short j = this->m_shifter << 1; j > 0; j <<= 1) {
 			std::cout << bool(this->m_ptr[i] & printer) << " ";
			printer >>= 1;
	}
	std::cout << std::endl;
}










