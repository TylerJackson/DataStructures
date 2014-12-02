/* Tyler Jackson
 * 11/23/13
 * QueryProcessor.h
 *
 *  	This is our query processor header class.  Notice it allows you to set the query, but
 *  it keeps all implementation functions private.  Therefore when we use this object later we
 *  pass in the query.  The rest is handled by the class private functions.  We can then get each
 *  string array using the getters.
 */

#ifndef QUERYPROCESSOR_H_
#define QUERYPROCESSOR_H_
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class QueryProcessor {
public:
	//default constructor
	QueryProcessor();
	//constructor with the query as an argument
	QueryProcessor(string tempQuery);
	//sets the query
	void setQuery(string tempQuery);
	//returns the or words
	string* getOrs();
	//returns the not words
	string* getNots();
	//returns the ands
	string* getAnds();
	//gets the num ors
	int getNumOrs();
	//gets the num nots
	int getNumNots();
	//gets the number of ands
	int getNumAnds();
	//prints the query
	void printQuery();
	//default destructor
	virtual ~QueryProcessor();

private:
	//sets the indices of the bools
	void setIndicesOfBools();
	//sets the and words array
	void setAnds();
	//sets the or words array
	void setOrs();
	//sets the not words array
	void setNots();
	//determines which type of query
	void setQueryType();
	//prints the ands array
	void printAnds();
	//prints the ors array
	void printOrs();
	//prints the nots array
	void printNots();
	//stems the words in the array
	void stemStringArray(string * s, int numInArray);
	//reads in the stop words from the file
	void setStopWordsFromFile();
	//checks if the word is a stop word
	bool isStopWord(string s);

	vector<string> stopWords;
	string * andWords;
	string * orWords;
	string * notWords;
	string query;
	bool containsNot;
	bool containsAnd;
	bool containsOr;

	int andIndex;
	int orIndex;
	int notIndex;
	int numAnds = 0;
	int numOrs = 0;
	int numNots = 0;



};


#endif /* QUERYPROCESSOR_H_ */
