/*
 * readInObject.cpp
 *
 *  Created on: Sep 11, 2013
 *      Author: tgjackson
 */
#include <fstream>
#include <iostream>
#include "readInObject.h"
#include "Word.h"
#include <cstdlib>
#include <cstdio>
using namespace std;

readInObject::readInObject() {
	// TODO Auto-generated constructor stub
	numStopWords=0;
	currentPage=0;
	stopWords=0;
	categList=0;
	numCateg=0;
}

char* readInObject::getStopWord(int index) {
	return stopWords[index];
}

int readInObject::getNumStopWords() {
	return numStopWords;
}

void readInObject::addCategoryToList(char* categName) {
	if(numCateg==0){
		categList=new Category[1];
		categList[0]=Category(categName);
	}else{
		Category *temp=new Category [numCateg+1];
		for(int i=0;i<numCateg;i++){
			temp[i]=Category(categList[i]);
		}
		temp[numCateg]=Category(categName);
		delete []categList;
		categList=temp;
	}
	numCateg++;
}

Category& readInObject::getCategoryByName(char* tempName) {
	for(int i=0;i<numCateg;i++){
		if(strcmp(categList[i].getName(),tempName)==0)return categList[i];
	}
	return categList[0];
}

readInObject::~readInObject() {
	// TODO Auto-generated destructor stub
}

void readInObject::readInTextFile(const char* textfile) {
	ifstream fin;
	fin.open(textfile);
	char * buffer=new char [80];
	while(!fin.eof()){
		fin.getline(buffer,80);
		cout<<buffer<<endl;
		if(buffer[0]=='['){
			int index=1;
			while(buffer[index]!=']'){
				index++;
			}
			char *temp=new char[index-1];
			for(int i=1;i<index;i++){
				temp[i-1]=buffer[i];
			}
			currentPage=atoi(temp);
			cout<<currentPage<<endl;
		}
	}
}

void readInObject::readInHelperFile(const char* textfile) {
	fstream fin;
	fin.open(textfile);
	char * buffer=new char[80];
	fin.getline(buffer,80);
	fin>>buffer;
	while(buffer[0]!='['){
		if(notStopWord(buffer)){
			addStopWord(buffer);
		}
		fin>>buffer;
	}
	fin.getline(buffer,80);//clears first line after [category]
	while(!fin.eof()){
		fin>>buffer;
		addCategoryToList(buffer);
		char * tempBuff=new char[31];
		fin>>tempBuff;//clears past = sign after category titles
		bool b=true;
		while(b){
			fin>>tempBuff;
			getCategoryByName(buffer).addCatWord(tempBuff);
			cout<<tempBuff;
			for(int i=0;i<strlen(tempBuff);i++){
				if(tempBuff[i]=='/n' ||fin.eof())b=false;
			}
		}
	}
	for(int i=0;i<3;i++){
		cout<<categList[i].getName()<<endl;
	}
}

bool readInObject::notStopWord(char* wordTemp) {
	for(int i=0;i<numStopWords;i++){
		if(strcmp(stopWords[i],wordTemp)==0) return false;
	}
	return true;
}
void readInObject::addStopWord(char *tempStopWord){
	if(numStopWords!=0){
		char ** temp=new char *[numStopWords+1];
		for(int i=0;i<numStopWords;i++){
			int tempLength=strlen(stopWords[i]);
			temp[i]=new char[tempLength+1];
			strcpy(temp[i],stopWords[i]);
		}
		for(int i=0;i<numStopWords;i++){
			delete [] stopWords[i];
		}
		delete [] stopWords;
		int tempLen=strlen(tempStopWord);
		temp[numStopWords]=new char[tempLen+1];
		strcpy(temp[numStopWords],tempStopWord);
		stopWords=temp;
	}else{
		stopWords=new char *[1];
		int tempoLen=strlen(tempStopWord);
		stopWords[0]=new char [tempoLen+1];
		strcpy(stopWords[0],tempStopWord);
	}
	numStopWords++;
}

Category& readInObject::getCategoryByIndex(int index) {
	return categList[index];
}

int readInObject::getNumCategories() {
	return numCateg;
}

void readInObject::printCategories() {
	for(int i=0;i<numCateg;i++){
		int j=i+1;
		cout<<"Category #"<<j<<"is: "<<categList[i].getName()<<endl;
		cout<<"The words in this category are: "<<endl;
		categList[i].printCatWords();
	}
}
