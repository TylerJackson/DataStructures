/*
 * Owner: alex
 * History of all changes:
 * Added ability to parse xml file
 * Added ability to add files to IFI
 * Added ability to add all documents to a document folder
 */

#ifndef DOCUMENTPARSER_H_
#define DOCUMENTPARSER_H_

#include "tinyxml2.h"
#include "PorterStemmer.h"
#include "Document.h"
#include "Word.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <functional>
#include <chrono>

using namespace tinyxml2;

class DocumentParser {
private:
	std::ifstream ifs;
	std::ofstream ofs;
	std::string input;
	std::vector<std::string> stopWords;
	std::vector<Document*> documents;
	std::vector<Word*> words;
	std::vector<std::string> docWords;

	/*
	 * parses the words in the input string into the vector,
	 * including removing punctuation, nonenglish words, and stop words
	 * makes words lowercase, and stems them
	 */
	void parseWords(std::string&, std::vector<std::string>&);

	/*
	 * Loads the previously added words before adding new ones
	 */
	void loadIndexes();

	/*
	 * Adds the new documents to the inverted file index and the document index folder
	 */
	void addNewWordsToIndexes();

public:
	DocumentParser();
	virtual ~DocumentParser();

	/*
	 * Adds all the words in the given XML file
	 */
	void add(std::string);

	/*
	 * Deletes all the documents in the IFI and document index
	 */
	void clearIndex();
};

#endif
