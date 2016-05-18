#include "BinomialQueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <sstream>
using namespace std;

// deletes item from the binomial queue bq and prints them in ordrer.
void DeleteMinAndPrintInOrder( BinomialQueue<int> &bq ) {
	while ( !bq.IsEmpty()) {
		int num = bq.FindMin();
		cout << num << " ";
		bq.DeleteMin();
	}
	cout << endl;
}

/* deletes the minimum element 10 times from the binomial queue that has been
 * created from the file input_filename and prints in sorted order. If the queue has less than 
 * 10 elements it reports to the user, deletes min and prints all the elements.
 */
void DeleteMin10( BinomialQueue<int> &bq, const string input_filename ) {
	stringstream ss;
	int i = 0;
	int count;
	string number = ""; 
	while (input_filename[i] != '_') {
		number+= input_filename[i];
		++i;
	}
	ss << number;
	ss >> count;
	if (count < 10) {
		cout << "The queue has less than 10 elements\n";
		while ( !bq.IsEmpty()) {
			int num = bq.FindMin();
			cout << num << " ";
			bq.DeleteMin();
		}
	} else {
		int i = 0;
		while ( i < 10 ) {
			int num = bq.FindMin();
			cout << num << " ";
			bq.DeleteMin();
			++i;
		}
	}
	cout << endl; 
}

/** reads numbers from the text file called input_filename and 
 * inserts them in a binomial queue uisng insert function that
 * calls merge. Calculates the time it takes to insert into the
 * queue and then deletes and prints the elements in a sorted order.
 */
void TestBinomialQueueFlag0( const string input_filename, int flag ) {
	// time begins
	const auto begin = chrono::high_resolution_clock::now();
	BinomialQueue<int> bq;
	int number;
	ifstream file(input_filename);
	if (!file.good())
		cerr << "Error Opening File\n";
	else {
		while (file >> number)
			bq.Insert(number); 
		file.close();
	}
	const auto end = chrono::high_resolution_clock::now(); // time ends.
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;

	cout << "Performing Delete Min\n";
	DeleteMinAndPrintInOrder(bq);
}

/** reads numbers from the text file called input_filename and 
 * inserts them in a binomial queue using NEW INSERT function that
 * DOES NOT call merge. Calculates the time it takes to insert into the
 * queue and then deletes and prints the elements in a sorted order.
 */
void TestBinomialQueueWithNewInsertFlag0( const string input_filename, int flag ) {
	// time begins
	const auto begin = chrono::high_resolution_clock::now();
	ifstream file(input_filename);
	int number;
	BinomialQueue<int> bq;
	if(!file.good())
		cerr << "Error Opening File\n";
	else {
		while (file >> number)
			bq.NewInsert(number);
	}
	file.close();
	const auto end = chrono::high_resolution_clock::now(); // time ends.
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;

	cout << "Performing Delete Min\n";
	DeleteMinAndPrintInOrder(bq);
}

/** reads numbers from the text file called input_filename and 
 * inserts them in a binomial queue using NEW INSERT function that
 * uses EFFICIENT MERGE. Calculates the time it takes to insert into the
 * queue and then deletes and prints the elements in a sorted order.
 */
void TestWithNewMergeFlag0( const string input_filename, int flag ) {
	// time begins
	const auto begin = chrono::high_resolution_clock::now();
	BinomialQueue<int> bq;
	int number;
	ifstream file(input_filename);
	if (!file.good())
		cerr << "Error Opening File\n";
	else {
		while (file >> number)
			bq.InsertWithEfficientMerge(number); 
		file.close();
	}
	const auto end = chrono::high_resolution_clock::now(); // time ends.
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;

	cout << "Performing Delete Min\n";
	DeleteMinAndPrintInOrder(bq);
}	

/** reads numbers from the text file called input_filename and 
 * inserts first quarter of elements into one queue and the rest into
 * another queue. Then it merges the two queues and calcualtes the time to perform all these operation 
 * and finally performs DeleteMin10.
 */
void TestBinomialQueueFlag1( const string input_filename, int flag ) {
	// time begins
	const auto begin = chrono::high_resolution_clock::now();
	ifstream file(input_filename);
	int count_item_in_file = 0;
	vector<int> numbers;
	int number;
	BinomialQueue<int> bq1; 
	BinomialQueue<int> bq2;
	if (!file.good())
	  cerr << "Error Opening File\n";
	else {
	  while (file >> number) {
		  numbers.push_back(number);
		  count_item_in_file++;	 
	  }
	  file.close();
	int first_quarter = count_item_in_file / 4;
	for (int i = 0; i < first_quarter; ++i)
	   bq1.Insert(numbers[i]);
	for (int j = first_quarter; j < numbers.size(); ++j)
	   bq2.Insert(numbers[j]);
	bq1.Merge(bq2);
	}
	const auto end = chrono::high_resolution_clock::now(); // time ends.
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;

	cout << "Performing Delete Min 10 Times\n";
	DeleteMin10(bq1, input_filename);
}

