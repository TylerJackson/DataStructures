/*
 * readInObject.h
 *	This is my read In Object Class.  Basically it handles
 *	reading in and processing all the data.
 *	It then prints the processed data out to the screen.
 *	It holds the list of categories and their data in a category list.
 *	It hold the list of words in a word list.
 *  Created on: Sep 11, 2013
 *      Author: tgjackson
 */
#include "Category.h"
#include "Word.h"
#ifndef READINOBJECT_H_
#define READINOBJECT_H_

class readInObject {
public:
	readInObject();
	Word& getWordByLetters(char * tempLetters);
	Category& getCategoryByIndex(int index);
	Category& getCategoryByName(char * tempName);
	char * getStopWord(int index);
	char * getCategoryNameByCatWord(char * catWord);
	int getNumStopWords();
	int getNumCategories();
	int numDigits(int n);
	bool notStopWord(char * wordTemp);
	bool isUniqueWord(char *wordtemp);
	bool isInCategoryFromList(char *wordtemp);
	void readInTextFile(const char * textfile);
	void readInHelperFile(const char * textfile);
	void sortWords();
	void groupPages();
	void addCategoryToList(char * categName);
	void addWord(Word& tempWord);
	void addStopWord(char *tempStopWord);
	void printAnswer(const char * outputfile);
	void printIndexedWords();
	void printCategories();
	virtual ~readInObject();
private:
	int currentPage;
	int numStopWords;
	int numCateg;
	int numWords;
	char ** stopWords;
	Category * categList;
	Word * wordList;
};

#endif /* READINOBJECT_H_ */
