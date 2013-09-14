/*
 * Word.h
 *
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
	Word& operator=(const Word& rhs);
	Word (const Word& orig);
	void addPageToWord(int pageNumb);
	char * getLetters();
	int getNumLetters();
	virtual ~Word();
private:
	char * letters;
	int * pages;
	char * category;
	int numLetters;
	bool inCategory;
	int numPages;
};

#endif /* WORD_H_ */
