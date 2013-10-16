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
	stringCopyToBeSorted=0;
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
	stringCopyToBeSorted=0;
	numSpaceCharStar=0;
}

void SortingCompetition::setFileName(const string& inputFileName) {
	textFile=inputFileName;
}

bool SortingCompetition::readData() {

	//reads in and stores words to a char **
	ifstream fin;
	fin.open(textFile.c_str());
	//cout<<textFile.c_str()<<endl;
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
				//cout<<"Did 10,000 more"<<endl;
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

	//use char ** to create array of strings
	textFileString= new string [numWordsCharStar];
	for(int i=0;i<numWordsCharStar;i++){
		textFileString[i] = textFileCharStar[i];
	}

	return true;
}

bool SortingCompetition::prepareData() {
	charStarCopyToBeSorted=new char * [numWordsCharStar];
	stringCopyToBeSorted = new string [numWordsCharStar];
	for(int i=0;i<numWordsCharStar;i++){
		charStarCopyToBeSorted[i]=new char[strlen(textFileCharStar[i])+1];
		strcpy(charStarCopyToBeSorted[i],textFileCharStar[i]);
		stringCopyToBeSorted[i] = textFileString[i];
	}

	return true;
}
/*
	//BEGIN INSERTION SORT CHAR **
//InsertionSort
void SortingCompetition::sortData() {
	int i,j,numLength = numWordsCharStar;
	char * key;
	for(j=1;j<numLength;j++){
		key = new char [strlen(charStarCopyToBeSorted[j])+1];
		strcpy(key,charStarCopyToBeSorted[j]);
		for(i=j-1;(i>=0)&&(strlen(charStarCopyToBeSorted[i])>strlen(key));i--){
			delete [] charStarCopyToBeSorted[i+1];
			charStarCopyToBeSorted[i+1] = new char [strlen(charStarCopyToBeSorted[i])+1];
			strcpy(charStarCopyToBeSorted[i+1],charStarCopyToBeSorted[i]);
		}
		strcpy(charStarCopyToBeSorted[i+1],key);
	}
	int startIndex=0;
	int finishIndex=1;
	int startLength=strlen(charStarCopyToBeSorted[0]);
	//int finishLength=strlen(charStarCopyToBeSorted[numWordsCharStar-1]);
	while(startLength <= strlen(charStarCopyToBeSorted[numWordsCharStar-1]) ){
		bool inIndex=true;
		while(strlen(charStarCopyToBeSorted[finishIndex]) == startLength  && inIndex){
			if(finishIndex+1 < numWordsCharStar)
				finishIndex++;
			else inIndex=false;
		}
		if(finishIndex+1 == numWordsCharStar)
			finishIndex++;
		for(int i=startIndex;i<finishIndex;i++){
			//cout<<charStarCopyToBeSorted[i]<<endl;
		}
		int m, k;numLength=finishIndex;
		char * holdit;
		for(k=startIndex+1;k<numLength;k++){
			holdit = new char [strlen(charStarCopyToBeSorted[k])+1];
			strcpy(holdit,charStarCopyToBeSorted[k]);
			for(m=k-1;(m>=startIndex)&&(strcmp(charStarCopyToBeSorted[m],holdit) > 0);m--){
				delete [] charStarCopyToBeSorted[m+1];
				charStarCopyToBeSorted[m+1] = new char [strlen(charStarCopyToBeSorted[m])+1];
				strcpy(charStarCopyToBeSorted[m+1],charStarCopyToBeSorted[m]);
			}
			strcpy(charStarCopyToBeSorted[m+1],holdit);
			delete [] holdit;
		}
		startIndex=finishIndex;
		if(finishIndex<numWordsCharStar)
			startLength=strlen(charStarCopyToBeSorted[finishIndex]);
		else
			startLength ++;
		finishIndex++;
	}

}

//SelectionSort char **
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

}
	//START OF BUBBLE SORT CHAR **
//BubbleSort char **
void SortingCompetition::sortData() {
	bool flagNum=true;
	int iNum=1;
	while(flagNum){
		flagNum=false;
		for(int j=0;j<numWordsCharStar-iNum;j++){
			if(strlen(charStarCopyToBeSorted[j+1]) < strlen(charStarCopyToBeSorted[j]) )
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

				flagNum=true;
			}
		}
		iNum++;
		if (iNum%10000==0){
			cout << "finished " << iNum << endl;
		}
	}

	int startIndex=0;
	int finishIndex=1;
	int startLength=strlen(charStarCopyToBeSorted[0]);
	//int finishLength=strlen(charStarCopyToBeSorted[numWordsCharStar-1]);
	while(startLength <= strlen(charStarCopyToBeSorted[numWordsCharStar-1]) ){
		bool inIndex=true;
		while(strlen(charStarCopyToBeSorted[finishIndex]) == startLength  && inIndex){
			if(finishIndex+1 < numWordsCharStar)
				finishIndex++;
			else inIndex=false;
		}
		if(finishIndex+1 == numWordsCharStar)
			finishIndex++;
		for(int i=startIndex;i<finishIndex;i++){
			//cout<<charStarCopyToBeSorted[i]<<endl;
		}
		bool flag=true;
		int i=1;
		while(flag){
			flag=false;
			for(int j=startIndex;j<finishIndex-i;j++){
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
		startIndex=finishIndex;
		if(finishIndex<numWordsCharStar)
			startLength=strlen(charStarCopyToBeSorted[finishIndex]);
		else
			startLength ++;
		finishIndex++;

	}

}
	//END OF BUBBLE SORT CHAR **


//This will be my combination sort to win it all baby
void SortingCompetition::sortData() {
}*/


