/*Tyler Jackson
 * 11/4/2013
 *
 *  stack.cpp
 *  This class implements all the functions from my stack.h
 */

#include "stack.h"
#include <iostream>

using namespace std;
stack::stack() {
	top=0;
	counter=0;
}

stack::~stack() {

}

void stack::push(stackNode* nodeToAdd) {
	if(counter==0){
		top=nodeToAdd;
		top->next=0;
		counter++;
	}else{
		nodeToAdd->next=top;
		top=nodeToAdd;
		counter++;
	}
}

string stack::pop() {
	counter--;
	stackNode * temp;
	temp=top;
	top->isBad = true;
	string s=temp->name;
	top=temp->next;

	return s;

}
bool stack::has(cityNode * poss){
	stackNode * iter=top;
	//cout << "poss name: " << poss->name << endl;
	while(iter != 0 ){
		if(iter->data != 0){
			//cout  << "B:" <<  iter->data->name << "==" << poss->name << endl;
			if(iter->data->name == poss->name){
				return true;
			}
		}else{
			//cout << "A:" << iter->srcNode->list->getSourceCity();
			//cout << "==" << poss->name << endl;
			if(iter->getName() == poss->name){

				return true;
			}
		}
		iter=iter->next;
	}
	return false;
}
bool stack::has(sourceNode * poss){
	stackNode * iter=top;
	while(iter != 0 ){
		if(iter->name == poss->list->getSourceCity()){
			return true;
		}
		iter=iter->next;
	}
	return false;
}
stack stack::getGood(stackNode * top, int count){
	stack temp;
	temp.printStack(top,count);
	return temp;

}
void stack::printStack(stackNode * top,int count){
	printStackItems(top,count);
	double totCost=0;
	stackNode * iter;
	iter=this->top;
	while(iter->next!=0){
		if(!iter->isBad)
			totCost+=iter->cost;
		iter=iter->next;
	}
	cout<<"Total Cost: $"<<totCost<<endl;
}
void stack::printStackFile(stackNode * top,int count,char * fileName){
	ofstream fout;
	fout.open(fileName,ios::app);
	printStackItemsFile(top,count,fileName);
	double totCost=0;
	stackNode * iter;
	iter=this->top;
	while(iter->next!=0){
		if(!iter->isBad)
			totCost+=iter->cost;
		iter=iter->next;
	}
	fout<<"Total Cost: $"<<totCost<<endl;
	fout.close();
}
void stack::printStackItems(stackNode * top,int count){
	if(top->next!=0){
		if(top->next->isBad==true)
			printStackItems(top->next,count);
		else
			printStackItems(top->next,count-1);
	}
	if(top->isBad == false && top->startLeg != top->getName()){
		cout<<"Leg "<<count-1<<": "<<top->startLeg<<" to "<<top->getName()<<" $"<<top->cost<<endl;

	}
}
void stack::printStackItemsFile(stackNode * top,int count, char * fileName){
	ofstream fout;
	fout.open(fileName,ios::app);
	if(top->next!=0){
		if(top->next->isBad==true)
			printStackItemsFile(top->next,count,fileName);
		else
			printStackItemsFile(top->next,count-1,fileName);
	}
	if(top->isBad == false && top->startLeg != top->getName()){
		fout<<"Leg "<<count-1<<": "<<top->startLeg<<" to "<<top->getName()<<" $"<<top->cost<<endl;

	}
	fout.close();
}

stackNode* stack::top1(){
	return top;
}

void stack::clear() {
	//while
}

bool stack::isEmpty() {
	if(this->counter == 0)
		return true;
	return false;
//	if(top == 0){
//		return true;
//	}
//	while(top->isBad == true || top->next == 0){
//		this->top=this->top->next;
//	}
//	return false;
}

int stack::count() const {
	return counter;
}

