/** @file        : QuadraticProbing.h
 *  @author      : Mir Ahmed
 *  @detail      : the quadratic probing class implements the hashtable data structure
                   that is known for constant operation such as insert, find, delete.
  @date created: 03/25
 */
#ifndef CSCI335_HASHING_QUADRATIC_PROBING_H_
#define CSCI335_HASHING_QUADRATIC_PROBING_H_
#include <vector>
using namespace std;

// Unnamed namespace for stand-alone functions.
// Place them in cpp file when using one.
namespace {
// Internal method to test if a positive number is prime.
// Not an efficient algorithm.
bool IsPrime(int n) {
  if (n == 2 || n == 3)
    return true;
  if (n == 1 || n % 2 == 0)
    return false;
  for (int i = 3; i * i <= n; i += 2)
    if (n % i == 0)
      return false;
  return true;
}

// Internal method to return a prime number at least as large as n.
// Assumes n > 0.
int NextPrime(int n) {
    if (n % 2 == 0) ++n;
    for ( ;!IsPrime(n); n += 2) ;
    return n;
}

}  // namespace

// QuadraticProbing Hash table class.
// Assumes that there is a class hash<HashedObj> that overloads
// the () operator returning a size_t.
// Sample usage:
//  HashTable<string> a_hash_table;
//  while (..getting string a_string..)
//    a_hash_table.Insert(a_string);
//  const b_string = "A given string";
//  if (a_hash_table.Contains(b_string))
//     cout << b_string << " in table " << endl;
//  else
//     cout << b_string << " not in table " << endl;
//  const c_string = "Another string";
// if (a_hash_table.Remove(c_string))
//    cout << "Removed " << c_string << endl;
// else
//    cout << c_string << " Not in the table" << endl;
// a_hash_table.MakeEmpty();  // Clears everything.
template <typename HashedObj>
class HashTable {
 public:
  // Each hash-cell is in one of these states.
  enum EntryType {kActive, kEmpty, kDeleted};

  explicit HashTable(int size = 101) : array_(NextPrime(size)), collisions_{0}
    { MakeEmpty(); }
  HashTable(const HashTable &a_hash_table) = default;
  HashTable(HashTable &&a_hash_table) = default;
  HashTable &operator=(const HashTable &a_hash_table) = default;
  HashTable &operator=(HashTable &&a_hash_table) = default;
  ~HashTable() = default;

  // @param x: A given item.
  // @return true if item is in the hash table and false otherwise.
  bool Contains(const HashedObj & x);

  // Empties the hash table.
  void MakeEmpty();

  // @param x: Item to insert.
  // @return true if insertion was succesfull, false otherwise
  //   (i.e. when x is already in the hash table).
  // Insertion may lead to rehashing.
  bool Insert(const HashedObj & x);

  // Same as above Insert for x being an rvalue reference.
  bool Insert(HashedObj && x);
  
  // @param x: Item to be removed.
  // @return true if succesfull, false if x is not found in the
  //   hash table.
  bool Remove(const HashedObj & x);
  
  // @return the total number of element in the table
  int GetCurrentSize() const;
  
  // @reutrns the table size
  int GetTableSize() const;
  
  // @returns the number of collisions in the hash table
  int GetCollisions() const;
  
  // @returns number of probes needed to insert x.
  int GetProbes(const HashedObj &x );

protected:
  // Each hash entry contains the item and its type.
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
	  int probe_ = 0;
    
    HashEntry(const HashedObj &element = HashedObj{}, EntryType infotype = kEmpty)
     : element_{element}, info_{infotype} {}  
    HashEntry(HashedObj &&element, EntryType infotype = kEmpty)
     : element_{std::move(element)}, info_{infotype} { }
  };
  // The hash table.
  vector<HashEntry> array_;
  // Number of elements in the hash table.
  int current_size_;
  
  // number of collisions in the hash table.
  int collisions_;

  // @param current_pos: position in the hash table.
  // @return true if item in that position is kActive,
  //    false otherwise.
  // No error checking is performed (i.e. it is assumed
  //   that current_pos is within the correct range).
  bool IsActive(int current_pos) const
  { return array_[ current_pos ].info_ == kActive; }

  // @param x: a given item.
  // @returns the location of x in the hash table if item
  //   is there (i.e. a HashEntry with element_ equal to x
  //   and info_ being kActive). If x is not in the 
  //   hash table, the function returns the position of
  //   insertion of x.
  virtual int FindPos(const HashedObj & x);

  // Performs rehashing by creating a new hash table having
  // size being equal to the next prime greater than or equal
  // to the double of the current table size.
  // Note that table size is _array.size();
  void Rehash(); 
  

  // @param x: a given item.
  // Returns the hash value of x.
  // Assumes that a class hash<HashedObj> has been defined,
  // with an overloaded () operator.
  size_t InternalHash(const HashedObj & x) const {
    static hash<HashedObj> hf;
    return hf(x) % array_.size();
  }
};

#include "QuadraticProbing.cpp"  // For template compilation.
#endif  // CSCI335_HASHING_QUADRATIC_PROBING_H_
