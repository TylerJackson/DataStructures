#include "Document.h"

using namespace std;

Document::Document() {
	ID = 0;
}

Document::~Document() {

}

Document::Document(int a, string& b, string& c, vector<string>& d, string& e, string& f) {
	ID = a;
	title = b;
	text = c;
	setWords(d);
	date = e;
	contributor = f;
}

void Document::setID(int allocator) {
	ID = allocator;
}

int Document::getID() {
	return ID;
}

void Document::setTitle(string& allocator) {
	title = allocator;
}

string Document::getTitle() {
	return title;
}

void Document::setText(string& allocator) {
	text = allocator;
}

string Document::getText() {
	return text;
}

void Document::setWords(vector<string>& allocator) {
	for(unsigned int i=0; i<allocator.size(); i++)//for all new words
	{
		bool isRepeat = false;
		for(unsigned int j=0; j<words.size(); j++)//for all existing words
			if(allocator[i] == words[j])
			{
				isRepeat = true;
				frequency[j]++;
				break;
			}
		if(isRepeat == false)
		{
			words.push_back(allocator[i]);
			frequency.push_back(1);
		}
	}
}

vector<string> Document::getWords() {
	return words;
}

void Document::setFrequency(vector<int> allocator) {
	frequency = allocator;
}

vector<int> Document::getFrequency() {
	return frequency;
}

void Document::setDate(string& allocator) {
	date = allocator;
}

string Document::getDate() {
	return date;
}

void Document::setContributor(string& allocator) {
	contributor = allocator;
}

string Document::getContributor() {
	return contributor;
}
