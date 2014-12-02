/*
 * Owner: alex
 * History of changes
 * Added member variables and getters and setters
 * Added associative arrays for mapping
 */

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
        AssocArray docFreq;
        //key = docID, value = docFreq
        AssocArray docWeight;
        //key = docID, value = docWeight

public:
        Word();
        Word(string s);
        Word& operator=(const Word& rhs);
        bool operator<(Word& tempWord);

        virtual ~Word();
        void addFrequencyToID(int id, double freq);
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
