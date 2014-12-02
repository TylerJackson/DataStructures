#include "Word.h"
#include <iostream>
using namespace std;

Word::Word() {
        word = "";
        totFreq = 0;
}

Word::~Word() {

}

void Word::setWord(string allocator) {
        word = allocator;
}

string Word::getWord() {
        return word;
}

int Word::getTotFreq() {
        return totFreq;
}

void Word::addID(int allocator) {
        docIDs.push_back(allocator);
}

vector<int> Word::getIDs() {
        return docIDs;
}

void Word::addFrequency(int allocator) {
        docFrequencies.push_back(allocator);
}

Word::Word(string s) {
        word = s;
        totFreq = 0;
}

vector<int> Word::getFrequencies() {
        return docFrequencies;
}

bool Word::operator <(Word& tempWord) {
        //cout << "CALLED OVERLOAD" << endl;
        return word < tempWord.getWord();
}

Word& Word::operator=(const Word &rhs){
        this->word = rhs.word;
        this->totFreq = rhs.totFreq;
        this->docFreq = rhs.docFreq;
        return *this;
}
void Word::addIDFreqPair(int ID,double Freq){
        docFreq.insert(pair<int,double>(ID,Freq));
}

void Word::printDocsIDs(){
        AssocArray Temp(docFreq.begin(),docFreq.end());
        AssocArray::const_iterator it;
        for(it = Temp.begin(); it != Temp.end();++it){
                cout << " Doc ID: " << it->first << endl;
                cout << " Doc Freq: " << it->second << endl;
        }
}

AssocArray Word::getDocFreq() {
        return docFreq;
}

//only call if this id is already in the list
void Word::addFrequencyToID(int id, double freq) {
        docFreq[id]+=freq;
}
