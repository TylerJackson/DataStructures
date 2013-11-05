/*
 * flightPath.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: tgjackson
 */

#include "flightPath.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
flightPath::flightPath() {
	possibleRoutesFile=0;
	routesToCalculateFile=0;
	outputFile=0;
	mainList= new adjacencyList;

}
flightPath::flightPath(const char * possibleRoutes,const char * routesToCalculate,const char * output){
	possibleRoutesFile = new char [strlen(possibleRoutes)+1];
	strcpy(possibleRoutesFile,possibleRoutes);
	routesToCalculateFile = new char [strlen(routesToCalculate)+1];
	strcpy(routesToCalculateFile,routesToCalculate);
	outputFile = new char [strlen(output)+1];
	strcpy(outputFile,output);
	mainList=new adjacencyList;
}

void flightPath::processPossibles(){
	ifstream fin;
	fin.open(possibleRoutesFile);
	if(fin.is_open()){
	//	cout<<"OPEN"<<endl;
	}
	//get number of routes
	int numRoutes;
	fin>>numRoutes;

	//move fin down to first path
	char * buffer=new char[80];
	fin.getline(buffer,80);

	int numPaths=0;
	while(!fin.eof()){
		fin.getline(buffer,80);

		//get first comma index
		int commaIndex=0;
		while(buffer[commaIndex]!=','){
			commaIndex++;
		}

		//store source city into sourceTemp1 as a string
		char * sourceTemp=new char [commaIndex];
		for(int i=0;i<commaIndex;i++){
			sourceTemp[i]=buffer[i];
		}
		//cout<<sourceTemp<<endl;
		string sourceTemp1=sourceTemp;

		//add this source city as a new sourceNode(with a linked list if it doesn't already exist
		//if it already exists do nothing
		if(mainList->isUniqueSource(sourceTemp1)){
			LList temp(sourceTemp1);
			sourceNode * nodeToAdd=new sourceNode (temp);
			mainList->insertNode(nodeToAdd);
		}

		//get second comma index
		int commaIndex1=commaIndex;
		commaIndex++;
		while(buffer[commaIndex]!=','){
			commaIndex++;
		}

		//store destination city into the destTemp1
		char * destTemp=new char [commaIndex-commaIndex1-2];
		for(int i=commaIndex1+2;i<commaIndex;i++){
			destTemp[i-commaIndex1-2]=buffer[i];
		}
		//cout<<destTemp<<endl;
		string destTemp1=destTemp;

		//get end of line whitespace index
		int spaceIndex=commaIndex+2;
		int commaIndex2=spaceIndex;
		while(buffer[spaceIndex]!= ' '){
			spaceIndex++;
		}


		//store cost of this leg into legCost
		char * tempCost=new char[spaceIndex-commaIndex2];
		for(int i=commaIndex2;i<spaceIndex;i++){
			tempCost[i-commaIndex2]=buffer[i];
		}
		double legCost=atof(tempCost);
		//cout<<legCost<<endl;
		//cout<<endl;

		//add this cityNode to the correct spot on the adjacencyList
		cityNode * tempCity=new cityNode(destTemp1,legCost);
		mainList->addCityToSource(tempCity,sourceTemp1);
		numPaths++;
	}
	mainList->printAdjacencyList();
	cout<<endl;
	cout<<"THE TOTAL NUMBER OF PATHS WAS: "<<numPaths<<"."<<endl;


}

void flightPath::calcFlightPlan(string sourceCity,string destCity){

}


flightPath::~flightPath() {
	// TODO Auto-generated destructor stub
}

