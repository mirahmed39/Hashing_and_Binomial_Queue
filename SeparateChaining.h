/** @file        : SeparateChaining.h
 *  @author      : Mir Ahmed
 *  @detail      : the separate chaining class implements hashtable
                   data structure using stl vector and lists. It is
                   primarily known for avoiding collisions in the table
                   It can do operations such as inserting an element, deleteing.
                   finding etc. 
  @date created: 03/27
 */
#ifndef CSCI335_HASHING_SEPARATE_CHAINING_H_
#define CSCI335_HASHING_SEPARATE_CHAINING_H_

#include <algorithm>
#include <vector>
#include <list>
using namespace std;


// SeparateChaining Hash table class.
// Assumes that there is a class hash<HashedObject> that overloads
// the () operator returning a size_t.
// Sample usage:
//  SeparateChaining<string> a_hash_table;
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
template <typename HashedObject>
class SeparateChaining {
 public:
  explicit SeparateChaining(int size = 101) : current_size_{0}
  { the_lists_.resize(101); }

  SeparateChaining(const SeparateChaining &a_hash_table) = default;
  SeparateChaining(SeparateChaining &&a_hash_table) = default;
  SeparateChaining &operator=(const SeparateChaining &a_hash_table) = default;
  SeparateChaining &operator=(SeparateChaining &&a_hash_table) = default;
  ~SeparateChaining() = default;

  // @param x: A given item.
  // @return true if item is in the hash table and false otherwise.
  bool Contains(const HashedObject &x);

  // Empties the hash table.
  void MakeEmpty();

  // @param x: Item to insert.
  // @return true if insertion was succesfull, false otherwise
  //   (i.e. when x is already in the hash table).
  // Insertion may lead to rehashing.
  bool Insert(const HashedObject & x);

  // Same as above Insert for x being an rvalue reference.
  bool Insert(HashedObject && x);

  // @param x: Item to be removed.
  // @return true if succesfull, false if x is not found in the
  //   hash table.
  bool Remove(const HashedObject & x);
  
  // @return the total number of element in the table
  int GetCurrentSize() const;
  
  // @reutrns the table size
  int GetTableSize() const;
  
  // @returns the number of collisions in the hash table
  int GetCollisions() const;
  
  // @ returns the number of probes 
  int GetProbes(const HashedObject &x);
  
 private:

  // The vector of lists.
  // TableSize is the_lists_.size().
  vector<list<HashedObject>> the_lists_;
  // The number of elements in the hash table.
  int  current_size_;
  
  int collisions_= 0;
  
  int probe_ = 0;
  
  // Performs rehashing by creating a new hash table having
  // size being equal to the next prime greater than or equal
  // to the double of the current table size.
  // Note that table size is _array.size();
  void Rehash();

  // @param x: a given item.
  // Returns the hash value of x.
  // Assumes that a class hash<HashedObject> has been defined,
  // with an overloaded () operator.
  size_t InternalHash(const HashedObject & x) const {
    static hash<HashedObject> hf;
    return hf(x) % the_lists_.size( );
  }
};

#include "SeparateChaining.cpp"  // For template compilation.
#endif  // CSCI335_HASHING_SEPARATE_CHAINING_H_
