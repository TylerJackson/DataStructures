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
#include <cstring>
using namespace std;

//default constructor just initializes all private data to null
readInObject::readInObject() {
	numStopWords=0;
	currentPage=0;
	stopWords=0;
	categList=0;
	numCateg=0;
	wordList=0;
	numWords=0;
}

//returns the word in our word list that contains the word tempLetters
//only called when word list has at least one word
Word& readInObject::getWordByLetters(char* tempLetters) {
	for(int i=0;i<numWords;i++){
		if(strcmp(wordList[i].getLetters(),tempLetters)==0){
			return wordList[i];
		}
	}
	return wordList[0];//shouldn't ever get here--just here to return something
}

//returns category in our category list that coincides with index 'index'
//only called when categories exist
Category& readInObject::getCategoryByIndex(int index) {
	return categList[index];
}

//returns the category in our list that has the name 'tempName'
//only called when the category list contains at least one
Category& readInObject::getCategoryByName(char* tempName) {
	for(int i=0;i<numCateg;i++){
		if(strcmp(categList[i].getName(),tempName)==0)return categList[i];
	}
	return categList[0]; //shouldn't ever get here
}

//returns the stop word that coincides with 'index' in our stopWords list
char* readInObject::getStopWord(int index) {
	return stopWords[index];
}

//returns the name of the category that has the word catWord in it
//only called when there exists a category with this word in it
char * readInObject::getCategoryNameByCatWord(char* catWord) {
	for(int i =0;i < numCateg; i++){
		int numWordsInCateg=categList[i].getNumCatWords();
		for(int j=0;j<numWordsInCateg;j++){
			if(strcmp(categList[i].getCatWord(j),catWord)==0){
				return categList[i].getName();
			}
		}
	}return categList[0].getName();//this is just to return something--should
									//never get here
}

int readInObject::getNumStopWords() {
	return numStopWords;
}


int readInObject::getNumCategories() {
	return numCateg;
}
int readInObject::numDigits(int n){
	int num=0;
	while(n>0){
		n=n/10;
		num++;
	}
	return num;
}


bool readInObject::notStopWord(char* wordTemp) {
	for(int i=0;i<strlen(wordTemp);i++){
		wordTemp[i]=tolower(wordTemp[i]);
	}
	for(int i=0;i<numStopWords;i++){
		if(strcmp(stopWords[i],wordTemp)==0) return false;
	}
	return true;
}

bool readInObject::isUniqueWord(char* wordtemp) {
	for(int i=0;i<numWords;i++){
		if(strcmp(wordList[i].getLetters(),wordtemp)==0)return false;
	}
	return true;
}

//this loops through all the words in all the categories in our list
//to see if the word 'wordTemp' is in any of the categories
bool readInObject::isInCategoryFromList(char* wordtemp) {
	for(int i =0;i < numCateg; i++){
		int numWordsInCateg=categList[i].getNumCatWords();
		for(int j=0;j<numWordsInCateg;j++){
			if(strcmp(categList[i].getCatWord(j),wordtemp)==0){
				return true;
			}
		}
	}return false;
}

//this reads in from the text file or our book file
//stores each word that isn't a stop word into our list, as well as
//the page that its on
void readInObject::readInTextFile(const char* textfile) {
	ifstream fin;
	fin.open(textfile);
	char * buffer1=new char [80];
	fin>>buffer1;
	while(!fin.eof()){
		//sets current page using the value between []
		if(buffer1[0]=='['){
			int index=1;
			while(buffer1[index]!=']'){
				index++;
			}
			char *temp=new char[index-1];
			for(int i=1;i<index;i++){
				temp[i-1]=buffer1[i];
			}
			currentPage=atoi(temp);
		}else{	//gets all the words from the current page and adds them to our wordlist
			if(notStopWord(buffer1)){
				if(isUniqueWord(buffer1) ){
					if(isInCategoryFromList(buffer1)){
						char * categHolder=new char[strlen(getCategoryNameByCatWord(buffer1))+1];
						strcpy(categHolder,getCategoryNameByCatWord(buffer1));
						Word tempWord(buffer1,categHolder);
						tempWord.addPageToWord(currentPage);
						addWord(tempWord);
					}else{  //if not in a category uses diff. word constructor,then adds word
						Word tempWord(buffer1);
						tempWord.addPageToWord(currentPage);
						addWord(tempWord);
					}
				}else{  //if not unique word, doesn't make a new word, it just adds the current page
						getWordByLetters(buffer1).addPageToWord(currentPage);
				}
			}else{
					//this is just the case that the word is a stop word, do nothing
			}
		}
		//read in next word/convert it to lower case--this increments fin for our while loop as well
		fin>>buffer1;
		for(int i=0;i<strlen(buffer1);i++){
			buffer1[i]=tolower(buffer1[i]);
		}
	}
}

