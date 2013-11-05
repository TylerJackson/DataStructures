/*
 * stack.h
 *
 *  Created on: Nov 4, 2013
 *      Author: tgjackson
 */

#ifndef STACK_H_
#define STACK_H_
#include "adjacencyList.h"
using namespace std;

struct stackNode{
	cityNode * data;
	stackNode * next;

	stackNode(){
		next=0;
		data=0;
	}
	stackNode(cityNode * node){
		next=0;
		data=node;
		data->next=node->next;
		data->cost=node->cost;
		data->name=node->name;
	}


};

class stack {
public:
	stack();
	virtual ~stack();
	void push(stackNode * nodeToAdd);
	stackNode& pop();
	stackNode* top1();
	void clear();
	bool isEmpty();
	bool isFull();
	int count() const;

private:
	stackNode * top;
	int counter;
};

#endif /* STACK_H_ */
