/*	Tyler Jackson
	This is my tester class for my adjacency lists
	Oct. 25 2013

*/

#include <iostream>
#include "adjacencyList.h"

using namespace std;

int main(){
		//test adjacency lists constructors
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

	sourceNode * node1Adj=new sourceNode(firstList);
	sourceNode * node2Adj=new sourceNode(secondList);
	sourceNode * node3Adj=new sourceNode(copyFirst);
	sourceNode * node4Adj=new sourceNode(copyFirst2);
	sourceNode * node5Adj=new sourceNode(firstList);

	cout<<"should be Phoenix: "<<node1Adj->list->getSourceCity()<<endl;
	cout<<"should be Denver: "<<node1Adj->list->getHead()->name<<endl;
	cout<<endl;
	adjacencyList tester1;
	tester1.insertNode(node1Adj);
	tester1.insertNode(node2Adj);
	tester1.insertNode(node3Adj);
	if(tester1.isUniqueSource(node5Adj->list->getSourceCity())){
		cout<<"I am incorrectly adding this: "<<endl;
		tester1.insertNode(node5Adj);
	}else{
		cout<<"It shouldn't add the last one because it isn't unique"<<endl;
	}

	//add city to a source
	cout<<"Now I am going to add this new city to a source"<<endl;
	cityNode * lastNode=new cityNode("Mexico City",1500);
	tester1.addCityToSource(lastNode,"Las Vegas");
	tester1.addCityToSource(lastNode,"Phoenix");

	tester1.printAdjacencyList();

	return 0;
}
