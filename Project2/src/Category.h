/*
 * Category.h
 *
 *  Created on: Sep 13, 2013
 *      Author: tgjackson
 */

#ifndef CATEGORY_H_
#define CATEGORY_H_
#include <cstring>

class Category{
public:
	Category();
	Category(char * name);
	Category& operator=(const Category& rhs);
	Category (const Category& orig);
	char* getName();
	void addCatWord(char * wordTemp);
	char * getCatWord(int index);
	int getNumCatWords();
	virtual ~Category();
	void printCatWords();
private:
	char * name;
	char ** categoryWords;
	int numCatWords;
};

#endif /* CATEGORY_H_ */

