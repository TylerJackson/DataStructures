/*
 * readInObject.h
 *
 *  Created on: Sep 11, 2013
 *      Author: tgjackson
 */
#include "Category.h"
#ifndef READINOBJECT_H_
#define READINOBJECT_H_

class readInObject {
public:
	readInObject();
	void readInTextFile(const char * textfile);
	bool notStopWord(char * wordTemp);
	void addStopWord(char *tempStopWord);
	void readInHelperFile(const char * textfile);
	char * getStopWord(int index);
	int getNumStopWords();
	int getNumCategories();
	Category& getCategoryByIndex(int index);
	Category& getCategoryByName(char * tempName);
	void addCategoryToList(char * categName);
	void printCategories();
	virtual ~readInObject();
private:
	int currentPage;
	char ** stopWords;
	int numStopWords;
	Category * categList;
	int numCateg;
};

#endif /* READINOBJECT_H_ */
