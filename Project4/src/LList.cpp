/*	Tyler Jackson
 * 11/4/2013
 *
 * LList.cpp
 * 	This class implements all the functions from the LList.h
 *
 */

#include "LList.h"
#include <iostream>
#include <string>
using namespace std;

LList::LList(cityNode * tempHead,string sourceName){
	insertNode(tempHead);
	while(tempHead->next!=0){
		insertNode(tempHead->next);
		tempHead=tempHead->next;
	}
	sourceCity=sourceName;
}
LList::LList(string sourceName){
	head=0;
	tail=0;
	place=0;
	sourceCity=sourceName;
}

bool LList::isLeaf(cityNode * end){
	if(end->next == 0)
		return true;
	else
		return false;
}

bool LList::isEmpty(){
	if(head == 0)
		return true;
	else
		return false;
}

LList& LList::operator =(const LList& rhs) {
	//deletes lhs if it doesn't equal rhs
	//makes sure to only delete the private data that was not initialized to null
	if(this != &rhs){
		if(this->head!=0){
			delete this->head;
		}
		if(this->tail!=0){
			delete this->tail;
		}
	}
	this->head=rhs.head;
	this->head->next=rhs.head->next;
	this->head->name=rhs.head->name;
	this->head->cost=rhs.head->cost;

	this->place=rhs.place;
	this->place->next=rhs.place->next;
	this->place->name=rhs.place->name;
	this->place->cost=rhs.place->cost;

	this->tail=rhs.tail;
	this->tail->next=rhs.tail->next;
	this->tail->name=rhs.tail->name;
	this->tail->cost=rhs.tail->cost;

	this->sourceCity=rhs.sourceCity;
	return *this;

}


LList::LList(const LList& orig) {
	//set linked list name to the same name as orig.
	this->sourceCity=orig.sourceCity;
	this->head = Clone(orig.head);
	this->tail=orig.tail;
	this->place=orig.head;
}
LList::LList(const LList* orig) {
	//set linked list name to the same name as orig.
	this->sourceCity=orig->sourceCity;
	this->head = Clone(orig->head);
	this->tail = orig->tail;
	this->place=orig->place;
}


void LList::insertNode(cityNode * addThis) {
	if(this->head == 0){
		this->head = addThis;
		this->place = addThis;
		this->tail = addThis;
	}else{
		this->tail->next = addThis;
		this->tail = addThis;

	}
}
cityNode* LList::getHead(){
	return this->head;
}
cityNode* LList::getPlace(){
	return this->place;
}
void LList::setPlace(cityNode * placeTemp){
	place=placeTemp;
	place->next=placeTemp->next;
	place->cost=placeTemp->cost;
	place->name=placeTemp->name;
}

string LList::getSourceCity(){
	return sourceCity;
}

void LList::printLList() {
	//print name of source city
	cout<<"The name of the Source City is: "<<sourceCity<<endl;
	if(head!=0){
		cout<<"    My destination cities are: "<<endl;
	}
	else{
		cout<<"    I have no destination cities."<<endl;
	}
	cityNode * temp=head;
	int countCities=1;
	int alignText=0;
	while(temp != 0){
		alignText=temp->name.length();
		cout<<"         "<<countCities<<"). "<<temp->name<<" ";
		while(alignText!=20){
			cout<<"-";
			alignText++;
		}
		cout<<" cost = $"<<temp->cost<<endl;
		temp=temp->next;
		countCities++;
		alignText=0;
	}
}
cityNode* LList::Clone(cityNode* list){
	if(list == NULL) return NULL;

	cityNode * result = new cityNode;
	result->cost = list->cost;
	result->name = list->name;
	result->next = Clone(list->next);
	return result;
}


LList::~LList() {
	// TODO Auto-generated destructor stub
}

