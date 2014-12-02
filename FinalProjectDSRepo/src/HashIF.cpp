/* Tyler Jackson
 * Date: Nov. 16, 2013
 * HashIF.h
 *
 *		This is my Hash IF header class that briefly describes the functionality
 *	The AVL interface class inherits from the IndexIF class and handles basically all
 *	functionality on the AVL Tree side of the project.
 */

#include "HashIF.h"
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
using namespace std;

//default constructor
HashIF::HashIF() {
	hashTable = new HashTab();
	Qproc = new QueryProcessor();
}
//search hash table using query and print them to console
void HashIF::search(string query){
	setResultsFromBoolean(query);
	printRankedResults();
}
//load index into hashtable from the inverted file index filepath
void HashIF::index(string filepath) {
	ifstream fin;
	fin.open(filepath.c_str());
	if(!fin.is_open())
		cout << "Did not open file" << endl;
	while(!fin.eof()){

		//initialize word object to add to hash table for each word
		Word tempWord;

		//get next line and store it in buffer
		char * buffer = new char [8000];
		fin.getline(buffer,8000);

		//get wordname and store to wordNameTemp
		//line iterator will point to first comma after this action
		int commaIndex = 0;
		while(buffer[commaIndex] != ','){
			commaIndex ++;
		}
		char * wordNameTemp = new char [commaIndex + 1];
		for(int j = 0;j < commaIndex; j++){
			wordNameTemp[j] = buffer[j];
		}
		wordNameTemp[commaIndex] = 0;

		//store the wordName into the word object
		tempWord.setWord(wordNameTemp);

		int startIndex = commaIndex + 1;			//starting index of first doc ID
		for(int i = startIndex;i < strlen(buffer) - 1; i++){

				//get each Doc ID and store to nextID
				commaIndex = i + 1;
				while(buffer[commaIndex] != ','){
					commaIndex ++;
				}
				char * nextID = new char [commaIndex - i + 1];
				for(int j = 0;j < commaIndex - i; j++){
					nextID[j] = buffer[i + j];
				}
				nextID[commaIndex - i] = 0;
				int ID = atoi(nextID);

				//get corresponding frequency and store to nextFreq
				i = commaIndex + 1;
				commaIndex ++;
				while(buffer[commaIndex] != ','){
					commaIndex++;
				}
				char * nextFreq = new char [commaIndex - i + 1];

				for(int j = 0;j < commaIndex - i; j++){
					nextFreq[j] = buffer[i + j];
				}
				nextFreq[commaIndex - i] = 0;
				int Freq = atoi(nextFreq);
				double frequency = (double)(Freq);

				//store the doc ID and the freq of the word in that Doc into the word object
				tempWord.addIDFreqPair(ID,frequency);
				i = commaIndex;
		}
			//insert word object into hash table
			hashTable->insert(tempWord);
	}
}

//print hashtable--calls HashTab print function
void HashIF::print(){
	hashTable->print();
}

//print the results prior to having the tf-idf set up
void HashIF::printResults(){
	AssocArray::const_iterator results_iter;
	cout << "The results from the query are: " << endl;

	for(results_iter = results.begin(); results_iter != results.end();++results_iter){
		cout << " 		Doc ID: " << results_iter->first << endl;
		cout << "		Freq  : " << results_iter->second << endl;
	}
}

