/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename Type>
class Quadratic_hash_table {
	private:
		int count;
		int power;
		int array_size;
		int mask;
		Type *array;
		bin_state_t *occupied;

		int hash( Type const & ) const;

	public:
		Quadratic_hash_table( int = 5 );
		~Quadratic_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;

		void print() const;

		void insert( Type const & );
		bool erase( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Quadratic_hash_table<T> const & );
};

template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new bin_state_t[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}
}

// Your implementation here
template <typename Type>
int Quadratic_hash_table<Type>::hash(Type const & obj) const{
	return (static_cast<int>(obj) & mask);
}

template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table(){
	delete [] array;
	delete [] occupied;
}

template <typename Type>
int Quadratic_hash_table<Type>::size() const{
	return count;
}

template <typename Type>
int Quadratic_hash_table<Type>::capacity() const{
	return array_size;
}

template <typename Type>
double Quadratic_hash_table<Type>::load_factor() const{
	int load = 0;
	for (int i = 0; i < array_size; ++i) {
		load += (occupied[i] != bin_state_t::UNOCCUPIED);
	}
	return static_cast<double>(load) / static_cast<double>(array_size);
}

template <typename Type>
bool Quadratic_hash_table<Type>::empty() const{
	return (count == 0);
}

template <typename Type>
bool Quadratic_hash_table<Type>::member(Type const& obj) const{
	int index=hash(obj);
	for (int i = 0; i < array_size; ++i) {
		index +=i;
		if (index > array_size) {
			index -= array_size;
		}
		if (occupied[index] == bin_state_t::UNOCCUPIED) {
			return false;
		} else if ((occupied[index] == bin_state_t::OCCUPIED) && array[index] == obj) {
			return true;
		}
	}
	return false;
}

template <typename Type>
Type Quadratic_hash_table<Type>::bin(int n) const {
	return array[n];
}

template <typename Type>
void Quadratic_hash_table<Type>::print() const{
	for (int i = 0; i < array_size; ++i) {
		if (occupied[i]==bin_state_t::OCCUPIED) {
			std::cout << array[i] << " ";
		} else if (occupied[i]==bin_state_t::ERASED) {
			std::cout << "* ";
		}
	}
	std::cout << std::endl;
}

template <typename Type>
void Quadratic_hash_table<Type>::insert(Type const& obj) {
	if (count == array_size) {
		throw overflow();
	} else {
		int index = hash(obj);
		for (int i = 0; i < array_size; ++i) {
			index += i;
			if (index >= array_size) {
				index -= array_size;
			}
			if ((occupied[index] == bin_state_t::OCCUPIED)
			&& (array[index] == obj)) {
				return;
			} else if (occupied[index] !=bin_state_t::OCCUPIED) {
				occupied[index] = bin_state_t::OCCUPIED;
				array[index]=obj;
				count += 1;
				return;
			}
		}
	}
}

template <typename Type>
bool Quadratic_hash_table<Type>::erase (Type const& obj) {
	int index = hash(obj);
	for (int i = 0; i < array_size; ++i) {
		index +=i;
		if (index >= array_size) {
			index -= array_size;
		}
		if (occupied[index] == bin_state_t::UNOCCUPIED) {
			return false;
		} else if ((occupied[index] == OCCUPIED)
		&& (array[index] == obj)) {
			count -=1;
			occupied[index]=bin_state_t::ERASED;
			return true;
		}
	}
}

template <typename Type>
void Quadratic_hash_table<Type>::clear() {
	count = 0;
	for (int i = 0; i < array_size; ++i) {
		occupied[i] = bin_state_t::UNOCCUPIED;
	}
}
template <typename T>
std::ostream &operator<<( std::ostream &out, Quadratic_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == UNOCCUPIED ) {
			out << "- ";
		} else if ( hash.occupied[i] == ERASED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif
