/*
 * main.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: tgjackson
 */
#include "flightPath.h"
#include <cstdlib>
#include <iostream>
int main(int argc, const char * argv[]){
	flightPath route(argv[1],argv[2],argv[3]);
	route.processPossibles();
	return 0;
}