void SortingCompetition::outputData(const string& outputFileName){
	ofstream fout;
	fout.open(outputFileName.c_str());
	for(int i=0;i<numWordsCharStar;i++){
		//fout<<charStarCopyToBeSorted[i]<<endl;
		fout<<stringCopyToBeSorted[i]<<endl;
	}
}
/*
	//START OF QUICK SORT FUNCTIONS CHAR **

//QuickSort char **
void SortingCompetition::sortData() {
	quickSortNum(charStarCopyToBeSorted,0,numWordsCharStar-1);
	//quickSortAlp(charStarCopyToBeSorted,0,2);
	//quickSortAlp(charStarCopyToBeSorted,3,5);
	//quickSortAlp(charStarCopyToBeSorted,6,7);
	int startIndex=0;
	int finishIndex=1;
	int startLength=strlen(charStarCopyToBeSorted[0]);
	//int finishLength=strlen(charStarCopyToBeSorted[numWordsCharStar-1]);
	while(startLength <= strlen(charStarCopyToBeSorted[numWordsCharStar-1]) ){
		bool inIndex=true;
		while(strlen(charStarCopyToBeSorted[finishIndex]) == startLength  && inIndex){
			if(finishIndex+1 < numWordsCharStar)
				finishIndex++;
			else inIndex=false;
		}
		if(finishIndex+1 == numWordsCharStar)
			finishIndex++;
		for(int i=startIndex;i<finishIndex;i++){
			//cout<<charStarCopyToBeSorted[i]<<endl;
		}
		quickSortAlp(charStarCopyToBeSorted,startIndex,finishIndex-1);
		startIndex=finishIndex;
		if(finishIndex<numWordsCharStar)
			startLength=strlen(charStarCopyToBeSorted[finishIndex]);
		else
			startLength ++;
		finishIndex++;
	}
}

	//quick sort char **
void SortingCompetition::quickSortAlp(char ** temp,int left, int right){
	if(right-1 == left)	//size of set is 2
	{
		if(strcmp(temp[left],temp[right])>0){
			char * place =new char[strlen(temp[left])+1];
			strcpy(place,temp[left]);
			delete[] temp[left];
			temp[left]=new char [strlen(temp[right])+1];
			strcpy(temp[left],temp[right]);
			delete [] temp[right];
			temp[right]=new char [strlen(place)+1];
			strcpy(temp[right],place);
		}
	}else{
		char * first=new char[strlen(temp[left])+1];
		strcpy(first,temp[left]);
		int numInSet= right-left;
		if(left!= 0)numInSet++;
		char * last=new char [strlen(temp[right])+1];
		strcpy(last,temp[right]);
		char * middle=new char [strlen(temp[left+numInSet/2])+1];
		strcpy(middle,temp[left+numInSet/2]);
		char * pivot;
		if(strcmp(first,middle)>0){
			if(strcmp(first,last)>0){
				if(strcmp(last,middle)>0){
					//last = pivot
					pivot = new char[strlen(last)+1];
					strcpy( pivot, last);
				}else{
					//middle = pivot
					pivot = new char[strlen(middle)+1];
					strcpy( pivot, middle);
				}
			}else{
				//first is pivot
				pivot = new char[strlen(first)+1];
				strcpy( pivot, first);
			}
		}else{
			if (strcmp(middle,last)>0 ){
				if (strcmp(last,first)>0){
					//last = pivot
					pivot = new char[strlen(last)+1];
					strcpy( pivot, last);
				}else{
					//first = pivot
					pivot = new char[strlen(first)+1];
					strcpy( pivot, first);
				}
			}else{
				//middle = pivot
				pivot = new char [strlen(middle) +1];
				strcpy(pivot,middle);
			}
		}
		char * placeHolder;
		int i=left;
		int j =right;
		if(j - i >1){
			//char * pivot= new char[strlen(temp[(left+right)/2])+1];
			//strcpy(pivot,temp[(left+right)/2]);
			while ( i <= j){
				while(strcmp(temp[i],pivot) < 0)
					i++;
				while(strcmp(temp[j],pivot)>0)
					j--;
				if ( i <= j) {
					placeHolder=new char[strlen(temp[i])+1];
					strcpy(placeHolder,temp[i]);
					delete temp[i];
					temp[i]=new char[strlen(temp[j])+1];
					strcpy(temp[i],temp[j]);
					delete temp[j];
					temp[j]=new char[strlen(placeHolder)+1];
					strcpy(temp[j],placeHolder);
					i++;
					j--;
				}
			}
			if (left < j)
				quickSortAlp(temp,left,j);
			if( i < right)
				quickSortAlp(temp,i, right);
		}else{
			if(strcmp(temp[i],temp[j])>0){
				placeHolder=new char[strlen(temp[i])+1];
				strcpy(placeHolder,temp[i]);
				delete temp[i];
				temp[i]=new char[strlen(temp[j])+1];
				strcpy(temp[i],temp[j]);
				delete temp[j];
				temp[j]=new char[strlen(placeHolder)+1];
				strcpy(temp[j],placeHolder);
			}
		}
	}
}
	// quick sort num char **
void SortingCompetition::quickSortNum(char ** temp,int left, int right){
	if(right-1 == left)	//size of set is 2
	{
		if(strcmp(temp[left],temp[right])>0){
			char * place =new char[strlen(temp[left])+1];
			strcpy(place,temp[left]);
			delete[] temp[left];
			temp[left]=new char [strlen(temp[right])+1];
			strcpy(temp[left],temp[right]);
			delete [] temp[right];
			temp[right]=new char [strlen(place)+1];
			strcpy(temp[right],place);
		}
	}else{
		char * first=new char[strlen(temp[left])+1];
		strcpy(first,temp[left]);
		int numInSet= right-left;
		if(left!= 0)numInSet++;
		char * last=new char [strlen(temp[right])+1];
		strcpy(last,temp[right]);
		char * middle=new char [strlen(temp[left+numInSet/2])+1];
		strcpy(middle,temp[left+numInSet/2]);
		char * pivot;
		if(strcmp(first,middle)>0){
			if(strcmp(first,last)>0){
				if(strcmp(last,middle)>0){
					//last = pivot
					pivot = new char[strlen(last)+1];
					strcpy( pivot, last);
				}else{
					//middle = pivot
					pivot = new char[strlen(middle)+1];
					strcpy( pivot, middle);
				}
			}else{
				//first is pivot
				pivot = new char[strlen(first)+1];
				strcpy( pivot, first);
			}
		}else{
			if (strcmp(middle,last)>0 ){
				if (strcmp(last,first)>0){
					//last = pivot
					pivot = new char[strlen(last)+1];
					strcpy( pivot, last);
				}else{
					//first = pivot
					pivot = new char[strlen(first)+1];
					strcpy( pivot, first);
				}
			}else{
				//middle = pivot
				pivot = new char [strlen(middle) +1];
				strcpy(pivot,middle);
			}
		}
	int i=left;
	int j =right;
	char * placeHolder;
	while ( i <= j){
		while(strlen(temp[i]) < strlen(pivot) )
			i++;
		while(strlen(temp[j]) > strlen(pivot) )
			j--;
		if ( i <= j) {
			placeHolder=new char[strlen(temp[i])+1];
			strcpy(placeHolder,temp[i]);
			delete temp[i];
			temp[i]=new char[strlen(temp[j])+1];
			strcpy(temp[i],temp[j]);
			delete temp[j];
			temp[j]=new char[strlen(placeHolder)+1];
			strcpy(temp[j],placeHolder);
			i++;
			j--;
		}
	}
	if (left < j)
		quickSortNum(temp,left,j);
	if( i < right)
		quickSortNum(temp,i, right);
	}
}
	//////END OF QUICK SORT CHAR **

	//////START OF FUNCTIONS FOR MERGE SORT CHAR **

//MergeSort char**
void SortingCompetition::sortData() {

	mergeSortNum(charStarCopyToBeSorted, numWordsCharStar);
	int startIndex=0;
	int finishIndex=1;
	int startLength=strlen(charStarCopyToBeSorted[0]);
	//int finishLength=strlen(charStarCopyToBeSorted[numWordsCharStar-1]);
	while(startLength <= strlen(charStarCopyToBeSorted[numWordsCharStar-1]) ){
		bool inIndex=true;
		while(strlen(charStarCopyToBeSorted[finishIndex]) == startLength  && inIndex){
			if(finishIndex+1 < numWordsCharStar)
				finishIndex++;
			else inIndex=false;
		}
		if(finishIndex+1 == numWordsCharStar)
			finishIndex++;
		for(int i=startIndex;i<finishIndex;i++){
			//cout<<charStarCopyToBeSorted[i]<<endl;
		}
		mergeSortAlp(charStarCopyToBeSorted,startIndex,finishIndex-1);
		startIndex=finishIndex;
		if(finishIndex<numWordsCharStar)
			startLength=strlen(charStarCopyToBeSorted[finishIndex]);
		else
			startLength ++;
		finishIndex++;
	}

}

	//merge char **
void SortingCompetition:: mergeAlp(char ** input, int left, int right, char **storage){

	//base case- only one element
	if(right == left +1){
		return;

	}else{

		int i=0;
		int length = right - left;
		int midpoint = length/2;

		// l and r refer to first index in left and right subarray
		int l = left;
		int r = left + midpoint;

		//sort each subarray

		mergeAlp(input, left, left + midpoint, storage);
		mergeAlp(input, left + midpoint, right, storage);

		//merge the arrays back together

		for(i = 0; i < length; i++){
			//	first check to see if any elements remain in left array
			//  - if yes, check if any elements remain in right array
			//  -- if so compare them
			//  -Otherwise, use element from left array for merge
			//

			if (l < left + midpoint &&
					(r == right ||  strcmp(input[l], input[r])<0))
			{
				storage[i]=new char [strlen(input[l])+1];
				strcpy(storage[i],input[l]);
				l++;
			}else{
				storage[i]=new char [strlen(input[r])+1];
				strcpy(storage[i],input[r]);
				r++;
			}
		}

		//copy sorted subarray back to input
		for(i = left; i < right; i++){
			delete [] input[i];
			input[i]=new char[strlen(storage[i-left])+1];
			strcpy(input[i], storage[i-left]);
		}

	}
}
	//merge char **
void SortingCompetition::mergeSortAlp(char **input, int start, int finishIndex){
	char ** storage = new char * [finishIndex-start+1];
	mergeAlp(input, start, finishIndex+1, storage);

}
	//merge char **
void SortingCompetition:: mergeNum(char ** input, int left, int right, char **storage){

	//base case- only one element
	if(right == left +1){
		return;

	}else{

		int i=0;
		int length = right - left;
		int midpoint = length/2;

		// l and r refer to first index in left and right subarray
		int l = left;
		int r = left + midpoint;

		//sort each subarray

		mergeNum(input, left, left + midpoint, storage);
		mergeNum(input, left + midpoint, right, storage);

		//merge the arrays back together

		for(i = 0; i < length; i++){
			//	first check to see if any elements remain in left array
			//  - if yes, check if any elements remain in right array
			//  -- if so compare them
			//  -Otherwise, use element from left array for merge
			//

			if (l < left + midpoint &&
					(r == right || ( strlen(input[l]) < strlen(input[r]) ) ) )
			{
				storage[i]=new char [strlen(input[l])+1];
				strcpy(storage[i],input[l]);
				l++;
			}else{
				storage[i]=new char [strlen(input[r])+1];
				strcpy(storage[i],input[r]);
				r++;
			}
		}

		//copy sorted subarray back to input
		for(i = left; i < right; i++){
			delete [] input[i];
			input[i]=new char[strlen(storage[i-left])+1];
			strcpy(input[i], storage[i-left]);
		}

	}
}
	//merge char **
void SortingCompetition::mergeSortNum(char **input, int size){
	char ** storage = new char * [size];
	mergeNum(input, 0, size, storage);

}
	///////END OF MERGE SORT CHAR **

	///////START OF MERGE SORT STRING

//mergeSort string *
void SortingCompetition::sortData(){
	mergeSortNum(stringCopyToBeSorted, numWordsCharStar);
	int startIndex=0;
	int finishIndex=1;
	int startLength= stringCopyToBeSorted[0].length();
	//int finishLength=strlen(charStarCopyToBeSorted[numWordsCharStar-1]);
	while(startLength <= stringCopyToBeSorted[numWordsCharStar-1].length() ){
		bool inIndex=true;
		while(stringCopyToBeSorted[finishIndex].length() == startLength  && inIndex){
			if(finishIndex+1 < numWordsCharStar)
				finishIndex++;
			else inIndex=false;
		}
		if(finishIndex+1 == numWordsCharStar)
			finishIndex++;
		for(int i=startIndex;i<finishIndex;i++){
			//cout<<charStarCopyToBeSorted[i]<<endl;
		}
		mergeSortAlp(stringCopyToBeSorted,startIndex,finishIndex-1);
		startIndex=finishIndex;
		if(finishIndex<numWordsCharStar)
			startLength=stringCopyToBeSorted[finishIndex].length();
		else
			startLength ++;
		finishIndex++;
	}
}

	//string *
void SortingCompetition:: mergeAlp(string * input, int left, int right, string *storage){

	//base case- only one element
	if(right == left +1){
		return;

	}else{

		int i=0;
		int length = right - left;
		int midpoint = length/2;

		// l and r refer to first index in left and right subarray
		int l = left;
		int r = left + midpoint;

		//sort each subarray

		mergeAlp(input, left, left + midpoint, storage);
		mergeAlp(input, left + midpoint, right, storage);

		//merge the arrays back together

		for(i = 0; i < length; i++){
			//	first check to see if any elements remain in left array
			//  - if yes, check if any elements remain in right array
			//  -- if so compare them
			//  -Otherwise, use element from left array for merge
			//

			if (l < left + midpoint &&
					(r == right ||  (input[l] < input[r] )) )
			{
				storage[i]=input[l];
				l++;
			}else{
				storage[i]=input[r];
				r++;
			}
		}

		//copy sorted subarray back to input
		for(i = left; i < right; i++){
			input[i]=storage[i-left];
		}

	}
}
	//merge string *
void SortingCompetition::mergeSortAlp(string *input, int start, int finishIndex){
	string * storage = new string [finishIndex-start+1];
	mergeAlp(input, start, finishIndex+1, storage);

}
	//merge string *
void SortingCompetition:: mergeNum(string * input, int left, int right, string *storage){

	//base case- only one element
	if(right == left +1){
		return;

	}else{

		int i=0;
		int length = right - left;
		int midpoint = length/2;

		// l and r refer to first index in left and right subarray
		int l = left;
		int r = left + midpoint;

		//sort each subarray

		mergeNum(input, left, left + midpoint, storage);
		mergeNum(input, left + midpoint, right, storage);

		//merge the arrays back together

		for(i = 0; i < length; i++){
			//	first check to see if any elements remain in left array
			//  - if yes, check if any elements remain in right array
			//  -- if so compare them
			//  -Otherwise, use element from left array for merge
			//

			if (l < left + midpoint &&
					(r == right || ( input[l].length() < input[r].length() ) ) )
			{
				storage[i]=input[l];
				l++;
			}else{
				storage[i]=input[r];
				r++;
			}
		}

		//copy sorted subarray back to input
		for(i = left; i < right; i++){
			input[i]= storage[i-left];
		}

	}
}
	//merge string *
void SortingCompetition::mergeSortNum(string *input, int size){
	string * storage = new string [size];
	mergeNum(input, 0, size, storage);

}

////////END OF MERGESORT FOR STRING

*/
//START OF QUICK SORT FUNCTIONS string *

