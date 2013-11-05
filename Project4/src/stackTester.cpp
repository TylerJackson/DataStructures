/*
 * stackTester.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: tgjackson
 */

#include <iostream>
#include "stack.h"
using namespace std;

int main(){
		//test adjacency lists constructors
		LList firstList("Phoenix");
		LList secondList("Las Vegas");
		LList thirdList("New York City");
		LList fourthList("Denver");

		cityNode * firstNode=new cityNode("Denver",500);
		cityNode * secondNode=new cityNode("New York City",250);
		cityNode * thirdNode=new cityNode("Las Vegas",500);
		cityNode * fourthNode=new cityNode("Orlando",250);
		cityNode * lastNode=new cityNode("Mexico City",1500);

		firstList.insertNode(firstNode);
		firstList.insertNode(secondNode);
		secondList.insertNode(fourthNode);
		secondList.insertNode(firstNode);
		thirdList.insertNode(thirdNode);
		thirdList.insertNode(firstNode);
		fourthList.insertNode(lastNode);





	sourceNode * node1Adj=new sourceNode(firstList);
	sourceNode * node2Adj=new sourceNode(secondList);
	sourceNode * node3Adj=new sourceNode(thirdList);
	sourceNode * node4Adj=new sourceNode(fourthList);

	adjacencyList tester1;
	tester1.insertNode(node1Adj);
	tester1.insertNode(node2Adj);
	tester1.insertNode(node3Adj);
	tester1.insertNode(node4Adj);


	tester1.printAdjacencyList();

	tester1.calcFlightPlan("Phoenix","Las Vegas");
	return 0;
}







