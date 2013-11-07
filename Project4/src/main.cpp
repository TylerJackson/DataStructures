/* Tyler Jackson
 * 11/4/2013
 * main.cpp
 *
 */
#include "flightPath.h"
#include <cstdlib>
#include <iostream>
int main(int argc, const char * argv[]){
	//This is my main routine for the project
	//	It creates a flight path object using the three command line arguments
	//		1. possible routes, 2. routes to calculate, 3. the output file to put the solution paths
	//  It then processes the possible outcomes, and the calculates the flight plans.


	flightPath route(argv[1],argv[2],argv[3]);
	route.processPossibles();
	route.calcFlightPlans();

	return 0;
}





