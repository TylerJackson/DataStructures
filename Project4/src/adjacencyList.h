/*
 * adjacencyList.h
 *
 *  Created on: Oct 28, 2013
 *      Author: tgjackson
 */

#ifndef ADJACENCYLIST_H_
#define ADJACENCYLIST_H_

using namespace std;

class adjacencyList {
public:
	adjacencyList();
	adjacencyList& operator=(const adjacencyList& rhs);
	adjacencyList (const adjacencyList& orig);
	void addLList(LList addThis);
	void printAdjacencyList();
	virtual ~adjacencyList();

private:
	LList * flightPath;
};

#endif /* ADJACENCYLIST_H_ */
