// Implements Quadratic Probing.

template <typename HashedObj>
bool HashTable<HashedObj>::Contains(const HashedObj & x) {
  return IsActive(FindPos(x));
}

template <typename HashedObj>
void HashTable<HashedObj>::MakeEmpty() {
  current_size_ = 0;
  for (auto & entry : array_)
    entry.info_ = kEmpty;
}

template <typename HashedObj>
bool HashTable<HashedObj>::Insert(const HashedObj & x) {
  // Insert x as active.
  int current_pos = FindPos(x);
  if (IsActive(current_pos))
    return false;
  
  array_[current_pos].element_ = x;
  array_[current_pos].info_ = kActive;
  
  // Rehash; see Section 5.5.
  if (++current_size_ > array_.size() / 2)
    Rehash();
  
  return true;
}
    
template <typename HashedObj>
bool HashTable<HashedObj>::Insert(HashedObj && x) {
  // Insert x as active.
  int current_pos = FindPos(x);
  if (IsActive(current_pos))
    return false;
  
  array_[current_pos] = std::move(x);
  array_[current_pos].info_ = kActive;
  
  // Rehash; see Section 5.5.
    if (++current_size_ > array_.size() / 2)
      Rehash();
    
    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::Remove(const HashedObj & x) {
  int current_pos = FindPos(x);
  if (!IsActive(current_pos))
    return false;
  
  array_[current_pos].info_ = kDeleted;
  return true;
}

template <typename HashedObj>
int HashTable<HashedObj>::GetCurrentSize() const {
	return current_size_;
}

template <typename HashedObj>
int HashTable<HashedObj>::GetTableSize() const {
	return array_.size();
}

template <typename HashedObj>
int HashTable<HashedObj>::GetCollisions() const {
	return collisions_;
}

template<typename HashedObj>
int HashTable<HashedObj>::GetProbes( const HashedObj &x)  {
	int current_pos = FindPos(x);
	return array_[current_pos].probe_;
}

template <typename HashedObj>
int HashTable<HashedObj>::FindPos(const HashedObj & x) {
  int offset = 1;
  int current_pos = InternalHash(x);
  int probe = 1; // probe is always one greater than the number of collisions.
  
  while (array_[current_pos].info_ != kEmpty &&
	array_[current_pos].element_ != x ) {
    // Compute ith probe.
    current_pos += offset;  
    offset += 2;
	collisions_++;
	probe++;
      if (current_pos >= array_.size())
	current_pos -= array_.size( );
    }
	array_[current_pos].probe_ = probe;
  return current_pos;
}

template <typename HashedObj>
void HashTable<HashedObj>::Rehash() {
	int temp_collisions = collisions_;
  vector<HashEntry> old_array = array_;
  // Create new double-sized, empty table.
  array_.resize(NextPrime(2 * old_array.size()));
  for (auto & entry : array_)
    entry.info_ = kEmpty;
  
  // Copy table over.
  current_size_ = 0;
  for (auto & entry : old_array)
    if (entry.info_ == kActive)
      Insert(std::move(entry.element_));

  collisions_ = temp_collisions;
}