//print the ranked results based on their tf-idf score
//allows the user to ask for more info from a certain doc
void HashIF::printRankedResults(){
	AssocArray::const_iterator results_iter;
	cout << "Ranked results from your query:" << endl;

	string filepath = "/home/tgjackson/workspace/FinalProjectDSRepo/documentIndex/";

	//sort results into vector based on their tf-idf score
	vector<pair<double, int>> sortedResults;
	for(results_iter = FinalRankedResultsInverse.begin(); results_iter != FinalRankedResultsInverse.end();++results_iter){
		pair <double, int> pair1(results_iter->second, results_iter->first);
		sortedResults.push_back(pair1);
	}
	sort(sortedResults.rbegin(), sortedResults.rend());

	//print first 15 results
	for(unsigned int i=0; i<sortedResults.size(); i++){
		string filepathTemp = filepath;
		string sID = static_cast<ostringstream*>( &(ostringstream() << sortedResults[i].second) )->str();
		filepathTemp += sID;
		ifstream ifs;
		string fileLine;
		ifs.open(filepathTemp);
//		cout << " filepath: " << filepathTemp << endl;
		if(ifs.is_open())
			cout << "The file opened" << endl;
		getline(ifs, fileLine);
		cout << (i+1) << ": " << fileLine << ". TF/IDF score: " << sortedResults[i].first << endl;
		if(i == 14)
			break;
		ifs.close();
	}

	//allow the user to ask for more info from a particular document
	string input;
	cout << "Enter result number to print the document, or 0 for interactive menu: ";
	cin >> input;
	int openDoc = stoi(input);
	openDoc--;
	string sID = static_cast<ostringstream*>( &(ostringstream() << sortedResults[openDoc].second) )->str();
	string filepathTemp = filepath;
	filepathTemp += sID;
	ifstream ifs;
	string fileLine;
	ifs.open(filepathTemp);
	getline(ifs, fileLine);
	while(ifs.good())
	{
		getline(ifs, fileLine);
		cout << fileLine << endl;
	}
	ifs.close();
}

