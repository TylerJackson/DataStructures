/*	Tyler Jackson
 * 	Date: Nov. 16, 2013
 *
 * 	AVLIF.cpp
 *
 *		This class is my AVLIF class.  It inherits from the Index IF class.  It basically handles
 *	all functionality for the user to access the AVL tree.  It loads the index into an avl tree
 *	as well as handles searching the tree and returning desired results
 */

#include "AVLIF.h"

#include <sstream>

using namespace std;

//basic constructor
AVLIF::AVLIF() {
	tree = new AVLTree();
	Qproc = new QueryProcessor();
}

//searches the tree based on a query and returns ranked results
void AVLIF::search(string query){
	setResultsFromBoolean(query);
	printRankedResults();
}

//this indexes the file based on a filepath to the inverted file index
void AVLIF::index(string filepath){
	ifstream fin;
	fin.open(filepath.c_str());
	if(!fin.is_open())
		cout << "File didn't open" << endl;
	int too = 1;
	while(!fin.eof()){
//		cout << "line #: " << too << endl;
		too++;
		//initialize word to add to AVL tree for each word
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

		//store the wordName into the word
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
			//insert the wordObject into the tree
			tree->insertWord(tempWord);
	}
}

//this takes a query and passes it to the processor.
//then this uses set union/ set intersection / set difference to find the corresponding docs
void AVLIF::setResultsFromBoolean(string query){

	//pass query to processor
	Qproc->setQuery(query);
	string * ands = Qproc->getAnds();
	string * ors = Qproc->getOrs();
	string * nots = Qproc->getNots();
	AssocArray tempResults;
	AssocArray::iterator tempResults_iter(tempResults.begin());
	AssocArray obj1;
	int numberResultsFromAnd = 0;

	//if there were and words in the query go in here
	if (Qproc->getNumAnds() > 0){
		if(tree->wordExists(ands[0]))
			obj1 = tree->getWord(ands[0]).getDocFreq();
		for(int i = 1;i < Qproc->getNumAnds(); i++){
			AssocArray temp;
			if(tree->wordExists(ands[i])){
				temp = tree->getWord(ands[i]).getDocFreq();
			}
			//get docs from the intersection of the and words
			set_intersection(obj1.begin(),obj1.end(),temp.begin(),temp.end(),
					inserter(tempResults,tempResults_iter),obj1.value_comp() );
			obj1 = tempResults;

			tempResults.clear();
		}
		tempResults = obj1;
		numberResultsFromAnd = tempResults.size();
	}
	//if there are any or words in the query
	if (Qproc->getNumOrs() > 0){
		if(tree->wordExists(ors[0])){
			AssocArray temp1;
			AssocArray::iterator temp1_iter(temp1.begin());
			obj1 = tree->getWord(ors[0]).getDocFreq();
			set_union(obj1.begin(),obj1.end(),tempResults.begin(),tempResults.end(),
					inserter(temp1,temp1_iter),obj1.value_comp() );
			obj1.clear();
			obj1 = temp1;
			temp1.clear();
		}
		// add union of current results and the or words doc lists
		for(int i = 1;i < Qproc->getNumOrs(); i++){
			AssocArray temp;
			if(tree->wordExists(ors[i])){
				temp = tree->getWord(ors[i]).getDocFreq();
			}
			// set union of results and current or words doc list
			set_union(obj1.begin(),obj1.end(),temp.begin(),temp.end(),
					inserter(tempResults,tempResults_iter),obj1.value_comp() );
			obj1 = tempResults;
			tempResults.clear();
		}
		tempResults = obj1;
	}
	//if there are any not words from the query go here
	for(int i = 0;i < Qproc->getNumNots(); i++){
		AssocArray obj1 = tempResults;
		tempResults.clear();
		AssocArray temp;
		if(tree->wordExists(nots[i])){
			temp = tree->getWord(nots[i]).getDocFreq();
		}
		// exclude any docs that are in the results list and also a part of the current
		//not word's doc list
		set_difference(obj1.begin(),obj1.end(),temp.begin(),temp.end(),
				inserter(tempResults,tempResults_iter),obj1.value_comp() );
	}
	//store final set of doc lists into results, and then apply a tf-idf score to each doc
	results = tempResults;
	rankResults(numberResultsFromAnd);
}

