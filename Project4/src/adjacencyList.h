/*
 * adjacencyList.h
 *
 *  Created on: Oct 28, 2013
 *      Author: tgjackson
 */

#ifndef ADJACENCYLIST_H_
#define ADJACENCYLIST_H_
#include "LList.h"
#include "stack.h"

using namespace std;

struct sourceNode{
	string name;
	sourceNode * next;
	LList* list;
	sourceNode(){
		name="";
		next=0;
		list=0;
	}
	sourceNode(sourceNode * temp){
		name=temp->name;
		next=temp->next;
		list=new LList(temp->list);
	}
	sourceNode& operator=(const sourceNode& rhs){
		if(this != &rhs){
			if(this->next!=0){
				delete this->next;
			}
			if(this->list!=0){
				delete this->list;
			}
		}
		this->next=rhs.next;
		this->list=new LList(rhs.list);
		this->name=rhs.name;
		return *this;
	}

	sourceNode(LList tempHead){
		name="";
		next=0;
		list=new LList(tempHead);
	}
	sourceNode (string cityName){
		name = cityName;
		next = 0;
		list=0;
	}

};
class adjacencyList {
public:
	adjacencyList();
	adjacencyList (sourceNode * tempHead);
	adjacencyList& operator=(const adjacencyList& rhs);
	adjacencyList (const adjacencyList& orig);
	sourceNode* Clone(sourceNode * list);
	sourceNode*&  getHead();
	void addCityToSource(cityNode * rhs,string sourceName);
	void insertNode(sourceNode * addThis);
	bool isUniqueSource(string sourceName);
	void printAdjacencyList();
	void calcFlightPlan(string sourceCity,string destCity);
	virtual ~adjacencyList();

private:
	sourceNode * head;
	sourceNode * current;
	sourceNode * tail;
};

#endif /* ADJACENCYLIST_H_ */
