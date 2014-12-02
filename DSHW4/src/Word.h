#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <vector>
#include <map>

using namespace std;
typedef std::map<int,double> AssocArray;

class Word {
private:
	string word;
	vector<int> docIDs;
	vector<int> docFrequencies;
	int totFreq;
	AssocArray docFreq;			//key = docid, value = docfreq
	AssocArray docWeight;		//key = docid, value = docWeight

public:
	Word();
	Word(string s);
	Word& operator=(const Word& rhs);
	bool operator<(Word& tempWord);

	virtual ~Word();

	void setWord(string);
	string getWord();
	void addID(int);
	vector<int> getIDs();
	void addFrequency(int);
	vector<int> getFrequencies();
	int getTotFreq();
	void addIDFreqPair(int ID,double Freq);
	void printDocsIDs();
	AssocArray getDocFreq();
};

#endif
