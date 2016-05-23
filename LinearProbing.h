/** @file        : LinearProbing.h
 *  @author      : Mir Ahmed
 *  @detail      : the linear hash probing class inherits all the functionalities
 				   of quadratic probing class except for that it has a different way of
 				   hashing elements to a table. So it uses the idea of polymorphism to
 				   overwrite the FindPos fucntion and it has its own second hash function.
 	@date created: 03/26
 */
#ifndef _LINEAR_PROBING_H_
#define _LINEAR_PROBING_H_
#include "QuadraticProbing.h"


template<typename T>
class LinearProbing : public HashTable<T> {
protected:
	// @returns the index of the table where x should belong.
	int FindPos(const T & x) {
		int offset = 1;
		int current_pos = HashTable<T>::InternalHash(x);
		int probe = 1;
  
		while (HashTable<T>::array_[current_pos].info_ != HashTable<T>::kEmpty &&
		HashTable<T>::array_[current_pos].element_ != x ) {
			// Compute ith probe.
			current_pos += offset; 
			HashTable<T>::collisions_++;
			probe++;
			// this assures wrapping around the table once the hash exceeds table size
			if (current_pos >= HashTable<T>::array_.size())
				current_pos -= HashTable<T>::array_.size( );
		}
		HashTable<T>::array_[current_pos].probe_ = probe;
		return current_pos;
	}
};

#endif // _LINEAR_PROBING_H_