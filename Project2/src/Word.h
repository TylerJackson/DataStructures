/*
 * Word.h
 *	This is my word class, it contains each word, and also an integer array
 *	that holds the list of pages that word is found on.
 *	The Word object also has a category char * that is set to the name of the
 *	category the word is in, if its in a category.
 *  Created on: Sep 12, 2013
 *      Author: tgjackson
 */

#ifndef WORD_H_
#define WORD_H_

class Word {
public:
	Word();
	Word(char * letterTemp,char * categoryTemp);
	Word(char * letterTemp);
	Word (const Word& orig);
	Word& operator=(const Word& rhs);
	void addPageToWord(int pageNumb);
	bool isInCategory();
	char * getLetters();
	char * getMyCategory();
	int * getPages();
	int getNumLetters();
	int getPageByIndex(int n);
	int getNumPages();
	int getNumCatLetters();
	virtual ~Word();
private:
	int numCatLetters;
	char * letters;
	int * pages;
	char * category;
	int numLetters;
	bool inCategory;
	int numPages;
};

#endif /* WORD_H_ */
