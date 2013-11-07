/* Tyler Jackson
 * 11/4/2013
 *
 * LList.h
 * 		This class is a linked list of city nodes.  Similarly to my adjacency List class, the linked
 * 		list class has 3 data members.  A city node pointer to the head of the list, to the tail,
 * 		and one pointing to the current spot in the list.  The pointer to the current spot in the list
 * 		is called place.  The LList object also has a private string object called sourceCity that
 * 		represents the departure city from which these destination nodes are connected to.
 *
 * 	City Nodes
 * 		Each city node represents a destination from the sourceCity of the linked List.
 * 		It there has a cost data member, and also a next cityNode pointer that points to the
 * 		next node in the LList.The cityNodes also have a string object 'name' that refers to the
 * 		destination city's name
 *
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
	LList():head(NULL),tail(NULL){
		place=NULL;
	}
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
	bool isLeaf(cityNode * end);
	void setPlace(cityNode * placeTemp);
	bool isEmpty();

	void printLList();
	//cityNode *head;
	//cityNode *tail;
	virtual ~LList();
	cityNode * place;

private:
	string sourceCity;
	cityNode * head;
	cityNode * tail;

};


#endif /* LLIST_H_ */
