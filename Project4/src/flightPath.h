/* Tyler Jackson
 * 11/4/2013
 *
 * flightPath.h holds all the declarations for my flight path functions.
 * My flight path object is the object I use to parse in the files, and the file in which I call
 * my calculate path function, and print the result to the file.  It is constructed using the three
 * command line arguments as parameters which are then stored as private string objects.  These are used
 * later to read/write to files.
 *
 * Each flight path object also has a private adjacency list pointer that points to the adjacency list
 * created from reading in from the file
 *
 */

#ifndef FLIGHTPATH_H_
#define FLIGHTPATH_H_
#include "adjacencyList.h"
#include "stack.h"
using namespace std;

class flightPath {
public:
	flightPath();
	flightPath(const char * possibleRoutes,const char * routesToCalc, const char * output);
	void calcFlightPlans();
	void processPossibles();
	virtual ~flightPath();
private:
	char * possibleRoutesFile;
	char * routesToCalculateFile;
	char * outputFile;
	adjacencyList * mainList;

};

#endif /* FLIGHTPATH_H_ */
