// Implements Separate Chaining.

template <typename HashedObject>
bool SeparateChaining<HashedObject>::Contains(const HashedObject &x) {
  // Find the appropriate list.
  auto &which_list = the_lists_[InternalHash(x)];
  // Search within the list.
  return find(begin(which_list), end(which_list), x) != end(which_list);
}

template <typename HashedObject>
void SeparateChaining<HashedObject>::MakeEmpty() {
  for (auto &this_list : the_lists_)
    this_list.clear();
}

template <typename HashedObject>
bool SeparateChaining<HashedObject>::Insert(const HashedObject & x) {
  // Find the appropriate list.
  auto &which_list = the_lists_[InternalHash(x)];
  // Search within the list.
  if (find(begin(which_list), end(which_list), x) != end(which_list))
    return false;
  collisions_ += which_list.size();
  // Insert at the end of the list.
  which_list.push_back(x);
  // Rehash; see Section 5.5
  if (++current_size_ > the_lists_.size())
    Rehash();
    return true;
}
    
template <typename HashedObject>
bool SeparateChaining<HashedObject>::Insert(HashedObject && x) {
  // Find the appropriate list.
  auto &which_list = the_lists_[InternalHash(x)];
  // Search within the list.
  if (find(begin(which_list), end(which_list), x) != end(which_list)) {
    return false;
  }
  collisions_ += which_list.size();
  // Insert at the end of the list, using rvalue reference.
  which_list.push_back(std::move(x));
  // Rehash; see Section 5.5
  if (++current_size_ > the_lists_.size())
    Rehash();
  return true;
}

template <typename HashedObject>
bool SeparateChaining<HashedObject>::Remove(const HashedObject & x) {
  // Find the appropriate list.
  auto &which_list = the_lists_[InternalHash(x)];
  // Search within the list.
  auto itr = find(begin(which_list), end(which_list), x);
  if (itr == end(which_list))
    return false;
  // Remove.
  which_list.erase(itr);
  --current_size_;
  return true;
}

template <typename HashedObject>
int SeparateChaining<HashedObject>:: GetCurrentSize() const {
	return current_size_;
}

template <typename HashedObject>
int SeparateChaining<HashedObject>:: GetTableSize() const {
	return the_lists_.size();
}

template <typename HashedObject>
int SeparateChaining<HashedObject>:: GetCollisions() const {
	return collisions_;
}

// returns the number of probes needed to insert x into the table.
template<typename HashedObject>
int SeparateChaining<HashedObject>::GetProbes( const HashedObject &x )  {
	auto &which_list = the_lists_[InternalHash(x)];
	auto itr = which_list.begin();
	if (itr == end(which_list))
		return 1;
	probe_ = 1; // internal hashing is considered one probe.
	while (itr != end(which_list) && *itr != x) {
		++probe_;
		++itr;
	}
	return probe_;
}

template <typename HashedObject>
void SeparateChaining<HashedObject>::Rehash() {
  int temp_counter = collisions_;
  vector<list<HashedObject>> old_lists = the_lists_;
  // Create new double-sized, empty table.
  the_lists_.resize(NextPrime(2 * the_lists_.size()));
  for (auto & this_list: the_lists_)
    this_list.clear();

  // Initialize number of elements in hash table to 0.
  current_size_ = 0;
  // Copy from current table to larger table.
  for (auto & this_list : old_lists) {
    for (auto & x : this_list )
      Insert(std::move(x));
  }
  collisions_ = temp_counter;
}