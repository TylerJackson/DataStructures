/*Tyler Jackson
 * 11/4/2013
 * adjacencyList.h
 *
 *	This class holds my adjacency list declarations and private data
 *
 *	Each adjacency list is made up of sourceNodes.  Each list has a sourceNode * that
 *	points to the head of the list, the tail of the list, and a current sourceNode *.
 *	The current pointer is for when I want to iterate through my adjacency list.
 *
 *	SourceNodes
 *		Each source node has a name, which refers to the name of the sourceCity.
 *		In regards to a flight path, each sourceNode should hold the name of the departure city
 *
 *		Each source node has a LList pointer which points to a linked list of my destination cities
 *		Each source node also has a next pointer that points to the next node in the adjacency list
 */


#ifndef ADJACENCYLIST_H_
#define ADJACENCYLIST_H_

#include "LList.h"

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

#include "stack.h"



class adjacencyList {
public:
	adjacencyList();
	adjacencyList (sourceNode * tempHead);
	adjacencyList& operator=(const adjacencyList& rhs);
	adjacencyList (const adjacencyList& orig);
	sourceNode* Clone(sourceNode * list);
	sourceNode* getSourceNode(string sourceName);
	sourceNode*&  getHead();
	void addCityToSource(cityNode * rhs,string sourceName);
	void insertNode(sourceNode * addThis);
	bool isUniqueSource(string sourceName);
	void printAdjacencyList();
	void calcFlightPlan(string sourceCity,string destCity);
	void calcFlightPlanFile(string sourceCity,string destCity, char * fileName);
	virtual ~adjacencyList();

private:
	sourceNode * head;
	sourceNode * current;
	sourceNode * tail;
};

#endif /* ADJACENCYLIST_H_ */
