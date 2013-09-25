/*
 * Category.h
 *	This is my category class.  It holds the category, stored in name,
 *	and each word in that category, stored in categoryWords.
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
	void addCatWord(char * wordTemp);
	char* getName();
	char * getCatWord(int index);
	int getNumCatWords();
	void printCatWords();
	virtual ~Category();
private:
	char * name;
	char ** categoryWords;
	int numCatWords;
};

#endif /* CATEGORY_H_ */

