/*Tyler Jackson
 * 11/4/2013
 * adjacencyList.cpp
 *
 *This class implements my adjacency list functions described in adjacencyList.h
 */

#include "adjacencyList.h"
#include <cstdio>
#include <iostream>
#include <fstream>
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
	this->current=rhs.current;
	this->tail=rhs.tail;
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
	bool doesntExist=true;
	stack fp;
	stack bd;
	//cout<<"bals"<<endl;
	stackNode * pushIt;
	pushIt = new stackNode(this->getSourceNode(sourceCity),sourceCity,0);
	//cout<<"ack"<<endl;
	//return;
	fp.push(pushIt);
	//cout<<"I just pushed "<<fp.top->getName()<<endl;
	bd.push(pushIt);
	//cout<<"I just pushed this to bad list "<<bd.top->getName()<<endl;
	while(!fp.isEmpty())
	{
		//cout<<fp.top->getName()<<endl;
		if(fp.top->getName() == destCity) {
			cout<<"The flight path from "<<sourceCity<<" to "<<destCity<<" is: "<<endl;
			fp.printStack(fp.top,fp.count());
			doesntExist=false;
			break;
		}
		if(fp.top->isLeaf()){
			fp.pop();

		} else {
			while(bd.has(fp.top->srcNode->list->place)){
				if(fp.top->srcNode->list->place->next == NULL){
					fp.pop();
					if(!fp.isEmpty()){
						continue;
					}
					else{
						cout<<"The flight path from "<<sourceCity<<" to "<<destCity<<" is: "<<endl;
						cout<<"    No possible flight plans between these two cities"<<endl;
						return;
					}
				}
				fp.top->srcNode->list->place = fp.top->srcNode->list->place->next;
			}
			pushIt=new stackNode  (getSourceNode(fp.top->srcNode->list->place->name),fp.top->srcNode->list->getSourceCity(),fp.top->srcNode->list->place->cost);
			fp.push(pushIt);
			bd.push(pushIt);
		}
	}
	if(doesntExist){
		cout<<"The flight path from "<<sourceCity<<" to "<<destCity<<" is: "<<endl;
		cout<<"    No possible flight plans between these two cities"<<endl;
	}
}

void adjacencyList::calcFlightPlanFile(string sourceCity,string destCity,char * fileName){
	ofstream fout;
	fout.open(fileName,ios::app);

	bool doesntExist=true;
	stack fp;
	stack bd;
	stackNode * pushIt;
	pushIt = new stackNode(this->getSourceNode(sourceCity),sourceCity,0);
	fp.push(pushIt);
	bd.push(pushIt);
	while(!fp.isEmpty())
	{
		if(fp.top->getName() == destCity) {
			fp.printStackFile(fp.top,fp.count(),fileName);
			doesntExist=false;
			break;
		}
		if(fp.top->isLeaf()){
			fp.pop();

		} else {
			while(bd.has(fp.top->srcNode->list->place)){
				if(fp.top->srcNode->list->place->next == NULL){
					fp.pop();
					if(!fp.isEmpty()){
						continue;
					}
					else{
						fout<<"Flight Not Possible"<<endl;
						return;
					}
				}
				fp.top->srcNode->list->place = fp.top->srcNode->list->place->next;
			}
			pushIt=new stackNode  (getSourceNode(fp.top->srcNode->list->place->name),fp.top->srcNode->list->getSourceCity(),fp.top->srcNode->list->place->cost);
			fp.push(pushIt);
			bd.push(pushIt);
		}
	}
	if(doesntExist){
		fout<<"Flight Not Possible"<<endl;
	}
	fout.close();
}



sourceNode* adjacencyList::getSourceNode(string sourceName){
	sourceNode * temp = this->head;
	while(temp->list->getSourceCity() != sourceName){
		if(temp==tail){
			temp=0;
			break;
		}
		temp = temp->next;
	}
	if(temp==0){
		LList tempo(sourceName);
		temp=new sourceNode(tempo);
		this->insertNode(temp);
	}
	return temp;
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
