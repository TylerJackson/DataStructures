/*
 * Owner: alex
 * History of changes:
 * Added all getters and setters
 * Added ability to calculate word frequency as words are added to the object
 */
#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>
#include <vector>

using namespace std;

class Document {
private:
	int ID;
	string title;
	string text;
	vector<string> words;
	vector<int> frequency;
	string date;
	string contributor;

public:
	Document();
	Document(int, string&, string&, vector<string>&, string&, string&);
	virtual ~Document();

	void setID(int);
	int getID();
	void setTitle(string&);
	string getTitle();
	void setText(string&);
	string getText();

	/*
	 * Given a vector of words, deletes repeats and adds frequencies to an associative array
	 */
	void setWords(vector<string>&);
	vector<string> getWords();
	void setFrequency(vector<int>);
	vector<int> getFrequency();
	void setDate(string&);
	string getDate();
	void setContributor(string&);
	string getContributor();

};

#endif
