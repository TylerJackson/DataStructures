/* Tyler Jackson
 * Date: Nov. 16, 2013
 * HashIF.h
 *
 *		This is my Hash IF header class that briefly describes the functionality
 *	The Hash interface class inherits from the IndexIF class and handles basically all
 *	functionality on the hash table side of the project.
 */

#ifndef HASHIF_H_
#define HASHIF_H_
#include "IndexIF.h"
#include "HashTab.h"
#include "QueryProcessor.h"
using namespace std;

typedef map<int, double> inversefinalresults;	 //docID,tfidf
class HashIF: public IndexIF{
public:
	//default constructor
	HashIF();

	//search the hash table based on a query
	void search(string query);

	//load index into hash table from inverted file index filepath
	void index(string filepath);

	//print the hash table
	void print();

	//print the results from the query
	void printResults();

	//set results from the query into the results list--then calls rank results to set the
	//tf-idf score for the results and stores into FinalRankedResultsInverse
	void setResultsFromBoolean(string);

	//this prints the ranked results based on their tf-idf score in descending order
	void printRankedResults();

	//destructor
	virtual ~HashIF();
private:
	//apply a tf-idf score to each doc by calling  setTFIDF AND and OR
	void rankResults(int numResultsFromAnd);

	//calcs the tf-idf score for results that came from the and part of the query
	void setTFIDFANDS(int docID, double & tfIDF,int numResultsFromAnd);

	//calcs the tf-idf score for results that came from the or part of the query
	void setTFIDFORS(int docID, double & tfIDF);

	QueryProcessor * Qproc;
	HashTab * hashTable;
	inversefinalresults FinalRankedResultsInverse;
	AssocArray results;

};

#endif /* HASHIF_H_ */