/** reads numbers from the text file called input_filename and 
 * inserts first quarter of elements into one queue and the rest into
 * another queue using NEW INSERT FUNCTION. Then it merges the
 * two queues and Calcualtes the time to perform 
 * all these operation and finally performs DeleteMin10.
 */
void TestBinomialQueueWithNewInsertFlag1( const string input_filename, int flag ) {
	//time begins
	const auto begin = chrono::high_resolution_clock::now();
	ifstream file(input_filename);
	int count_item_in_file = 0;
	vector<int> numbers;
	int number;
	BinomialQueue<int> bq1; 
	BinomialQueue<int> bq2;
	if (!file.good())
	  cerr << "Error Opening File\n";
	else {
	  while (file >> number) {
		  numbers.push_back(number);
		  count_item_in_file++;	 
	  }
	  file.close();
	int first_quarter = count_item_in_file / 4;
	for (int i = 0; i < first_quarter; ++i)
	   bq1.NewInsert(numbers[i]);
	for (int j = first_quarter; j < numbers.size(); ++j)
	   bq2.NewInsert(numbers[j]);
	bq1.Merge(bq2);
	}
	const auto end = chrono::high_resolution_clock::now(); // time ends.
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;

	cout << "Performing Delete Min 10 Times\n";
	DeleteMin10(bq1, input_filename);
}	

/** reads numbers from the text file called input_filename and 
 * inserts first quarter of elements into one queue and the rest into
 * another queue using NEW INSERT. Then merges the two queues using 
 * EFFICIENT MERGE and calcualtes the time to perform all 
 *these operation and finally performs DeleteMin10.
 */
void TestWithNewMergeFlag1( const string input_filename, int flag ) {
	// time begins
	const auto begin = chrono::high_resolution_clock::now();
	ifstream file(input_filename);
	int count_item_in_file = 0;
	vector<int> numbers;
	int number;
	BinomialQueue<int> bq1; 
	BinomialQueue<int> bq2;
	if (!file.good())
	  cerr << "Error Opening File\n";
	else {
	  while (file >> number) {
		  numbers.push_back(number);
		  count_item_in_file++;	 
	  }
	  file.close();
	int first_quarter = count_item_in_file / 4;
	for (int i = 0; i < first_quarter; ++i)
	   bq1.InsertWithEfficientMerge(numbers[i]);
	for (int j = first_quarter; j < numbers.size(); ++j)
	   bq2.InsertWithEfficientMerge(numbers[j]);
	bq1.NewMerge(bq2);
	}
	const auto end = chrono::high_resolution_clock::now(); // time ends.
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;
	cout << "Performing Delete Min 10 Times\n";
	DeleteMin10(bq1, input_filename);
}

// Sample main for program BinomialQueue
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <input_file_to_create_queue> <flag>" << endl;
    cout << "    flag should be either 0 or 1" << endl;
    return 0;
  }
  const string input_filename(argv[1]);
  const int flag = atoi(argv[2]);
  //testing part A.
  if (flag == 0) {
  	cout << "Input is " << input_filename << endl;
	cout << "Flag is " << flag << endl;

  	cout << "-----------Testing part A------------: \n";
  	cout << "Time Needed With Intial Fucntions:\n";
	TestBinomialQueueFlag0(input_filename, flag);

	//Testing part B
	// testing insertion using new insert with flag 0.
	cout << "-----------Testing part B------------: \n";
	cout << "Time needed for the New Insert: \n";
	TestBinomialQueueWithNewInsertFlag0(input_filename, flag);
	
	//Testing Part C
	//tesitng with New Merge with flag 0
	cout << "-----------Testing part C------------: \n";
	cout << "Time needed for the New Merge: \n";
	TestWithNewMergeFlag0(input_filename, flag);
  } 
  else if (flag == 1) {
  	cout << "Input is " << input_filename << endl;
	cout << "Flag is " << flag << endl;

	// testing part A with flag 1
	cout << "-----------Testing part A------------: \n";
	cout << "Time Needed With Intial Fucntions: \n";
	TestBinomialQueueFlag1(input_filename, flag);	
	
	//testing part B with flag 1
	cout << "-----------Testing part B------------: \n";
	cout << "Time needed for the New Insert: \n";
	TestBinomialQueueWithNewInsertFlag1(input_filename, flag);
	
	//Testing Part C
	//tesitng with New Merge with flag 1
	cout << "-----------Testing part C------------: \n";
	cout << "Time needed for the New Merge: \n";
	TestWithNewMergeFlag1(input_filename, flag);
  }
  else
	  cout << "flag must be either 0 or 1\n";
  
  return 0;
}
