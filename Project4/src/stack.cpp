/*
 * stack.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: tgjackson
 */

#include "stack.h"


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

stackNode& stack::pop() {
	counter--;
	stackNode * temp=new stackNode();
	temp=top;
	stackNode gonnaReturn(temp->data);
	top=top->next;
	delete temp;
	return gonnaReturn;
}

stackNode* stack::top1(){
	return top;
}

void stack::clear() {
	//while
}

bool stack::isEmpty() {
	if(top == 0){
		return true;
	}
	else return false;
}

int stack::count() const {
	return counter;
}

