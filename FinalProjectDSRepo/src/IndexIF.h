/* Tyler Jackson
 * Date: Nov. 16, 2013
 *
 * IndexIF.h
 *
 *			This is my index interface class.  It has only virtual functions, and I overwrite
 *		everything in my AVL and Hash interface classes.
 */

#ifndef INDEXIF_H_
#define INDEXIF_H_
#include <string>
#include <algorithm>
using namespace std;

class IndexIF {
public:

	IndexIF();
	virtual void search(string query);
	virtual void index(string filepath);
	virtual void setResultsFromBoolean(string);
	virtual void print();
	virtual void printResults();
	virtual void printRankedResults();
	virtual ~IndexIF();
private:
	virtual void rankResults(int numResultsFromAnd);
	virtual void setTFIDFANDS(int docID, double & tfIDF,int numResultsFromAnd);
	virtual void setTFIDFORS(int docID, double & tfIDF);


};

#endif /* INDEXIF_H_ */
