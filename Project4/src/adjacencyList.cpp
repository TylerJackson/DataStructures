/*
 * adjacencyList.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: tgjackson
 */

#include "adjacencyList.h"
#include <cstdio>
#include <iostream>
using namespace std;

adjacencyList::adjacencyList(){
	head=0;
	tail=0;
	current=0;
}
adjacencyList::adjacencyList(sourceNode* tempHead) {
	head=tempHead;
	head->next=tempHead->next;
	head->name=tempHead->name;
	head->list=new LList(tempHead->list);
	tail=tempHead;
	tail->next=tempHead->next;
	tail->name=tempHead->name;
	tail->list=new LList(tempHead->list);
	current=tempHead;
	current->next=tempHead->next;
	current->name=tempHead->name;
	current->list=new LList(tempHead->list);

}

adjacencyList& adjacencyList::operator =(const adjacencyList& rhs) {
	if(this != &rhs){
		if(this->head!=0){
			delete this->head;
		}
		if(this->tail!=0){
			delete this->tail;
		}
		if(this->current!=0){
			delete this->current;
		}
	}
	this->head=rhs.head;
//	this->head->next=rhs.next;
//	this->head->name=rhs.name;
//	this->head->list=new LList(rhs->list);
	this->current=rhs.current;
//	this->current->next=rhs->next;
//	this->current->name=rhs->name;
//	this->current->list=new LList(rhs->list);
	this->tail=rhs.tail;
//	this->tail->next=rhs->next;
//	this->tail->name=rhs->name;
//	this->tail->list=new LList(rhs->list);
while(current!=0)
	return *this;

}

adjacencyList::adjacencyList(const adjacencyList& orig) {
	//set linked list name to the same name as orig.
	this->head = Clone(orig.head);
	this->tail=orig.tail;
	this->current=orig.current;
}

sourceNode* adjacencyList::Clone(sourceNode* list) {
	if(list == NULL) return NULL;

	sourceNode * result = new sourceNode;
	result->name = list->name;
	result->next = Clone(list->next);
	return result;
}

void adjacencyList::insertNode(sourceNode* addThis) {
	if(this->head == 0){
		this->head = addThis;
		this->tail = addThis;
		this->current=addThis;
	}else{
		this->tail->next = addThis;
		this->tail = addThis;

	}
}
void adjacencyList::addCityToSource(cityNode * rhs,string sourceName){
	bool b=true;
	while(current!= 0 && b){
		if(current->list->getSourceCity() == sourceName){
			if(current->list->getHead()!=0){
				LList * temp=new LList(current->list->getHead(),current->list->getSourceCity());
				temp->insertNode(rhs);
				current->list=temp;
				b= false;
			}else{
				LList * temp= new LList(current->list->getSourceCity());
				temp->insertNode(rhs);
				current->list=temp;
				b= false;
			}

		}else
			current=current->next;
	}
	current=head;
}

bool adjacencyList::isUniqueSource(string sourceName){
	bool b=true;
	while(current!=0){
			if(current->list->getSourceCity() == sourceName)
				return false;
			current=current->next;
	}
	current=head;
	return true;
}
sourceNode*& adjacencyList::getHead(){
	return this->head;
}
void adjacencyList::calcFlightPlan(string sourceCity,string destCity){
	stack firstStack;
	string localSource=sourceCity;
	while(current!=0){
		if(current->list->getSourceCity() == localSource){
			 if(current->list->getPlace()!=0){
				stackNode * nodeToAdd=new stackNode (current->list->getPlace());
				firstStack.push(nodeToAdd);
				if(firstStack.top1()->data->name == destCity){
					for(int i=0;i<firstStack.count();i++){
						cout<<"Leg "<<i+1<<": "<<firstStack.pop().data->name<<endl;
					}
					current=0;
				}else{
					localSource= firstStack.top1()->data->name;
					current=head;

				}
			 }else{
				 firstStack.pop();
				 current->list->setPlace(firstStack.top1()->data->next);
			 }
		}else{
			current=current->next;
		}
	}
}


void adjacencyList::printAdjacencyList() {
	//print name of source city
	if(this->head==0){
	cout<<"    I have no source cities."<<endl;
	}else{
		sourceNode * temp;
		temp=this->head;
		while(temp != 0){
			temp->list->printLList();
			temp=temp->next;
		}
	}
}

adjacencyList::~adjacencyList() {
}