//QuickSort string *
void SortingCompetition::sortData() {
quickSortNum(stringCopyToBeSorted,0,numWordsCharStar-1);
//quickSortAlp(charStarCopyToBeSorted,0,2);
//quickSortAlp(charStarCopyToBeSorted,3,5);
//quickSortAlp(charStarCopyToBeSorted,6,7);
int startIndex=0;
int finishIndex=1;
int startLength=stringCopyToBeSorted[0].length();
//int finishLength=strlen(charStarCopyToBeSorted[numWordsCharStar-1]);
while(startLength <= stringCopyToBeSorted[numWordsCharStar-1].length() ){
	bool inIndex=true;
	while(stringCopyToBeSorted[finishIndex].length() == startLength  && inIndex){
		if(finishIndex+1 < numWordsCharStar)
			finishIndex++;
		else inIndex=false;
	}
	if(finishIndex+1 == numWordsCharStar)
		finishIndex++;
	for(int i=startIndex;i<finishIndex;i++){
		//cout<<charStarCopyToBeSorted[i]<<endl;
	}
	quickSortAlp(stringCopyToBeSorted,startIndex,finishIndex-1);
	startIndex=finishIndex;
	if(finishIndex<numWordsCharStar)
		startLength=stringCopyToBeSorted[finishIndex].length();
	else
		startLength ++;
	finishIndex++;
}
}

