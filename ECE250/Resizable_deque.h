/*****************************************
 * UW User ID:  20629096
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
		// Your member variables
		Type* array;
		int initial_array_capacity;
		int array_capacity;
		int deque_size;
		int ifront;
		int iback;
		// Any private member functions
		//   - helper functions for resizing your array?
		void double_deque();
		void half_deque();
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n )
// Your initalization list
:array{new Type[n]},initial_array_capacity{n},array_capacity{n},
deque_size{0},ifront{8},iback{8}
{
	// Enter your implementation here
	if (n < 16) {
		initial_array_capacity = 16;
		array_capacity = 16;
	}
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque )
// Your initalization list
:array{new Type[deque.array_capacity]},
initial_array_capacity{deque.initial_array_capacity}, //not quite sure about this
array_capacity{deque.array_capacity},
deque_size{deque.deque_size},ifront{deque.ifront},iback{deque.iback}
{
	// Enter your implementation here
	for (int i=0; i < array_capacity; ++i){
		array[i] = deque.array[i];
	}
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
// Your initalization list
:array{deque.array},
initial_array_capacity{deque.initial_array_capacity},
array_capacity{deque.array_capacity},
deque_size{deque.deque_size},ifront{deque.ifront},iback{deque.iback}
{
	// Enter your implementation here
	deque.array = nullptr;
}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	// Enter your implementation here
	delete[] array;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
	// Enter your implementation here
	return deque_size;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// Enter your implementation here
	return array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// Enter your implementation here
	return deque_size == 0;
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// Enter your implementation here
	if (deque_size == 0) throw underflow();
	return array[ifront];
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// Enter your implementation here
	if (deque_size ==0) throw underflow();
	return array[iback];
}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
	//     std::swap( variable, deque.variable );

	// Enter your implementation here
	std::swap(array,deque.array);
	std::swap(initial_array_capacity,deque.initial_array_capacity);
	std::swap(array_capacity,deque.array_capacity);
	std::swap(deque_size,deque.deque_size);
	std::swap(ifront,deque.ifront);
	std::swap(iback,deque.iback);
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	// Enter your implementation here
	if (array_capacity == deque_size) {
		double_deque();
	}
	--ifront;
	if (ifront < 0) {
		ifront = array_capacity;
	}
	array[ifront] = obj;
	if (deque_size == 0) iback = ifront;
	++deque_size;
}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
	if (array_capacity == deque_size) {
		double_deque();
	}
	++iback;
	if (iback == array_capacity) {
		iback = 0;
	}
	array[iback] = obj;
	if (deque_size == 0) ifront = iback;
	++deque_size;
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
	// Enter your implementation here
	if (deque_size == 0) throw underflow();
	++ifront;
	if (ifront == array_capacity) {
		ifront = 0;
	}
	--deque_size;
	if ((4*deque_size <= array_capacity) && array_capacity > initial_array_capacity) {
		half_deque();
	}
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// Enter your implementation here
	if (deque_size == 0) throw underflow();
	--iback;
	if (iback < 0) {
		iback = array_capacity;
	}
	--deque_size;
	if ((4*deque_size <= array_capacity) && array_capacity > initial_array_capacity) {
		half_deque();
	}
}

template <typename Type>
void Resizable_deque<Type>::clear() {
	// Enter your implementation here
	delete[] array;
	array = new Type[initial_array_capacity];
	array_capacity = initial_array_capacity;
	deque_size = 0;
	ifront = initial_array_capacity / 2;
	iback = ifront;
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functios (helper functions) here
template <typename Type>
void Resizable_deque<Type>::double_deque() {
	int old_array_capacity = array_capacity;
	array_capacity *= 2;
	Type* old_array = array;
	array = new Type[array_capacity];
	if (ifront <= iback) {
		for (int i=ifront; i <= iback; ++i) {
			array[i] = old_array[i];
		}
	} else {
		for (int i = 0; i <= iback; ++i) {
			array[i] = old_array[i];
		}
		for (int i=1; i <= old_array_capacity - ifront; ++i) {
			array[array_capacity-i] = old_array[old_array_capacity-i];
		}
		ifront = array_capacity - (old_array_capacity - ifront);
	}
}

template<typename Type>
void Resizable_deque<Type>::half_deque() {
	int old_array_capacity = array_capacity;
	array_capacity /= 2;
	Type* old_array = array;
	array = new Type[array_capacity];
	if (ifront <= iback) {
		for (int i = 0; i <= iback - ifront; ++i) {
			array[i] = old_array[ifront+i];
		}
		ifront = 0;
		iback = deque_size - 1;
	} else {
		for (int i = 0; i <= iback; ++i) {
			array[i] = old_array[i];
		}
		for (int i = 1; i <= old_array_capacity - ifront; ++i) {
			array[array_capacity-i] = old_array[old_array_capacity-i];
		}
		ifront = array_capacity - (old_array_capacity - ifront);
	}
}


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
	out << "deque_size is " << list.deque_size << std::endl;
	out << "array_capacity is " << list.array_capacity << std::endl;
	out << "initial_array_capacity is " << list.initial_array_capacity << std::endl;
	if (list.deque_size == 0) {
		out << " " << std::endl;
		return out;
	} else if (list.ifront <= list.iback) {
		for (int i = list.ifront; i <= list.iback; ++i) {
			out << list.array[i] << " ";
		}
	} else {
		for (int i = list.ifront; i < list.array_capacity; ++i) {
			out << list.array[i] << " ";
		}
		for (int i = 0; i <= list.iback; ++i) {
			out << list.array[i] << " ";
		}
	}
	out << std::endl;
	return out;
}

#endif
