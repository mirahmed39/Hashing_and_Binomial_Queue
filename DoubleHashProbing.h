/** @file        : DoubleHashProbing.h
 *  @author      : Mir Ahmed
 *  @detail      : the double hash probing class inherits all the functionalities
 				   of quadratic probing class except for that it has a different way of
 				   hashing elements to a table. So it uses the idea of polymorphism to
 				   overwrite the FindPos fucntion and it has its own second hash function.
 	@date created: 03/26
 */
#ifndef _DOUBLE_HASH_PROBING_H_
#define _DOUBLE_HASH_PROBING_H_
#include "QuadraticProbing.h"

template<typename L>
class DoubleHashProbing : public HashTable<L> {
protected:
	// second hash fucntion that is used that hashes x and produces an integer. 
	int hash2(const L &x ) {
		static hash<L> hf;
		int hash_val  = hf(x);
		return 47 - (hash_val % 47);
	}
	// @returns the index of the table where x should belong.
	int FindPos(const L &x) {
		int offset = hash2(x);
		int current_pos = HashTable<L>::InternalHash(x);
		int probe = 1; 
		
		while (HashTable<L>::array_[current_pos].info_ != HashTable<L>::kEmpty &&
		HashTable<L>::array_[current_pos].element_ != x ) {
			// Compute ith probe.
			current_pos += offset;
			HashTable<L>::collisions_++;
			probe++;
			// this assures wrapping around the table once the hash exceeds table size
			if (current_pos >= HashTable<L>::array_.size())
				current_pos -= HashTable<L>::array_.size( );
		}
		HashTable<L>::array_[current_pos].probe_ = probe;
		return current_pos;
	}
};

#endif // _DOUBLE_HASH_PROBING_H_