#include <iostream>
#include <fstream>
#include <string>
#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleHashProbing.h"
#include "SeparateChaining.h"

using namespace std;

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
	cout << "TestFunctionForHashTables..." << endl;
	cout << "Words filename: " << words_filename << endl;
	cout << "Query filename: " << query_filename << endl;
	
	// testing for part A
	string word;
	ifstream file(words_filename);
	if (!file.good())
	  cerr << "Error opening file\n";
	else {
	  while ( getline(file, word) ) {
		  hash_table.Insert(word);
	  }
	  file.close();
	}

	cout << "Total number of elements: " << hash_table.GetCurrentSize() << endl;
	cout << "Table size: " << hash_table.GetTableSize() << endl;
	cout << "Load Factor: " << double (hash_table.GetCurrentSize()) / hash_table.GetTableSize() << endl; 
	cout << "Number of Collisions: " << hash_table.GetCollisions() << endl;
	cout << "Average Number of Collisions: " << double(hash_table.GetCollisions()) / hash_table.GetCurrentSize() << endl;
	
	// testing for part B
	ifstream input_file(query_filename);
	string query_word;
	if (!input_file.good())
	  cerr << "Error opening file\n";
	else {
	  while ( getline(input_file, query_word) ) {
		  if (hash_table.Contains(query_word))
			  cout << query_word << " Found. Probes: " << hash_table.GetProbes(query_word) << endl;
		  else 
			  cout << query_word << " Not Found. Probes: " << hash_table.GetProbes(query_word) << endl;
	  }
	  file.close();
	}
}

// Sample main for program CreateAndTestHash
int main(int argc, char **argv) {
	if (argc != 4) {
	cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
	return 0;
	}

	const string words_filename(argv[1]);
	const string query_filename(argv[2]);
	const string param_flag(argv[3]);
	cout << "Input words file is " << words_filename << ", and query file is " << query_filename << endl;
	if (param_flag == "linear") {
	cout << "I will run the linear hashing code " << endl;
	// Run the linear table.
	LinearProbing<string> linear_probing_table;
	TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
	} else if (param_flag == "quadratic") {
	cout << "I will run the quadratic hashing code " << endl;
	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
	} else if (param_flag == "double") {
	cout << "I will run the double hashing code " << endl;
	// ..code for double Hash
	// ..By calling TestFunctionForHashTable()
	DoubleHashProbing<string> double_hash_probing_table;
	TestFunctionForHashTable(double_hash_probing_table, words_filename, query_filename);
	} else if (param_flag == "chaining") {
	cout << "I will run the seperate chaining hashing code " << endl;
	SeparateChaining<string> sep_chaining_table;
	TestFunctionForHashTable(sep_chaining_table, words_filename, query_filename);
	} else {
	cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
	}
	return 0;
}