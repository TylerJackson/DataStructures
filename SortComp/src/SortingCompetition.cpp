/*
 * SortingCompetition.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: tgjackson
 */

#include "SortingCompetition.h"
#include <fstream>
#include <cstring>
#include <iostream>

SortingCompetition::SortingCompetition() {
	textFileCharStar=0;
	textFileString=0;
	textFileVector=0;
	textFile="";
	numWordsCharStar=0;
	charStarCopyToBeSorted=0;
	numSpaceCharStar=0;
}

SortingCompetition::~SortingCompetition() {
	// TODO Auto-generated destructor stub
}

SortingCompetition::SortingCompetition(const string& inputFileName) {
	textFile=inputFileName;
	textFileCharStar=0;
	textFileString=0;
	textFileVector=0;
	numWordsCharStar=0;
	charStarCopyToBeSorted=0;
	numSpaceCharStar=0;
}

void SortingCompetition::setFileName(const string& inputFileName) {
	textFile=inputFileName;
}

bool SortingCompetition::readData() {

	//reads in and stores words to a char **
	ifstream fin;
	fin.open("/home/tgjackson/workspace/DataStructuresRepo/SortComp/src/TomSawyer.txt");
	while(!fin.eof()){
		char *buffer=new char[80];
		fin>>buffer;
		if(textFileCharStar==0){
			textFileCharStar=new char * [10000];
			textFileCharStar[0]=new char [strlen(buffer)+1];
			strcpy(textFileCharStar[0],buffer);
			numWordsCharStar++;
			numSpaceCharStar=10000;
		}else{
			if(numWordsCharStar+1==numSpaceCharStar){
				cout<<"Did 10,000 more"<<endl;
				numSpaceCharStar+=10000;
				char ** temp=new char *[numSpaceCharStar];
				for(int i=0;i<numWordsCharStar;i++){
					temp[i]=new char[strlen(textFileCharStar[i])+1];
					strcpy(temp[i],textFileCharStar[i]);
				}
				temp[numWordsCharStar]=new char[strlen(buffer)+1];
				strcpy(temp[numWordsCharStar],buffer);
				for(int i=0;i<numWordsCharStar;i++){
					delete textFileCharStar[i];
				}
				delete [] textFileCharStar;
				textFileCharStar=temp;
				numWordsCharStar++;
			}else{
				textFileCharStar[numWordsCharStar]=new char[strlen(buffer)+1];
				strcpy(textFileCharStar[numWordsCharStar],buffer);
				numWordsCharStar++;
			}
		}
	}
	// END of reading into a char **


	return true;
}

bool SortingCompetition::prepareData() {
	charStarCopyToBeSorted=new char * [numWordsCharStar];
	for(int i=0;i<numWordsCharStar;i++){
		charStarCopyToBeSorted[i]=new char[strlen(textFileCharStar[i])+1];
		strcpy(charStarCopyToBeSorted[i],textFileCharStar[i]);
	}

	return true;
}


/*//MergeSort
void SortingCompetition::sortData() {
}
//QuickSort
void SortingCompetition::sortData() {

}
//InsertionSort
void SortingCompetition::sortData() {
}*/
//SelectionSort
void SortingCompetition::sortData() {

	for(int i=0;i<numWordsCharStar;i++){
		int minIndex=i;
		for(int j=i+1;j<numWordsCharStar;j++){
			if(strlen(charStarCopyToBeSorted[j])<strlen(charStarCopyToBeSorted[minIndex]))
				minIndex=j;
		}
		char * first=new char[strlen(charStarCopyToBeSorted[i])+1];
		strcpy(first,charStarCopyToBeSorted[i]);
		delete charStarCopyToBeSorted[i];
		charStarCopyToBeSorted[i]=new char[strlen(charStarCopyToBeSorted[minIndex])+1];
		strcpy(charStarCopyToBeSorted[i],charStarCopyToBeSorted[minIndex]);
		delete charStarCopyToBeSorted[minIndex];
		charStarCopyToBeSorted[minIndex]=new char[strlen(first)+1];
		strcpy(charStarCopyToBeSorted[minIndex],first);
	}

	for(int k=0;k<numWordsCharStar;k++){
		int minIndex=k;
		for(int m=k+1;m<numWordsCharStar;m++){
			if(strlen(charStarCopyToBeSorted[m]) == strlen(charStarCopyToBeSorted[minIndex]) ){
				if(strcmp(charStarCopyToBeSorted[m],charStarCopyToBeSorted[minIndex])<0)
					minIndex=m;
			}
		}
		char * first=new char[strlen(charStarCopyToBeSorted[k])+1];
		strcpy(first,charStarCopyToBeSorted[k]);
		delete charStarCopyToBeSorted[k];
		charStarCopyToBeSorted[k]=new char[strlen(charStarCopyToBeSorted[minIndex])+1];
		strcpy(charStarCopyToBeSorted[k],charStarCopyToBeSorted[minIndex]);
		delete charStarCopyToBeSorted[minIndex];
		charStarCopyToBeSorted[minIndex]=new char[strlen(first)+1];
		strcpy(charStarCopyToBeSorted[minIndex],first);
	}

}/*
//BubbleSort
void SortingCompetition::sortData() {
	bool flag=true;
	int i=1;
	while(flag){
		flag=false;
		for(int j=0;j<numWordsCharStar-1-i;j++){
			if(strcmp(charStarCopyToBeSorted[j+1],charStarCopyToBeSorted[j])<0)
			{
				// temp = array[j]
				char * first=new char[strlen(charStarCopyToBeSorted[j])+1];
				strcpy(first,charStarCopyToBeSorted[j]);

				// array[j] = array[j+1]
				delete charStarCopyToBeSorted[j];
				charStarCopyToBeSorted[j]=new char[strlen(charStarCopyToBeSorted[j+1])+1];
				strcpy(charStarCopyToBeSorted[j],charStarCopyToBeSorted[j+1]);

				// array[j+1] = temp
				delete charStarCopyToBeSorted[j+1];
				charStarCopyToBeSorted[j+1]=new char[strlen(first)+1];
				strcpy(charStarCopyToBeSorted[j+1],first);

				flag=true;
			}
		}
		i++;
		if (i%10000==0){
			cout << "finished " << i << endl;
		}
	}
	cout << "finished sorting " << endl;
}
//This will be my combination sort to win it all baby
void SortingCompetition::sortData() {
}
*/
void SortingCompetition::outputData(const string& outputFileName){
	ofstream fout;
	fout.open(outputFileName.c_str());
	for(int i=0;i<numWordsCharStar;i++){
		fout<<charStarCopyToBeSorted[i]<<endl;
	}

}/*
void quickSort(char ** temp,int numInSet){
	char * first=new char[strlen(temp[0])+1];
	strcpy(first,temp[0]);
	char * last=new char [strlen(temp[numInSet-1])+1];
	strcpy(first,temp[0]);
	char * middle=new char [strlen(temp[numInSet/2])+1];
	strcpy(first,temp[0]);
	char * pivot;
	if(strcmp(first,middle)>0){
		if(strcmp(first,last)>0){
			if(strcmp(last,middle)>0){
				//last = pivot
				pivot = new char[strlen(last)+1];
				strcpy( pivot, last);
			}
		}
	}else if (strcmp(first,middle)>0 && strcmp(first,last)>0 && strcmp(last,middle)<0){
		//middle = pivot
		pivot = new char [strlen(middle) +1];
		strcpy(pivot,middle);
	}
}
*/