//print the results not in order--used to compare the results to the ranked results
void AVLIF::printResults(){
	AssocArray::const_iterator results_iter;
	cout << "The results from the query are: " << endl;
	for(results_iter = results.begin(); results_iter != results.end();++results_iter){
		cout << " 		Doc ID: " << results_iter->first << endl;
		cout << "		Freq  : " << results_iter->second << endl;
	}
}

//give each doc a tf-idf score based on the query type
void AVLIF::rankResults(int numResultsFromAnd){
	FinalRankedResultsInverse.clear();
	//if there are any and words in the query
	if(Qproc->getNumAnds() > 0){
		AssocArray::iterator results_iter;
		//iterate over each doc id in results calling setTFIDFAnds
		for(results_iter = results.begin();results_iter!=results.end();++results_iter){
			int docid = results_iter->first;
			double currTFIDF = results_iter->second;
			//this is what actually sets the tf-idf score
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
			//this is what actually sets the tf-idf score
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

//print the avl tree--calls the avl tree print function
void AVLIF::print(){
	tree->print();
}

//print the ranked results-- this sorts the results by their tf-idf and prints them in the
//format we wanted for display
//also allows the user to request to see more info on a certain doc based
void AVLIF::printRankedResults() {
	AssocArray::const_iterator results_iter;
	cout << "Ranked results from your query:" << endl;

	string filepath = "/home/tgjackson/workspace/FinalProjectDSRepo/documentIndex/";

	//sort results into vector based on tf-idf score
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
		getline(ifs, fileLine);
		cout << (i+1) << ": " << fileLine << ". TF/IDF score: " << sortedResults[i].first << endl;
		if(i == 14)
			break;
		ifs.close();
	}

	//get the user input to see if they want more info on a document
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

	//print the extra info on the doc if they requested
	ifs.open(filepathTemp);
	getline(ifs, fileLine);
	while(ifs.good())
	{
		getline(ifs, fileLine);
		cout << fileLine << endl;
	}
	ifs.close();
}

//destructor for interface
AVLIF::~AVLIF() {
	delete tree;
	delete Qproc;
}

//this sets the tf-idf score for results that came from the AND part of the query
void AVLIF::setTFIDFANDS(int docID, double & tfIDF, int numResultsFromAnd){
	string * ands = Qproc->getAnds();
	//first check if word is in all ands
	bool inAllAnds = true;
	for(int i = 0;i < Qproc->getNumAnds();i++){
		AssocArray andarray = tree->getWord(ands[i]).getDocFreq();
		if(andarray.count(docID) < 1 )
			inAllAnds = false;
	}
	//if this document is in all ands then we want to calc the tfIDF
	double minTF = 0;
	if(inAllAnds){
		for(int i = 0;i < Qproc->getNumAnds();i++){
			AssocArray andarray = tree->getWord(ands[i]).getDocFreq();
			if(andarray[docID] < minTF || minTF == 0)
				minTF = andarray[docID];
		}
	}
		//////////////CALC TFIDF = min tf from all the words in the and query multiplied
		////////////////////////	by  (number of docsTotal/ #of doc results from and query)
		double IDF = 700000.0/(numResultsFromAnd + 1.0);
		tfIDF = IDF * minTF;
}

//this sets the tf-idf score for results that came from the AND part of the query
void AVLIF::setTFIDFORS(int docID, double & tfIDF){
	string * ors = Qproc->getOrs();

		//if there were 'and' words in the query add the or tf-idf for each doc for each word to the
		//and tf-idf for that doc

		//loop through each or word
		double tempTFIDF = 0;

		for( int u =0; u < Qproc->getNumOrs(); u++){
			AssocArray tempArray;
			if(tree->wordExists(ors[u])){
				tempArray= tree->getWord(ors[u]).getDocFreq();
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
