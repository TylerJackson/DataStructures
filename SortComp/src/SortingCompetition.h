/*
 * SortingCompetition.h
 *
 *  Created on: Oct 3, 2013
 *      Author: tgjackson
 */

#ifndef SORTINGCOMPETITION_H_
#define SORTINGCOMPETITION_H_
#include <string>
#include <vector>
using namespace std;

class SortingCompetition {
	private:

	char ** textFileCharStar;
	char ** charStarCopyToBeSorted;
	string * textFileString;
	vector<char> * textFileVector;
	string textFile;
	int numWordsCharStar;
	int numSpaceCharStar;
	//you are free to determine your own internal
	//implementation with the following stipulations:
	//1) when the prepare method is called, you must make a
	//copy of the original dataset into another instance-level
	//data structure which will be used by the sort method. This will
	//allow for multiple executions of the sort method in order to
	//get better timing data.
	//2) your data structure must be linear (no trees).
	public:
	SortingCompetition();
	~SortingCompetition();
	//basic constructor that accepts an input
	//file name
	SortingCompetition(const string& inputFileName);
	//change the input file name
	void setFileName(const string& inputFileName);
	//read the data from the file and store it in
	//a linear data structure.
	//No sorting actions can be done in this method.
	bool readData();
	//copy the data from the original data structure
	//into a second location that will be used for sorting.
	//No sorting actions can be done in this method.
	bool prepareData();
	//sort the data based on the criteria set forth in the
	//hand out.
	//THIS IS THE FUNCTION THAT WILL BE TIMED.
	void sortData();
	//using outputFileName, write the "sorted" data structure
	//to the file. This will be used to test the validity of
	//your sorting algorithm (did it sort properly).
	void outputData(const string& outputFileName);
	};
#endif /* SORTINGCOMPETITION_H_ */
