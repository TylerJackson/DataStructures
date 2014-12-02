/* Tyler Jackson
 * Date: Nov. 16, 2013
 * AVLIF.h
 *
 *		This is my AVL IF header class that briefly describes the functionality
 *	The AVL interface class inherits from the IndexIF class and handles basically all
 *	functionality on the AVL Tree side of the project.
 */

#ifndef AVLIF_H_
#define AVLIF_H_
#include "AVLTree.h"
#include "IndexIF.h"
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <map>
#include "QueryProcessor.h"
using namespace std;

typedef map<int, double> inversefinalresults;	 //docID,tfidf

class AVLIF: public IndexIF{
public:
	//default constructor
	AVLIF();

	//search the avl tree based on a query
	void search(string query);

	//load index into avl tree from inverted file index filepath
	void index(string filepath);

	//print the avl tree
	void print();

	//print the results from the query
	void printResults();

	//set results from the query into the results list--then calls rank results to set the
	//tf-idf score for the results and stores into FinalRankedResultsInverse
	void setResultsFromBoolean(string);

	//this prints the ranked results based on their tf-idf score in descending order
	void printRankedResults();

	//destructor
	virtual ~AVLIF();
private:
	//apply a tf-idf score to each doc by calling  setTFIDF AND and OR
	void rankResults(int numResultsFromAnd);

	//calcs the tf-idf score for results that came from the and part of the query
	void setTFIDFANDS(int docID, double & tfIDF,int numResultsFromAnd);

	//calcs the tf-idf score for results that came from the or part of the query
	void setTFIDFORS(int docID, double & tfIDF);

	QueryProcessor * Qproc;
	AVLTree * tree;
	inversefinalresults FinalRankedResultsInverse;
	AssocArray results;

};

#endif /* AVLIF_H_ */
