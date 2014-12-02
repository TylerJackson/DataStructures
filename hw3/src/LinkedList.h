/*
 * LinkedList.h
 *
 *  Created on: Nov 3, 2013
 *      Author: tgjackson
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <cstdlib>
using namespace std;

class LinkedList {
public:
	LinkedList();
	//void insertNode(node * temp);
	virtual ~LinkedList();

private:
	struct node{
		int * val;
		node *next;
	};
	node *head;
};

#endif /* LINKEDLIST_H_ */
