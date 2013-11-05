/*
 * LList.h
 *
 *  Created on: Oct 28, 2013
 *      Author: tgjackson
 */
#ifndef LLIST_H_
#define LLIST_H_
#include <cstdlib>
#include <string>

using namespace std;

struct cityNode{
	string name;
	cityNode * next;
	double cost;
	cityNode(){
		name="";
		next=0;
		cost=0;
	}
	cityNode (string cityName, cityNode * nextCity, double price){
		name = cityName;
		next = nextCity;
		cost = price;
	}
	cityNode (string cityName){
		name =cityName;
		next = NULL;
		cost = 0;
	}
	cityNode (string cityName, double costTemp){
		name =cityName;
		next = NULL;
		cost = costTemp;
	}

};


//cityNode* Clone(cityNode* list){
//	if(list == NULL) return NULL;
//
//	cityNode * result = new cityNode;
//	result->cost = list->cost;
//	result->name = list->name;
//	result->next = Clone(list->next);
//	return result;
//}


class LList {
public:
	LList():head(NULL),tail(NULL){}
	LList (cityNode * tempHead, string sourceName);
	LList (string tempSourceCity);
	LList& operator=(const LList& rhs);
	LList (const LList& orig);
	LList (const LList* orig);
	cityNode* Clone(cityNode * list);
	void insertNode(cityNode * addThis);
	cityNode* getHead();
	string getSourceCity();
	cityNode* getPlace();
	void setPlace(cityNode * placeTemp);

	void printLList();
	//cityNode *head;
	//cityNode *tail;
	virtual ~LList();

private:
	string sourceCity;
	cityNode * head;
	cityNode * tail;
	cityNode * place;

};


#endif /* LLIST_H_ */
