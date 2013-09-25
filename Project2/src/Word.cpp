/*
 * Word.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: tgjackson
 */

#include "Word.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

//default constructor, all private data=null
Word::Word() {
		letters=0;
		pages=0;
		category=0;
		inCategory=false;
		numLetters=0;
		numPages=0;
		numCatLetters=0;
}

//Word constructor with letterTemp being the Word, and category Temp being the category its in
//assuming its in a category--deep copy
Word::Word(char * letterTemp,char * categoryTemp) {
	inCategory=true;
	numLetters=strlen(letterTemp);
	numCatLetters=strlen(categoryTemp);
	letters=new char[numLetters+1];
	for(int i=0;i<=numLetters;i++){
		letters[i]=tolower(letterTemp[i]);
	}
	category=new char[numCatLetters+1];
	for(int i=0;i<=numCatLetters;i++){
		category[i]=tolower(categoryTemp[i]);
	}
	pages=0;
	numPages=0;
}

//word constructor for a word that isn't in a category-- letterTemp is the word
Word::Word(char * letterTemp) {
	inCategory=false;
	numLetters=strlen(letterTemp);
	letters=new char[numLetters+1];
	for(int i=0;i<=numLetters;i++){
		letters[i]=tolower(letterTemp[i]);
	}
	category=0;
	numCatLetters=0;
	pages=0;
	numPages=0;
}

//copy constructor
Word::Word(const Word& orig) {
		this->numCatLetters=orig.numCatLetters;
		this->numLetters=orig.numLetters;
		this->numPages=orig.numPages;
		this->pages=new int[this->numPages];
		for(int i=0;i<this->numPages;i++){
			this->pages[i]=orig.pages[i];
		}
		this->letters=new char[this->numLetters+1];
		for(int i=0;i<=this->numLetters;i++){
			this->letters[i]=orig.letters[i];
		}
		this->inCategory=orig.inCategory;
		if(this->inCategory){
			int categoryLength=strlen(orig.category);
			this->category=new char[categoryLength+1];
			strcpy(this->category,orig.category);
		}else{
			this->category=0;
			this->inCategory=false;
		}
}

//operator=overloader->delete original lhs if its not null, then set all lhs private data to
//rhs private data
Word& Word::operator=(const Word& rhs) {
	if(this != &rhs){
		if( this->letters!=0){
			delete [] this->letters;
		}
		if( this->pages!=0){
				delete [] this->pages;
		}
		if( this->category!=0){
				delete [] this->category;
		}
	}
	this->numCatLetters=rhs.numCatLetters;
	this->numLetters=rhs.numLetters;
	this->numPages=rhs.numPages;
	this->pages=new int[this->numPages];
	for(int i=0;i<this->numPages;i++){
		this->pages[i]=rhs.pages[i];
	}
	this->letters=new char[this->numLetters+1];
	for(int i=0;i<=this->numLetters;i++){
		this->letters[i]=rhs.letters[i];
	}
	this->inCategory=rhs.inCategory;
	if(this->inCategory){
		int categoryLength=strlen(rhs.category);
		this->category=new char[categoryLength+1];
		strcpy(this->category,rhs.category);
	}else{
		this->category=0;
		this->inCategory=false;
	}
	return *this;
}
//adds a page to the word, has to increase size of page array by 1
void Word::addPageToWord(int pageNumber) {
	if(numPages==0){
		pages=new int[1];
		pages[0]=pageNumber;
		numPages++;
	}else{
		bool newPage=true;
		for(int m=0;m<numPages;m++){
			if(pageNumber==pages[m])newPage=false;
		}
		if(newPage){
			int * temp=new int [numPages+1];
			for(int i=0;i<numPages;i++){
				temp[i]=pages[i];
			}
			temp[numPages]=pageNumber;
			delete [] pages;
			pages=temp;
			numPages++;
		}
	}
}

bool Word::isInCategory() {
	return inCategory;
}

char* Word::getLetters() {
	return letters;
}

char * Word::getMyCategory() {
	return category;
}

int* Word::getPages() {
	return pages;
}

int Word::getNumLetters() {
	return numLetters;
}
int Word::getPageByIndex(int n){
	return pages[n];
}

int Word::getNumPages() {
	return numPages;
}

int Word::getNumCatLetters() {
	return numCatLetters;
}

Word::~Word() {
	if( letters!=0){
		delete [] letters;
	}
	if( pages!=0){
			delete [] pages;
		}
	if( category!=0){
			delete [] category;
		}
}