//set the results of the query
void HashIF::setResultsFromBoolean(string query) {
	//first pass the query to the processor
	Qproc->setQuery(query);
	string * ands = Qproc->getAnds();
	string * ors = Qproc->getOrs();
	string * nots = Qproc->getNots();
	AssocArray tempResults;
	AssocArray::iterator tempResults_iter(tempResults.begin());
	AssocArray obj1;
	int numberResultsFromAnd = 0;

	//if there were any and words in the query
	if (Qproc->getNumAnds() > 0){
		if(hashTable->wordExists(ands[0]))
			obj1 = hashTable->getWord(ands[0]).getDocFreq();
		for(int i = 1;i < Qproc->getNumAnds(); i++){
			AssocArray temp;
			if(hashTable->wordExists(ands[i])){
				temp = hashTable->getWord(ands[i]).getDocFreq();
			}
			//find intersection of all the "and" words docs
			set_intersection(obj1.begin(),obj1.end(),temp.begin(),temp.end(),
					inserter(tempResults,tempResults_iter),obj1.value_comp() );
			obj1 = tempResults;
			tempResults.clear();
		}
		tempResults = obj1;
		numberResultsFromAnd = tempResults.size();
	}
	//if there were and Or words in the query
	if (Qproc->getNumOrs() > 0){
		if(hashTable->wordExists(ors[0])){
			AssocArray temp1;
			AssocArray::iterator temp1_iter(temp1.begin());
			obj1 = hashTable->getWord(ors[0]).getDocFreq();
			//add all the docs from each "or" word to the query
			set_union(obj1.begin(),obj1.end(),tempResults.begin(),tempResults.end(),
					inserter(temp1,temp1_iter),obj1.value_comp() );
			obj1.clear();
			obj1 = temp1;
			temp1.clear();
		}
		for(int i = 1;i < Qproc->getNumOrs(); i++){
			AssocArray temp;
			if(hashTable->wordExists(ors[i])){
				temp = hashTable->getWord(ors[i]).getDocFreq();
			}
			//add all the docs from each "or" word to the query
			set_union(obj1.begin(),obj1.end(),temp.begin(),temp.end(),
					inserter(tempResults,tempResults_iter),obj1.value_comp() );
			obj1 = tempResults;
			tempResults.clear();
		}
		tempResults = obj1;
	}
	//if any not words
	for(int i = 0;i < Qproc->getNumNots(); i++){
		AssocArray obj1 = tempResults;
		tempResults.clear();
		AssocArray temp;
		if(hashTable->wordExists(nots[i])){
			temp = hashTable->getWord(nots[i]).getDocFreq();
		}
		//take all the docs from the "NOT" words off the results list
		set_difference(obj1.begin(),obj1.end(),temp.begin(),temp.end(),
				inserter(tempResults,tempResults_iter),obj1.value_comp() );
	}
	//store all results in here
	results = tempResults;
	//give the results tf-idf scores
	rankResults(numberResultsFromAnd);
}
//rank the results from the results list based on if they came from the AND or the OR in the
//query
void HashIF::rankResults(int numResultsFromAnd){
	FinalRankedResultsInverse.clear();

	//if there are any and words in the query
	if(Qproc->getNumAnds() > 0){
		AssocArray::iterator results_iter;
		//iterate over each doc id in results calling setTFIDFAnds
		for(results_iter = results.begin();results_iter!=results.end();++results_iter){
			int docid = results_iter->first;
			double currTFIDF = results_iter->second;
			//actually sets the tf-idf score
			setTFIDFANDS(docid, currTFIDF, numResultsFromAnd);
			pair<int,double> pair2 (docid,currTFIDF);
			FinalRankedResultsInverse.insert(pair2);
		}
	}
	//if there were any or words in the query
	if(Qproc->getNumOrs() > 0){
		AssocArray::iterator results_iter;
		//iterate over each doc id in results calling setTFIDFOrs
		for(results_iter = results.begin();results_iter!=results.end();++results_iter){
			int docID = results_iter->first;
			double currTFIDF = results_iter->second;
			//actually set the tf-idf score
			setTFIDFORS(docID,currTFIDF);
			if(FinalRankedResultsInverse.count(docID) > 0 )
				FinalRankedResultsInverse[docID] += currTFIDF;
			else{
				pair<int,double> pair2 (docID,currTFIDF);
				FinalRankedResultsInverse.insert(pair2);
			}
		}
	}
}
//this sets the tf-idf score for all results from the AND word
void HashIF::setTFIDFANDS(int docID, double & tfIDF, int numResultsFromAnd){
	string * ands = Qproc->getAnds();
	//first check if word is in all ands
	bool inAllAnds = true;
	for(int i = 0;i < Qproc->getNumAnds();i++){
		AssocArray andarray = hashTable->getWord(ands[i]).getDocFreq();
		if(andarray.count(docID) < 1 )
			inAllAnds = false;
	}
	//if this document is in all ands then we want to calc the tfIDF
	double minTF = 0;
	if(inAllAnds){
		for(int i = 0;i < Qproc->getNumAnds();i++){
			AssocArray andarray = hashTable->getWord(ands[i]).getDocFreq();
			if(andarray[docID] < minTF || minTF == 0)
				minTF = andarray[docID];
		}
	}
		//////////////CALC TFIDF =
		double IDF = 700000.0/(numResultsFromAnd + 1.0);
		tfIDF = IDF * minTF;
}
//set the tf-idf score for any results from the OR in the query
void HashIF::setTFIDFORS(int docID, double & tfIDF){
	string * ors = Qproc->getOrs();

		//if there were 'and' words in the query add the or tf-idf for each doc for each word to the
		//and tf-idf for that doc

		//loop through each or word
		double tempTFIDF = 0;

		for( int u =0; u < Qproc->getNumOrs(); u++){
			AssocArray tempArray;
			if(hashTable->wordExists(ors[u])){
				tempArray= hashTable->getWord(ors[u]).getDocFreq();
			}
			//if current doc is apart of this words doc list add its tfidf
			if(tempArray.count(docID) > 0){
				double tempTF = tempArray[docID];
				double tempIDF = 700000.0/(tempArray.size()+1.0);
				tempTFIDF += tempTF*tempIDF;
			}
		}
		tfIDF += tempTFIDF;
}
//destructor
HashIF::~HashIF() {
	delete hashTable;
	delete Qproc;
}