//quick sort string *
void SortingCompetition::quickSortAlp(string * temp,int left, int right){
/*if(right-1 == left)	//size of set is 2
{
	if(temp[left] > temp[right] ){
		string place = temp[left];
		temp[left]= temp[right];
		temp[right]= place;
	}
}*/
  if(right - left <24){
	  	int m, k,numLength=right;
	  		string holdit;
	  		for(k=left+1;k<numLength;k++){
	  			holdit =  temp[k];
	  			for(m=k-1;(m>=left) &&(temp[m] > holdit );m--){
	  				temp[m+1] = temp[m];
	  			}
	  			temp[m+1] = holdit;
	  		}
    }else{
	string first= temp[left];
	int numInSet= right-left;
	if(left!= 0)numInSet++;
	string last= temp[right];
	string middle= temp[left+numInSet/2];
	string pivot;
	if(first > middle ){
		if(first > last ){
			if( last > middle ){
				//last = pivot
				pivot = last;
			}else{
				//middle = pivot
				pivot = middle;
			}
		}else{
			//first is pivot
			pivot = first;
		}
	}else{
		if (middle > last ){
			if ( last > first ){
				//last = pivot
				pivot = last;
			}else{
				//first = pivot
				pivot = first;
			}
		}else{
			//middle = pivot
			pivot = middle;
		}
	}
	string placeHolder;
	int i=left;
	int j =right;
	if(j - i >1){
		while ( i <= j){
			while(temp[i] < pivot )
				i++;
			while( temp[j] > pivot )
				j--;
			if ( i <= j) {
				placeHolder = temp[i];
				temp[i]= temp[j];
				temp[j]= placeHolder;
				i++;
				j--;
			}
		}
		if (left < j)
			quickSortAlp(temp,left,j);
		if( i < right)
			quickSortAlp(temp,i, right);
	}else{
		if(temp[i] > temp[j] ){
			placeHolder= temp[i];
			temp[i]= temp[j];
			temp[j]= placeHolder;
		}
	}
}
}
// quick sort string *
void SortingCompetition::quickSortNum(string * temp,int left, int right){
	/*if(right-1 == left)	//size of set is 2
	{
		if( temp[left] > temp[right]){
			string place = temp[left];
			temp[left]= temp[right];
			temp[right]= place;
		}
	}*/
	if(right - left <24){
		int m, k,numLength=right;
			string holdit;
			for(k=left+1;k<numLength;k++){
				holdit =  temp[k];
				for(m=k-1;(m>=left) &&(temp[m].length() > holdit.length() );m--){
					temp[m+1] = temp[m];
				}
				temp[m+1] = holdit;
			}
	}else{

	    string first= temp[left];
		int numInSet= right-left;
		if(left!= 0)numInSet++;
		string last= temp[right];
		string middle= temp[left+numInSet/2];
		string pivot;
		if(first > middle ){
			if( first > last ){
				if(last > middle ){
					//last = pivot
					pivot = last;
				}else{
					//middle = pivot
					pivot = middle;
				}
			}else{
				//first is pivot
				pivot = first;
			}
		}else{
			if (middle > last ){
				if (last > first ){
					//last = pivot
					pivot = last;
				}else{
					//first = pivot
					pivot = first;
				}
			}else{
				//middle = pivot
				pivot = middle;
			}
		}
		int i=left;
		int j =right;
		string placeHolder;
		while ( i <= j){
			while(temp[i].length() < pivot.length() )
				i++;
			while(temp[j].length() > pivot.length() )
				j--;
			if ( i <= j) {
				placeHolder= temp[i];
				temp[i]= temp[j];
				temp[j]= placeHolder;
				i++;
				j--;
			}
		}
		if (left < j)
			quickSortNum(temp,left,j);
		if( i < right)
			quickSortNum(temp,i, right);
	}
}
//////END OF QUICK SORT string *
/*
//START OF INTRO SORT FUNCTIONS string *

//IntroSort string *
void SortingCompetition::sortData() {
quickSortNum(stringCopyToBeSorted,0,numWordsCharStar-1);
int startIndex=0;
int finishIndex=1;
int startLength=stringCopyToBeSorted[0].length();
//int finishLength=strlen(charStarCopyToBeSorted[numWordsCharStar-1]);
while(startLength <= stringCopyToBeSorted[numWordsCharStar-1].length() ){
	bool inIndex=true;
	while(stringCopyToBeSorted[finishIndex].length() == startLength  && inIndex){
		if(finishIndex+1 < numWordsCharStar)
			finishIndex++;
		else inIndex=false;
	}
	if(finishIndex+1 == numWordsCharStar)
		finishIndex++;
	for(int i=startIndex;i<finishIndex;i++){
		//cout<<charStarCopyToBeSorted[i]<<endl;
	}
	quickSortAlp(stringCopyToBeSorted,startIndex,finishIndex-1);
	startIndex=finishIndex;
	if(finishIndex<numWordsCharStar)
		startLength=stringCopyToBeSorted[finishIndex].length();
	else
		startLength ++;
	finishIndex++;
}
}

//intro sort string *
void SortingCompetition::quickSortAlp(string * temp,int left, int right){
if(right-1 == left)	//size of set is 2
{
	if(temp[left] > temp[right] ){
		string place = temp[left];
		temp[left]= temp[right];
		temp[right]= place;
	}
}else{
	string first= temp[left];
	int numInSet= right-left;
	if(left!= 0)numInSet++;
	string last= temp[right];
	string middle= temp[left+numInSet/2];
	string pivot;
	if(first > middle ){
		if(first > last ){
			if( last > middle ){
				//last = pivot
				pivot = last;
			}else{
				//middle = pivot
				pivot = middle;
			}
		}else{
			//first is pivot
			pivot = first;
		}
	}else{
		if (middle > last ){
			if ( last > first ){
				//last = pivot
				pivot = last;
			}else{
				//first = pivot
				pivot = first;
			}
		}else{
			//middle = pivot
			pivot = middle;
		}
	}
	string placeHolder;
	int i=left;
	int j =right;
	if(j - i >1){
		//char * pivot= new char[strlen(temp[(left+right)/2])+1];
		//strcpy(pivot,temp[(left+right)/2]);
		while ( i <= j){
			while(temp[i] < pivot )
				i++;
			while( temp[j] > pivot )
				j--;
			if ( i <= j) {
				placeHolder = temp[i];
				temp[i]= temp[j];
				temp[j]= placeHolder;
				i++;
				j--;
			}
		}
		if (left < j)
			quickSortAlp(temp,left,j);
		if( i < right)
			quickSortAlp(temp,i, right);
	}else{
		if(temp[i] > temp[j] ){
			placeHolder= temp[i];
			temp[i]= temp[j];
			temp[j]= placeHolder;
		}
	}
}
}
// intro sort string *
void SortingCompetition::quickSortNum(string * temp,int left, int right){
	if(right-1 == left)	//size of set is 2
	{
		if( temp[left] > temp[right]){
			string place = temp[left];
			temp[left]= temp[right];
			temp[right]= place;
		}
	}else{
		string first= temp[left];
		int numInSet= right-left;
		if(left!= 0)numInSet++;
		string last= temp[right];
		string middle= temp[left+numInSet/2];
		string pivot;
		if(first > middle ){
			if( first > last ){
				if(last > middle ){
					//last = pivot
					pivot = last;
				}else{
					//middle = pivot
					pivot = middle;
				}
			}else{
				//first is pivot
				pivot = first;
			}
		}else{
			if (middle > last ){
				if (last > first ){
					//last = pivot
					pivot = last;
				}else{
					//first = pivot
					pivot = first;
				}
			}else{
				//middle = pivot
				pivot = middle;
			}
		}
		int i=left;
		int j =right;
		string placeHolder;
		while ( i <= j){
			while(temp[i].length() < pivot.length() )
				i++;
			while(temp[j].length() > pivot.length() )
				j--;
			if ( i <= j) {
				placeHolder= temp[i];
				temp[i]= temp[j];
				temp[j]= placeHolder;
				i++;
				j--;
			}
		}
		if (left < j)
			quickSortNum(temp,left,j);
		if( i < right)
			quickSortNum(temp,i, right);
	}
}
//////END OF INTRO SORT string *

//////START OF HEAP SORT functions string *

void SortingCompetition::sortData(){
	makeHeapNum(stringCopyToBeSorted,numWordsCharStar);
	sortHeapNum(stringCopyToBeSorted,numWordsCharStar);
	int startIndex=0;
	int finishIndex=1;
	int startLength=stringCopyToBeSorted[0].length();
	//int finishLength=strlen(charStarCopyToBeSorted[numWordsCharStar-1]);
	while(startLength <= stringCopyToBeSorted[numWordsCharStar-1].length() ){
		bool inIndex=true;
		while(stringCopyToBeSorted[finishIndex].length() == startLength  && inIndex){
			if(finishIndex+1 < numWordsCharStar)
				finishIndex++;
			else inIndex=false;
		}
		if(finishIndex+1 == numWordsCharStar)
			finishIndex++;
		for(int i=startIndex;i<finishIndex;i++){
			//cout<<charStarCopyToBeSorted[i]<<endl;
		}
		makeHeap(stringCopyToBeSorted,startIndex,finishIndex);
		sortHeap(stringCopyToBeSorted,startIndex,finishIndex);

		startIndex=finishIndex;
		if(finishIndex<numWordsCharStar)
			startLength=stringCopyToBeSorted[finishIndex].length();
		else
			startLength ++;
		finishIndex++;
	}
}

void SortingCompetition::makeHeap(string * input, int startIndex, int finishIndex){
	int i, k, j;
	string temp;
	for(i=startIndex+1;i<finishIndex;i++){
		temp=input[i];
		k=(i-1)/2;
		j=i;
		while(j>startIndex && input[k]<temp){
			input[j]=input[k];
			j=k;
			k=(j-1)/2;
		}
		input[j]=temp;
	}
}
void SortingCompetition::sortHeap(string * input, int startIndex, int finishIndex){
	int i;
	string temp;
	for(i=finishIndex-1;i>=startIndex+1;i--){
		temp=input[i];
		input[i]=input[startIndex];
		input[startIndex]=temp;
		makeHeap(input,startIndex,i);
	}
}
void SortingCompetition::makeHeapNum(string * input, int size){
	int i, k, j;
	string temp;
	for(i=1;i<size;i++){
		temp=input[i];
		k=(i-1)/2;
		j=i;
		while(j>0 && input[k].length() < temp.length()){
			input[j]=input[k];
			j=k;
			k=(j-1)/2;
		}
		input[j]=temp;
	}
}
void SortingCompetition::sortHeapNum(string * input, int size){
	int i,j;
	string temp;
	for(i=size-1;i>=1;i--){
		temp=input[i];
		input[i]=input[0];
		input[0]=temp;
		makeHeapNum(input,i);
	}
}
*/