//This reads in our helper file, stores all the stop words in my stopWords char**
//Creates new categories for each category, and adds all the words into it
void readInObject::readInHelperFile(const char* textfile) {
	fstream fin;
	fin.open(textfile);
	char * buffer=new char[80];
	//skips past [stop]
	fin.getline(buffer,80);
	//gets first stop word/converts to lower
	fin>>buffer;
	for(int i=0;i<strlen(buffer);i++){
		buffer[i]=tolower(buffer[i]);
	}
	//reads in a stop word until it gets to the '[' before 'categories'
	//adds each stop word to my stop word list
	while(buffer[0]!='['){
		if(notStopWord(buffer)){
			addStopWord(buffer);
		}
		fin>>buffer;
		for(int i=0;i<strlen(buffer);i++){
			buffer[i]=tolower(buffer[i]);
		}
	}
	fin.close();

	fstream fin1;
	fin1.open(textfile);
	fin1.getline(buffer,80);
	//this just loops through the helper file from the beginning till its
	//at the line of '[category]'
	while(strcmp(buffer,"[category]")!=0){
		fin1.getline(buffer,80);
		for(int i=0;i<strlen(buffer);i++){
			buffer[i]=tolower(buffer[i]);
		}
	}
	//this loops through the rest of lines just to count how many categories there are
	fin1.getline(buffer,80);
	int numOfCats=1;
	while(!fin1.eof()){
		fin1.getline(buffer,80);
		numOfCats++;
	}
	fin1.close();

	//this loops till we are at the start of categories again
	fstream fin2;
	fin2.open(textfile);
	while(strcmp(buffer,"[category]")!=0){
		fin2.getline(buffer,80);
	}
	//this loops through each line and creates a category with the first word of that line
	for(int i=0;i<numOfCats;i++){
		fin2>>buffer;
		for(int i=0;i<strlen(buffer);i++){
			buffer[i]=tolower(buffer[i]);
		}
		addCategoryToList(buffer);
		fin2.getline(buffer,80);
	}
	fin2.close();

	//loop through file till start of categories list again
	fstream fin3;
	fin3.open(textfile);
	while(strcmp(buffer,"[category]")!=0){
		fin3.getline(buffer,80);
	}
	//loops through each line of the file adding each category word to its category
	int countCateg=0;
	while(countCateg<numOfCats){
		if(countCateg+1 != numOfCats){
			char * NextCatName=new char[strlen(categList[countCateg+1].getName())+1];
			strcpy(NextCatName,categList[countCateg+1].getName());
			fin3>>buffer;	//skip past first categ name
			fin3>>buffer;	//skip past = sign
			fin3>>buffer;	//gets first category word
			for(int i=0;i<strlen(buffer);i++){
						buffer[i]=tolower(buffer[i]);
			}
			//it knows when to stop getting next word with fin3>>buffer because the next word would
			//equal the next category's name
			while(strcmp(buffer,NextCatName)!=0){
				getCategoryByIndex(countCateg).addCatWord(buffer);
				fin3>>buffer;
				for(int i=0;i<strlen(buffer);i++){
					buffer[i]=tolower(buffer[i]);
				}
			}
			countCateg++;
		}else{			//if at last category of helper file
			fin3>>buffer;	//skip past = sign
			while(!fin3.eof()){
				fin3>>buffer;
				for(int i=0;i<strlen(buffer);i++){
					buffer[i]=tolower(buffer[i]);
				}
				getCategoryByIndex(countCateg).addCatWord(buffer);
			}
			countCateg++;
		}
	}
	fin3.close();

}

//just a simple sort algorithm to order words in wordlist based on alphabetical
//order
void readInObject::sortWords(){
	Word temp=wordList[0];
	for(int i=0;i<numWords;i++){
		for(int j=i+1;j<numWords;j++){
			if(strcmp(wordList[i].getLetters(),wordList[j].getLetters())>0){
				temp=wordList[i];
				wordList[i]=wordList[j];
				wordList[j]=temp;
			}
		}
	}
}

//this combines the words that are in categories to the category titles.
//it first makes a word if one doesn't already exist for that category.
//Then it makes sure that the page array of the new word containing the category
//title contains the page number of all its member's pages
void readInObject::groupPages() {
	for(int i=0;i<numCateg;i++){
		//if the category title didn't appear in the file, make a word with it
		if(isUniqueWord(categList[i].getName())==true){
			Word temp(categList[i].getName());
			for(int j=0;j<numWords;j++){
				if(wordList[j].isInCategory()){
					if(strcmp(wordList[j].getMyCategory(),temp.getLetters())==0){
						for(int m=0;m<wordList[j].getNumPages();m++){
							temp.addPageToWord(wordList[j].getPageByIndex(m));
						}
					}
				}
			}
			addWord(temp);
		}else{    //if category title did appear in text just combine page arrays
			Word temp1=getWordByLetters(categList[i].getName());
			for(int j=0;j<numWords;j++){
				if(wordList[j].isInCategory()){
					if(strcmp(wordList[j].getMyCategory(),temp1.getLetters())==0){
						for(int m=0;m<wordList[j].getNumPages();m++){
							temp1.addPageToWord(wordList[j].getPageByIndex(m));
						}
					}
				}
			}
			getWordByLetters(categList[i].getName())=temp1;
		}
	}
}

