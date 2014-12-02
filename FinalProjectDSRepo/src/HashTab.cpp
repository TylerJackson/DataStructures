/* Tyler Jackson
 * Date: Nov. 16, 2013
 *
 * 		HashTab.cpp
 *
 *			This is my hash table implementation class.  It relies heavily on unordered_map
 */

#include "HashTab.h"
#include <cstdlib>
#include <iostream>
using namespace std;
typedef std::map<string,Word> ordered;

HashTab::HashTab() {

}

//insert your word into a hashtable
void HashTab::insert(Word& w){
	string s = w.getWord();
	std::pair<std::string,Word> pair1 (s,w);
	//cout << "The word I am inserting is: " << pair1.first << endl;
	table.insert(pair1);
}
//print the hashtable--then puts it into a map and prints it in order
void HashTab::print(){
	cout << "First I will print my hashTable" << endl;
	cout << endl;
	hashtable::const_iterator it1;
	for(it1 = table.begin(); it1 != table.end();++it1){
		cout << "the name is: " << it1->first << endl;
		Word tempWord;
		tempWord = it1->second;
		tempWord.printDocsIDs();
	}
	cout << endl;

	cout << "Then I wanted to print it in order so I moved it from my hashTable into a map object" << endl;

	cout << endl;
	ordered Temp(table.begin(),table.end());
	ordered::const_iterator it;
	for(it = Temp.begin(); it != Temp.end();++it){
		cout << "the name is: " << it->first << endl;
		Word tempWord;
		tempWord = it->second;
		tempWord.printDocsIDs();
	}
}

//destructor
HashTab::~HashTab() {
}

//checks if the word exists
bool HashTab::wordExists(string word){
	if(table.count(word) > 0)
		return true;
	else return false;
}

//only call if wordExists
Word HashTab::getWord(string word){
//	Word temp;
//	return temp;
	return table[word];
}
