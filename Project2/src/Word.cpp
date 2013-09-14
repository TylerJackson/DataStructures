/*
 * Word.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: tgjackson
 */

#include "Word.h"
#include <cstring>

Word::Word(char * letterTemp,char * categoryTemp) {
	// TODO Auto-generated constructor stub
	inCategory=true;
	numLetters=strlen(letterTemp);
	letters=new char[numLetters+1];
	strcpy(letters,letterTemp);
	int categoryLength=strlen(categoryTemp);
	category=new char[categoryLength+1];
	strcpy(category,categoryTemp);
	pages=0;
	numPages=0;
}
Word::Word(char * letterTemp) {
	// TODO Auto-generated constructor stub
	inCategory=false;
	numLetters=strlen(letterTemp);
	letters=new char[numLetters+1];
	strcpy(letters,letterTemp);
	category=0;
	pages=0;
	numPages=0;

}

void Word::addPageToWord(int pageNumber) {
	if(numPages==0){
		pages=new int[1];
		pages[0]=pageNumber;
		numPages++;
	}else{
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

char* Word::getLetters() {
	return 0;
}

int Word::getNumLetters() {
	return 0;
}

Word::Word() {
		letters=0;
		pages=0;
		category=0;
		inCategory=false;
		numLetters=0;
		numPages=0;
}

Word& Word::operator=(const Word& rhs) {
	if(this != &rhs){
		if( this->letters!=0){
				delete [] this->letters;
			}
			if( this->pages!=0){
					delete [] this->pages;
				}
			if( this->category!=0){
					delete [] this->pages;
				}
	}
			this->numLetters=rhs.numLetters;
			this->numPages=rhs.numPages;
			this->pages=new int[this->numPages];
			for(int i=0;i<this->numPages;i++){
				this->pages[i]=rhs.pages[i];
			}
			this->letters=new char[this->numLetters+1];
			for(int i=0;i<this->numLetters;i++){
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

Word::Word(const Word& orig) {
		this->numLetters=orig.numLetters;
		this->numPages=orig.numPages;
		this->pages=new int[this->numPages];
		for(int i=0;i<this->numPages;i++){
			this->pages[i]=orig.pages[i];
		}
		this->letters=new char[this->numLetters+1];
		for(int i=0;i<this->numLetters;i++){
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

Word::~Word() {
	if( letters!=0){
		delete [] letters;
	}
	if( pages!=0){
			delete [] pages;
		}
	if( category!=0){
			delete [] pages;
		}
}

