/* Tyler Jackson
 * Date: Nov. 16, 2013
 *
 * 			HashTab.h
 *
 *		This is the header class for my hashtable-- it relies heavily on unordered map.
 */

#ifndef HASHTAB_H_
#define HASHTAB_H_
#include <string>
#include <cstdlib>
#include <tr1/unordered_map>
#include <map>
#include "Word.h"
using namespace std;

typedef tr1::unordered_map<string, Word> hashtable;

class HashTab {
public:
	//default constructor
	HashTab();
	//insert word into the hash table
	void insert(Word& w);
	//print the hash table--then put the hash table into a map and print it in order
	void print();
	//default destructor
	virtual ~HashTab();
	//checks if a word exists
	bool wordExists(string word);
	// returns a word based on a string
	Word getWord(string);
private:
	//unordered map object
	hashtable table;
};

#endif /* HASHTAB_H_ */
