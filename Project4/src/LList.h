/*
 * LList.h
 *
 *  Created on: Oct 28, 2013
 *      Author: tgjackson
 */
#ifndef LLIST_H_
#define LLIST_H_
#include <cstdlib>

using namespace std;

struct cityNode{
	string name;
	cityNode * next;
	double cost;
	cityNode (string cityName, cityNode * nextCity, double price){
		name = cityName;
		next = nextCity;
		cost = price;
	}
	cityNode (string cityName){
		name =cityName;
		next = NULL;
		cost = NULL;
	}


};

class LList {
public:
	LList():head(NULL),tail(NULL){}
	LList& operator=(const LList& rhs);
	LList (const LList& orig);
	void insertNode(cityNode * addThis);
	void printLList();
	cityNode *head;
	cityNode *tail;
	virtual ~LList();
};


#endif /* LLIST_H_ */
