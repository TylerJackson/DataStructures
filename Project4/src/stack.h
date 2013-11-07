/* Tyler Jackson
 * 11/4/2013
 *
 * stack.h
 * 	This file contains all my declarations for my stack object.
 * 		My stack object is what I used for my LIFO iterative backtracking algorithm.
 * 		Each stack is made up of stackNodes, as well as a stackNode pointer referring to the
 * 		top of the stack, or the last node added.
 *
 * 		stackNodes
 * 			Each stack node contains a cityNode * object and a sourceNode * object
 * 			That way I could in theory push a stack node initialized with either type of
 * 			object to the stack.  Its stackNode * next data member points to the next stackNode on
 * 			the stack, or the node that had been added one prior to our current node.
 * 			It also has a string object startLeg that refers to the sourceCity that a cityNode
 * 			came from.  Is bad is a bool I created to make my code more robust, as a second check
 * 			to make sure I didn't iterate over a node twice in my iterative backtracking.
 * 			Once I iterated over a node I would set the isBad flag to true, so I would know to skip
 * 			it if need be.  the double cost object is if the stackNode contains a cityNode object.
 * 			It refers to the associated cost to travel to that city Node from its particular departure
 * 			city at the time.
 *
 */

#ifndef STACK_H_
#define STACK_H_
#include "adjacencyList.h"
#include <fstream>
using namespace std;

struct stackNode{
	cityNode * data;
	stackNode * next;
	sourceNode *srcNode;
	string name;
	bool isBad;
	string startLeg;
	double cost;
	stackNode(){
		next=0;
		data=0;
		srcNode=0;
		name="butthead";
		isBad = false;
		startLeg="";
		cost=0;
	}
	stackNode(cityNode * node){
		next=0;
		data=node;
		srcNode=0;
		name=node->name;
		isBad = false;
		startLeg="";
		cost=node->cost;

	}
	stackNode(sourceNode * node){
		next=0;
		srcNode=node;
		data=0;
		name=node->list->getSourceCity();
		isBad = false;
		startLeg="";
		cost=0;

	}
	stackNode(sourceNode * node,string sourceName1,double cost){
		next=0;
		srcNode=node;
		data=0;
		name=node->list->getSourceCity();
		isBad = false;
		startLeg=sourceName1;
		this->cost=cost;
	}

	string getName(){
		if(data==0)
			return srcNode->list->getSourceCity();
		return data->name;
	}
	bool isLeaf(){
		if(data==0){
			if(srcNode->list->isEmpty())
				return true;
		}else{
			if(data->next==0)
				return true;
		}
		return false;
	}



};

class stack {
public:
	stack();
	virtual ~stack();
	void push(stackNode * nodeToAdd);
	string pop();
	stackNode* top1();
	bool has(cityNode * poss);
	bool has(sourceNode * poss);
	void clear();
	bool isEmpty();
	bool isFull();
	int count() const;
	stackNode * top;
	void printStack(stackNode * recur, int count);
	void printStackItems(stackNode * recur, int count);
	void printStackFile(stackNode * recur, int count,char * fileName);
	void printStackItemsFile(stackNode * recur, int count,char * fileName);

	stack getGood(stackNode * top, int count);
	//stackNode * printHelper(stackNode * recur, int count);
private:
	int counter;

};

#endif /* STACK_H_ */
