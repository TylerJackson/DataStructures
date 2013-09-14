/*
 * Category.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: tgjackson
 */
#include "Category.h"
#include <cstring>
#include <iostream>
using namespace std;
Category::Category() {
	name=0;
	categoryWords=0;
	numCatWords=0;
}
Category& Category::operator =(const Category& rhs) {
	if(this != &rhs){
		if(this->name!=0){
			delete []this->name;
		}
		if(this->categoryWords!=0){
			for(int i=0;i<this->numCatWords;i++){
				delete []categoryWords[i];
			}
			delete []categoryWords;
		}
	}
	int tempNameLength=strlen(rhs.name);
	this->name=new char[tempNameLength+1];
	strcpy(this->name,rhs.name);
	this->numCatWords=rhs.numCatWords;
	this->categoryWords=new char*[rhs.numCatWords];
	for(int i=0;i<this->numCatWords;i++){
		int tempLength=strlen(rhs.categoryWords[i]);
		this->categoryWords[i]=new char[tempLength+1];
		strcpy(this->categoryWords[i],rhs.categoryWords[i]);
	}
	return *this;
}

Category::Category(const Category& orig) {
	int tempNameLength=strlen(orig.name);
		this->name=new char[tempNameLength+1];
		strcpy(this->name,orig.name);
		this->numCatWords=orig.numCatWords;
		this->categoryWords=new char*[numCatWords];
		for(int i=0;i<this->numCatWords;i++){
			int tempLength=strlen(orig.categoryWords[i]);
			this->categoryWords[i]=new char[tempLength+1];
			strcpy(this->categoryWords[i],orig.categoryWords[i]);
		}
}


Category::Category(char* nameTemp) {
	int tempLen=strlen(nameTemp);
	name=new char[tempLen+1];
	strcpy(name,nameTemp);
	categoryWords=0;
	numCatWords=0;
}

void Category::addCatWord(char* wordTemp) {
	if(categoryWords!=0){
		char ** temp=new char * [numCatWords+1];
		for(int i=0;i<numCatWords;i++){
			int tempLen=strlen(categoryWords[i]);
			temp[i]=new char[tempLen+1];
			strcpy(temp[i],categoryWords[i]);
		}
		int tempWordLen=strlen(wordTemp);
		temp[numCatWords]=new char[tempWordLen+1];
		strcpy(temp[numCatWords],wordTemp);
		for(int i=0;i<numCatWords;i++){
				delete []categoryWords[i];
			}
			delete []categoryWords;
			categoryWords=temp;
	}else{
		categoryWords=new char *[1];
		int tempLen=strlen(wordTemp);
		categoryWords[0]=new char[tempLen+1];
		strcpy(categoryWords[0],wordTemp);
	}
	numCatWords++;
}

char* Category::getName() {
	return name;
}

char* Category::getCatWord(int index) {
	return categoryWords[index];
}

int Category::getNumCatWords() {
	return numCatWords;
}

Category::~Category() {
	if(categoryWords!=0){
		for(int i=0;i<numCatWords;i++){
			delete []categoryWords[i];
		}
		delete [] categoryWords;
	}
	if(name!=0){
		delete [] name;
	}
}

void Category::printCatWords() {
	for(int i=0;i<numCatWords;i++){
		int j=i+1;
		cout<<"Category Word # "<<j<<"is: "<<categoryWords[i]<<endl;
	}
}