//This adds a category to our list using 'categName'
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

//this adds a word to our wordlist
//has to create a new temporary wordlist that has
//room for new addition
void readInObject::addWord(Word& tempWord) {
	if(numWords==0){
		wordList=new Word[1];
		wordList[0]=tempWord;
		numWords++;
	}else{
		Word * tempWordList=new Word[numWords+1];
		for(int i=0;i<numWords;i++){
			tempWordList[i]=wordList[i];
		}
		tempWordList[numWords]=tempWord;
		delete []wordList;
		wordList=tempWordList;
		numWords++;
	}
}

//this adds the stop word to our stopwords **
void readInObject::addStopWord(char *tempStopWord){
	for(int i=0;i<strlen(tempStopWord);i++){
		tempStopWord[i]=tolower(tempStopWord[i]);
	}
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

//this prints our indexed words in the form that we want for submission to the file arg
//tricky part is having any words that put a line in the file over 50 to wrap.
//i.e. if indices of 47,48,49 at line is '15,' referring to page 15 and the comma to separate
//it from the next page I will list.  Let's say the next page is 20, that will get wrapped
//to next line with an indent
void readInObject::printAnswer(const char * outputfile){
	ofstream fout;
	fout.open(outputfile);
	//first group words
	groupPages();
	//sort words alphabetically
	sortWords();
	int i=0;
	//figures out current letter
	char * current=new char[wordList[0].getNumLetters()+1];
	strcpy(current,wordList[0].getLetters());
	char currentLetter=current[0];
	fout<<"["<<char(toupper(currentLetter))<<"]"<<endl;
	//loops through all words in list
	while(i<numWords){
		int charCount=0;	//this will count how many characters ive printed on each line
		if(wordList[i].getLetters()[0]==currentLetter){
			if(wordList[i].isInCategory()==true){
				//remember for words in a category, refer the person to the category header
				fout<<"For "<<wordList[i].getLetters()<<", see "<<wordList[i].getMyCategory()<<"."<<endl;
			}else{
				//increases my characters on line count to past the current word and the ": "
				charCount=charCount+strlen(wordList[i].getLetters())+2;
				fout.write(wordList[i].getLetters(),strlen(wordList[i].getLetters()));
				fout.write(": ",2);
				for(int j=0;j<wordList[i].getNumPages();j++){
					//adds the number of digits in my next page to my character in line count
					charCount=charCount+numDigits(wordList[i].getPageByIndex(j));

					//adds two more if not at last page for word to represent ", "
					if(j+1 < wordList[i].getNumPages())charCount=charCount+2;
					//will keep adding pages to line till character count=50
					if(charCount<=50){
						if(j+1 <wordList[i].getNumPages()){
							fout<<wordList[i].getPageByIndex(j)<<", ";
						}
						else{
							fout<<wordList[i].getPageByIndex(j)<<endl;
						}
					}else{
						//once character count=50, moves output to next line and adds indent
						//then resets my character per line count and decrements j to return
						//back to page from last iteration that I haven't printed.
						fout<<endl;
						fout<<"    ";
						charCount=4;
						j--;
					}
				}
			}
			i++;
		}else{
			current=new char[wordList[i].getNumLetters()+1];
			strcpy(current,wordList[i].getLetters());
			currentLetter=current[0];
			fout<<"["<<char(toupper(currentLetter))<<"]"<<endl;
		}
	}
	fout.close();
}

//this was just one of the printer functions I wrote to test my indexing
void readInObject::printIndexedWords() {
	groupPages();
	sortWords();
	for(int i=0;i<numWords;i++){
		char *temp=new char[strlen(wordList[i].getLetters())+1];
		int duh=strlen(wordList[i].getLetters());
		cout<<"Length of Word: "<<duh<<endl;
		strcpy(temp,wordList[i].getLetters());
		cout<<temp<<endl;

		if(wordList[i].isInCategory()){
				char *tempcat=new char[wordList[i].getNumCatLetters()+1];
				cout<<"			I'm in category: ";
				strcpy(tempcat,wordList[i].getMyCategory());
				cout<<tempcat<<endl;
		}
			else{
				cout<<"			I'm not in a category"<<endl;
			}
			cout<<"			The pages I'm on are: ";
			int* tempPageList=new int [wordList[i].getNumPages()];
			tempPageList=wordList[i].getPages();
		for(int j=0;j<wordList[i].getNumPages();j++){
			cout<<tempPageList[j]<<" ";
		}
		cout<<endl;
	}
}

//this prints the categories and their words, for testing purposes
void readInObject::printCategories() {
	for(int i=0;i<numCateg;i++){
		int j=i+1;
		cout<<"Category #"<<j<<"is: "<<categList[i].getName()<<endl;
		cout<<"The words in this category are: "<<endl;
		categList[i].printCatWords();
	}
}
readInObject::~readInObject() {
	// TODO Auto-generated destructor stub
}
