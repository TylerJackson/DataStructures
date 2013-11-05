/*
 * flightPath.h
 *
 *  Created on: Nov 4, 2013
 *      Author: tgjackson
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
	void calcFlightPlan(string sourceCity,string destCity);
	void processPossibles();
	virtual ~flightPath();
private:
	char * possibleRoutesFile;
	char * routesToCalculateFile;
	char * outputFile;
	adjacencyList * mainList;

};

#endif /* FLIGHTPATH_H_ */
