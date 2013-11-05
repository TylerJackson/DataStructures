/*	Tyler Jackson
	This is my tester class for my linked lists and adjacency lists
	Oct. 25 2013

*/

#include <iostream>
#include "adjacencyList.h"

using namespace std;

int main(){
	//test linked lists constructors
	LList firstList("Phoenix");
	LList secondList("Las Vegas");

	cityNode * firstNode=new cityNode("Denver",500);
	cityNode * secondNode=new cityNode("LA",250);

	firstList.insertNode(firstNode);
	firstList.insertNode(secondNode);

	firstList.printLList();
	secondList.printLList();

	LList copyFirst(firstList);
	LList copyFirst2=firstList;

	copyFirst.printLList();
	copyFirst2.printLList();

	cout<<"should be Phoenix: "<<firstList.getSourceCity()<<endl;
	cout<<"should be Denver: "<<firstList.getHead()->name<<endl;
	return 0;
}



