/*	Tyler Jackson
 * 11/19/13
 *
 * 		IndexIFTester.cpp
 *
 *
 * This class tests the Index interface.  I created two interfaces, one for the AVL Tree object and
 * one for the Hash Object.  Note the polymorphism when initializing the IndexIF objects.
 * I tested all the functionality of both classes
 *
 */

#include "IndexIF.h"
#include "AVLIF.h"
#include "HashIF.h"
int main(){
	string filepath = "/home/tgjackson/workspace/FinalProjectDSRepo/INDEXIFINDEXTESTER.txt";
	IndexIF * AVLTestIF = new AVLIF();
	IndexIF * HashTestIF = new HashIF();

	AVLTestIF->index(filepath);
	HashTestIF->index(filepath);

	AVLTestIF->print();
	HashTestIF->print();

	cout << endl;
	cout << endl;
	cout << "--------------------------------------------------------------------" << endl;
	cout << endl;
	cout << endl;

	cout << "Now I wanna test my AVL Interface's ability to only get results from our query" << endl;

	string query = "AND human axial";

	cout << "Query Test 1" << endl;
	cout << "This query tests AND of two words (human and axial)" << endl;
	cout << "The results should be 1481605, 2 and 1485605,2" << endl;
	cout << endl;

	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	query = "AND human anatomyosteologyaxialskeleton axial";

	cout << "Query Test 2" << endl;
	cout << "This query tests AND of three words (human, axial, and anatomyosteologyaxialskeleton)" << endl;
	cout << "The results should be 1481605, 2." << endl;
	cout << endl;

	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	query = "AND human anatomyosteologyaxialskeleton axial OR skull";

	cout << "Query Test 3" << endl;
	cout << "This query tests AND of three words (human, axial, and anatomyosteologyaxialskeleton)" << endl;
	cout << "This query tests that result OR with skull" << endl;
	cout << "The results should be 1481605, 2, 1481699, 1, 1481600, 1." << endl;
	cout << endl;

	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	query = "AND human anatomyosteologyaxialskeleton axial OR skull bodi";

	cout << "Query Test 4" << endl;
	cout << "This query tests AND of three words (human, axial, and anatomyosteologyaxialskeleton)" << endl;
	cout << "This query tests that result OR with skull and bodi" << endl;
	cout << "The results should be 1481603, 1, 1481601, 1, 1481605, 2, 1481699, 1, 1481600, 1." << endl;
	cout << endl;

	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	query = "AND human anatomyosteologyaxialskeleton axial OR skull bodi NOT consist";

	cout << "Query Test 5" << endl;
	cout << "This query tests AND of three words (human, axial, and anatomyosteologyaxialskeleton)" << endl;
	cout << "This query tests that result OR with skull and bodi" << endl;
	cout << "This query tests that result NOT with consist" << endl;
	cout << "The results should be 1481603, 1, 1481699, 1, 1481600, 1." << endl;
	cout << endl;

	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	query = "AND human anatomyosteologyaxialskeleton axial OR skull bodi NOT consist hyoid";

	cout << "Query Test 6" << endl;
	cout << "This query tests AND of three words (human, axial, and anatomyosteologyaxialskeleton)" << endl;
	cout << "This query tests that result OR with skull and bodi" << endl;
	cout << "This query tests that result NOT with consist and hyoid" << endl;
	cout << "The results should be 1481699, 1, 1481600, 1." << endl;
	cout << endl;

	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	cout << "    These next 6 tests should all have the same results as test 6, but we are " << endl;
	cout << "listing the query in a different order." << endl;

	cout << "Query Test 7" << endl;
	query = "AND anatomyosteologyaxialskeleton human axial OR bodi skull NOT hyoid consist";
	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	cout << "Query Test 8" << endl;
	query = "OR skull bodi AND human anatomyosteologyaxialskeleton axial NOT consist hyoid";
	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	cout << "Query Test 9" << endl;
	query = "OR skull bodi NOT consist hyoid AND human anatomyosteologyaxialskeleton axial";
	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	cout << "Query Test 10" << endl;
	query = "AND human anatomyosteologyaxialskeleton axial NOT consist hyoid OR skull bodi";
	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	cout << "Query Test 11" << endl;
	query = "NOT consist hyoid AND human anatomyosteologyaxialskeleton axial OR skull bodi";
	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	cout << "Query Test 12" << endl;
	query = "NOT consist hyoid OR skull bodi AND human anatomyosteologyaxialskeleton axial";
	AVLTestIF->setResultsFromBoolean(query);
	AVLTestIF->printResults();

	cout << endl;
	cout << endl;
	cout << "--------------------------------------------------------------------" << endl;
	cout << endl;
	cout << endl;

	cout << "Now I wanna test my Hash Interface's ability to only get results from our query" << endl;

	query = "AND human axial";

	cout << "Query Test 1" << endl;
	cout << "This query tests AND of two words (human and axial)" << endl;
	cout << "The results should be 1481605, 2 and 1485605,2" << endl;
	cout << endl;

	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	query = "AND human anatomyosteologyaxialskeleton axial";

	cout << "Query Test 2" << endl;
	cout << "This query tests AND of three words (human, axial, and anatomyosteologyaxialskeleton)" << endl;
	cout << "The results should be 1481605, 2." << endl;
	cout << endl;

	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	query = "AND human anatomyosteologyaxialskeleton axial OR skull";

	cout << "Query Test 3" << endl;
	cout << "This query tests AND of three words (human, axial, and anatomyosteologyaxialskeleton)" << endl;
	cout << "This query tests that result OR with skull" << endl;
	cout << "The results should be 1481605, 2, 1481699, 1, 1481600, 1." << endl;
	cout << endl;

	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	query = "AND human anatomyosteologyaxialskeleton axial OR skull bodi";

	cout << "Query Test 4" << endl;
	cout << "This query tests AND of three words (human, axial, and anatomyosteologyaxialskeleton)" << endl;
	cout << "This query tests that result OR with skull and bodi" << endl;
	cout << "The results should be 1481603, 1, 1481601, 1, 1481605, 2, 1481699, 1, 1481600, 1." << endl;
	cout << endl;

	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	query = "AND human anatomyosteologyaxialskeleton axial OR skull bodi NOT consist";

	cout << "Query Test 5" << endl;
	cout << "This query tests AND of three words (human, axial, and anatomyosteologyaxialskeleton)" << endl;
	cout << "This query tests that result OR with skull and bodi" << endl;
	cout << "This query tests that result NOT with consist" << endl;
	cout << "The results should be 1481603, 1, 1481699, 1, 1481600, 1." << endl;
	cout << endl;

	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	query = "AND human anatomyosteologyaxialskeleton axial OR skull bodi NOT consist hyoid";

	cout << "Query Test 6" << endl;
	cout << "This query tests AND of three words (human, axial, and anatomyosteologyaxialskeleton)" << endl;
	cout << "This query tests that result OR with skull and bodi" << endl;
	cout << "This query tests that result NOT with consist and hyoid" << endl;
	cout << "The results should be 1481699, 1, 1481600, 1." << endl;
	cout << endl;

	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	cout << "    These next 6 tests should all have the same results as test 6, but we are " << endl;
	cout << "listing the query in a different order." << endl;

	cout << "Query Test 7" << endl;
	query = "AND anatomyosteologyaxialskeleton human axial OR bodi skull NOT hyoid consist";
	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	cout << "Query Test 8" << endl;
	query = "OR skull bodi AND human anatomyosteologyaxialskeleton axial NOT consist hyoid";
	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	cout << "Query Test 9" << endl;
	query = "OR skull bodi NOT consist hyoid AND human anatomyosteologyaxialskeleton axial";
	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	cout << "Query Test 10" << endl;
	query = "AND human anatomyosteologyaxialskeleton axial NOT consist hyoid OR skull bodi";
	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	cout << "Query Test 11" << endl;
	query = "NOT consist hyoid AND human anatomyosteologyaxialskeleton axial OR skull bodi";
	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();

	cout << "Query Test 12" << endl;
	query = "NOT consist hyoid OR skull bodi AND human anatomyosteologyaxialskeleton axial";
	HashTestIF->setResultsFromBoolean(query);
	HashTestIF->printResults();


	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------------------" << endl;

	cout << "TEST RESULTS RANKING SYSTEM" << endl;
	cout << endl;
	cout << endl;

	IndexIF * hashRanksTester = new HashIF();
	IndexIF * avlRanksTester = new AVLIF();

	filepath = "/home/tgjackson/workspace/FinalProjectDSRepo/rankedResultsTesterIndex.txt";
	hashRanksTester->index(filepath);
	hashRanksTester->print();
	cout << "Ranked Query Test 1" << endl;
	query = "AND apple cherry";
	hashRanksTester->setResultsFromBoolean(query);
	hashRanksTester->printRankedResults();

	cout << "Ranked Query Test 2" << endl;
	query = "AND apple banana";
	hashRanksTester->setResultsFromBoolean(query);
	hashRanksTester->printRankedResults();

	cout << "Ranked Query Test 3" << endl;
	query = "AND apple banana cherry";
	hashRanksTester->setResultsFromBoolean(query);
	hashRanksTester->printRankedResults();

	cout << "Ranked Query Test 4" << endl;
	query = "AND apple";
	hashRanksTester->setResultsFromBoolean(query);
	hashRanksTester->printRankedResults();


	return 0;
}
