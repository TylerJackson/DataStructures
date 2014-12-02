/* Tyler Jackson
 * 11/23/13
 *
 * QueryProcessor.cpp
 *
 *		This is our query processor class.  It takes a query in from the UI and can parse
 *	it based on the AND OR NOT key words.  It stores each in its own string array to use when
 *	pulling results from our index objects
 */

#include "QueryProcessor.h"
#include "PorterStemmer.h"
using namespace std;

//default constructor
QueryProcessor::QueryProcessor() {
	query = "";
	setQueryType();
	setIndicesOfBools();
	setStopWordsFromFile();
}

//constructor with the query as an argument
QueryProcessor::QueryProcessor(string tempQuery) {
	query = tempQuery;
	setQueryType();
	setIndicesOfBools();
	setStopWordsFromFile();
	setAnds();
	setOrs();
	setNots();
	stemStringArray(andWords,numAnds);
	stemStringArray(orWords,numOrs);
	stemStringArray(notWords,numNots);

}
//if you use default constructor this allows you to set the query
void QueryProcessor::setQuery(string tempQuery){
	query = tempQuery;
	setQueryType();
	setIndicesOfBools();
	setAnds();
	setOrs();
	setNots();
	stemStringArray(andWords,numAnds);
	stemStringArray(orWords,numOrs);
	stemStringArray(notWords,numNots);

}
//takes the query and parses it to find which words are after OR
void QueryProcessor::setOrs() {
	if(numOrs != 0){
		delete []orWords;
	}
	int numOrsTemp = 0;
	numOrs = 0;
	for(int i = orIndex + 3; i< query.length() &&  i!= andIndex && i!= notIndex; i++){

		while(query[i] != ' '){
			if(i + 1 != query.length())
				i++;
			else break;
		}
		numOrsTemp ++;
	}
	orWords = new string [numOrsTemp];
	//if all three exist in query
	if(containsAnd == true && containsOr == true && containsNot == true){
		//if OR comes first
		if(orIndex < andIndex && orIndex < notIndex){
				for(int i = orIndex + 3; i< andIndex  &&  i< notIndex; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						orWords[numOrs] = tempWord;
						numOrs++;
					}
				}
		}//go to else if order is AND, OR, NOT
		else if(orIndex > andIndex && orIndex < notIndex){
				for(int i = orIndex + 3; i< notIndex ; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						orWords[numOrs] = tempWord;
						numOrs++;
					}
				}
		}//go to else if order is NOT, OR, AND
		else if(orIndex < andIndex && orIndex > notIndex){
				for(int i = orIndex + 3; i< andIndex ; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						orWords[numOrs] = tempWord;
						numOrs++;
					}
				}
		}//go to else when OR comes last
		else{
			for(int i = orIndex + 3; i< query.length() ; i++){
				int space = i+1;
				while(query[space] != ' '){
					space ++;
					if(space == query.length())
						break;
				}

				int wordLength = space -i + 1;
				char * tempWord = new char [wordLength];
				int iter=0;
				while(i < space){
					tempWord[iter] = query[i] ;
					i++;
					iter++;
				}
				tempWord[wordLength - 1] = 0;
				if(isStopWord(tempWord) == false){
					orWords[numOrs] = tempWord;
					numOrs++;
				}
			}
		}
	}//go to else if query has AND and OR but no NOT
	else if(containsAnd == true && containsOr == true && containsNot == false){
		//if OR is before AND
		if( orIndex < andIndex ){
				for(int i = orIndex + 3; i< andIndex; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						orWords[numOrs] = tempWord;
						numOrs++;
					}
				}
		}//go to else if OR is after AND
		else{
				for(int i = orIndex + 3; i< query.length() ; i++){
					int space = i+1;
					while(query[space] != ' '){
						space ++;
						if(space == query.length())
							break;
					}

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						orWords[numOrs] = tempWord;
						numOrs++;
					}
				}
		}
	}//go to else if query has OR and NOT but no AND
	else if(containsOr == true && containsAnd == false && containsNot == true){
		//if OR is before NOT
		if( orIndex < notIndex ){
				for(int i = orIndex + 3; i< notIndex; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						orWords[numOrs] = tempWord;
						numOrs++;
					}
				}
		}//go to else if OR is after NOT
		else{
				for(int i = orIndex + 3; i< query.length() ; i++){
					int space = i+1;
					while(query[space] != ' '){
						space ++;
						if(space == query.length())
							break;
					}

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						orWords[numOrs] = tempWord;
						numOrs++;
					}
				}
		}
	}//go to else if there is only OR in the query
	else if(containsOr == true && containsAnd == false && containsNot == false){
			for(int i = orIndex + 3; i< query.length(); i++){
				int space = i+1;
				while(query[space] != ' '){
					space ++;
					if(space == query.length())
						break;
				}

				int wordLength = space -i + 1;
				char * tempWord = new char [wordLength];
				int iter=0;
				while(i < space){
					tempWord[iter] = query[i] ;
					i++;
					iter++;
				}
				tempWord[wordLength - 1] = 0;
				if(isStopWord(tempWord) == false){
					orWords[numOrs] = tempWord;
					numOrs++;
				}
			}
	}

	//end if there is no OR in the query
	if(numOrs > 0){
		string * tempORS = new string [numOrs];
		for(int w = 0; w < numOrs; w++){
			tempORS[w] = orWords[w];
		}
		delete [] orWords;
		orWords = tempORS;
	}

}
//parses the query to get the words after the NOT
void QueryProcessor::setNots() {
	if(numNots != 0){
		delete []notWords;
	}
	int numNotsTemp = 0;
	numNots = 0;
	for(int i = notIndex + 4; i< query.length() &&  i!= orIndex && i!= andIndex; i++){

		while(query[i] != ' '){
			if(i + 1 != query.length())
				i++;
			else break;
		}
		numNotsTemp ++;
	}
	notWords = new string [numNotsTemp];
	//if all three exist in query
	if(containsAnd == true && containsOr == true && containsNot == true){
		//if NOT comes first
		if(notIndex < orIndex && notIndex < andIndex){
				for(int i = notIndex + 4; i< orIndex  &&  i< andIndex; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						notWords[numNots] = tempWord;
						numNots++;
					}
				}
		}//go to else if order is OR, NOT, AND
		else if(notIndex > orIndex && notIndex < andIndex){
				for(int i = notIndex + 4; i< andIndex ; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						notWords[numNots] = tempWord;
						numNots++;
					}
				}
		}//go to else if order is AND, NOT, OR
		else if(notIndex < orIndex && notIndex > andIndex){
				for(int i = notIndex + 4; i< orIndex ; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						notWords[numNots] = tempWord;
						numNots++;
					}
				}
		}//go to else when NOT comes last
		else{
			for(int i = notIndex + 4; i< query.length() ; i++){
				int space = i+1;
				while(query[space] != ' '){
					space ++;
					if(space == query.length())
						break;
				}
				int wordLength = space -i + 1;
				char * tempWord = new char [wordLength];
				int iter=0;
				while(i < space){
					tempWord[iter] = query[i] ;
					i++;
					iter++;
				}
				tempWord[wordLength - 1] = 0;
				if(isStopWord(tempWord) == false){
					notWords[numNots] = tempWord;
					numNots++;
				}
			}
		}
	}//go to else if query has NOT and OR but no AND
	else if(containsNot == true && containsOr == true && containsAnd == false){
		//if NOT is before OR
		if( notIndex < orIndex ){
				for(int i = notIndex + 4; i< orIndex; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						notWords[numNots] = tempWord;
						numNots++;
					}
				}
		}//go to else if NOT is after OR
		else{
				for(int i = notIndex + 4; i< query.length() ; i++){
					int space = i+1;
					while(query[space] != ' '){
						space ++;
						if(space == query.length())
							break;
					}
					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						notWords[numNots] = tempWord;
						numNots++;
					}
				}
		}
	}//go to else if query has NOT and AND but no OR
	else if(containsNot == true && containsOr == false && containsAnd == true){
		//if NOT is before AND
		if( notIndex < andIndex ){
				for(int i = notIndex + 4; i< andIndex; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						notWords[numNots] = tempWord;
						numNots++;
					}
				}
		}//go to else if NOT is after AND
		else{
				for(int i = notIndex + 4; i< query.length() ; i++){
					int space = i+1;
					while(query[space] != ' '){
						space ++;
						if(space == query.length())
							break;
					}

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						notWords[numNots] = tempWord;
						numNots++;
					}
				}
		}
	}//go to else if there is only NOT in the query
	else if(containsNot == true && containsOr == false && containsAnd == false){
			for(int i = notIndex + 4; i< query.length(); i++){
				int space = i+1;
				while(query[space] != ' '){
					space ++;
					if(space == query.length())
						break;
				}
				int wordLength = space -i + 1;
				char * tempWord = new char [wordLength];
				int iter=0;
				while(i < space){
					tempWord[iter] = query[i] ;
					i++;
					iter++;
				}
				tempWord[wordLength - 1] = 0;
				if(isStopWord(tempWord) == false){
					notWords[numNots] = tempWord;
					numNots++;
				}
			}
	}
	if(numNots > 0){
		string * tempNOTS = new string [numNots];
		for(int w = 0; w < numNots; w++){
			tempNOTS[w] = notWords[w];
		}
		delete [] notWords;
		notWords = tempNOTS;
	}

	//end if there is no NOT in the query
}

//determines if the query has an AND, a NOt, an OR, or some combination of the three
void QueryProcessor::setQueryType(){
	containsAnd = false;
	containsOr = false;
	containsNot = false;
	for(int i = 0; i < query.length(); i++){
		if(query[i] == 'A' && (i + 2) < query.length()){
			if( query[i + 1] == 'N'){
				if(query[i + 2] == 'D'){
					containsAnd = true;
				}
			}
		}
		else if( query[i] == 'O' && (i + 1) < query.length() ){
			if(query[i + 1] == 'R'){
				containsOr = true;
			}
		}
		else if(query[i] == 'N' && (i + 2) < query.length()){
			if( query[i + 1] == 'O'){
				if(query[i + 2] == 'T'){
					containsNot = true;
				}
			}
		}
	}
}

//call this after setting query type
//determines the index of the query where the 'A' in AND is, the 'O' in OR is and the 'N' in NOT is
//if they don't exist then the index is set to -1
void QueryProcessor::setIndicesOfBools(){
	andIndex = -1;
	orIndex = -1;
	notIndex = -1;

	for(int i = 0; i < query.length(); i++){
		if(query[i] == 'A' && (i + 2) < query.length()){
			if( query[i + 1] == 'N'){
				if(query[i + 2] == 'D'){
					andIndex = i;
				}
			}
		}
		else if( query[i] == 'O' && (i + 1) < query.length() ){
			if(query[i + 1] == 'R'){
				orIndex = i;
			}
		}
		else if(query[i] == 'N' && (i + 2) < query.length()){
			if( query[i + 1] == 'O'){
				if(query[i + 2] == 'T'){
					notIndex = i;
				}
			}
		}
	}

}
//determines what words are after AND in the query
void QueryProcessor::setAnds() {
	if(numAnds != 0){
		delete []andWords;
	}
	int numAndsTemp = 0;
	numAnds = 0;
	for(int i = andIndex + 4; i< query.length() &&  i!= orIndex && i!= notIndex; i++){

		while(query[i] != ' '){
			if(i + 1 != query.length())
				i++;
			else break;
		}
		numAndsTemp ++;
	}
	andWords = new string [numAndsTemp];
	//if all three exist in query
	if(containsAnd == true && containsOr == true && containsNot == true){
		//if AND comes first
		if(andIndex < orIndex && andIndex < notIndex){
				for(int i = andIndex + 4; i< orIndex  &&  i< notIndex; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						andWords[numAnds] = tempWord;
						numAnds++;
					}
				}
		}//go to else if order is OR, AND, NOT
		else if(andIndex > orIndex && andIndex < notIndex){
				for(int i = andIndex + 4; i< notIndex ; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						andWords[numAnds] = tempWord;
						numAnds++;
					}
				}
		}//go to else if order is NOT, AND, OR
		else if(andIndex < orIndex && andIndex > notIndex){
				for(int i = andIndex + 4; i< orIndex ; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						andWords[numAnds] = tempWord;
						numAnds++;
					}
				}
		}//go to else when AND comes last
		else{
			for(int i = andIndex + 4; i< query.length() ; i++){
				int space = i+1;
				while(query[space] != ' '){
					space ++;
					if(space == query.length())
						break;
				}
				int wordLength = space -i + 1;
				char * tempWord = new char [wordLength];
				int iter=0;
				while(i < space){
					tempWord[iter] = query[i] ;
					i++;
					iter++;
				}
				tempWord[wordLength - 1] = 0;
				if(isStopWord(tempWord) == false){
					andWords[numAnds] = tempWord;
					numAnds++;
				}
			}
		}
	}//go to else if query has AND and OR but no NOT
	else if(containsAnd == true && containsOr == true && containsNot == false){
		//if AND is before OR
		if( andIndex < orIndex ){
				for(int i = andIndex + 4; i< orIndex; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						andWords[numAnds] = tempWord;
						numAnds++;
					}
				}
		}//go to else if AND is after OR
		else{
				for(int i = andIndex + 4; i< query.length() ; i++){
					int space = i+1;
					while(query[space] != ' '){
						space ++;
						if(space == query.length())
							break;
					}
					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						andWords[numAnds] = tempWord;
						numAnds++;
					}
				}
		}
	}//go to else if query has AND and NOT but no OR
	else if(containsAnd == true && containsOr == false && containsNot == true){
		//if AND is before NOT
		if( andIndex < notIndex ){
				for(int i = andIndex + 4; i< notIndex; i++){
					int space = i+1;
					while(query[space] != ' ')
						space ++;

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						andWords[numAnds] = tempWord;
						numAnds++;
					}
				}
		}//go to else if AND is after NOT
		else{
				for(int i = andIndex + 4; i< query.length() ; i++){
					int space = i+1;
					while(query[space] != ' '){
						space ++;
						if(space == query.length())
							break;
					}

					int wordLength = space -i + 1;
					char * tempWord = new char [wordLength];
					int iter=0;
					while(i < space){
						tempWord[iter] = query[i] ;
						i++;
						iter++;
					}
					tempWord[wordLength - 1] = 0;
					if(isStopWord(tempWord) == false){
						andWords[numAnds] = tempWord;
						numAnds++;
					}
				}
		}
	}//go to else if there is only AND in the query
	else if(containsAnd == true && containsOr == false && containsNot == false){
			for(int i = andIndex + 4; i< query.length(); i++){
				int space = i+1;
				while(query[space] != ' '){
					space ++;
					if(space == query.length())
						break;
				}
				int wordLength = space -i + 1;
				char * tempWord = new char [wordLength];
				int iter=0;
				while(i < space){
					tempWord[iter] = query[i] ;
					i++;
					iter++;
				}
				tempWord[wordLength - 1] = 0;
				if(isStopWord(tempWord) == false){
					andWords[numAnds] = tempWord;
					numAnds++;
				}
			}
	}
	//if there is no AND in the query or an OR, must be a single word query
	if(andIndex == -1 && orIndex == -1){
		int index = 0;
		while(query[index] != ' '){
			if(index + 1 == query.length()){
				index++;
				break;
			}else
				index++;
		}
		char * tempWord = new char [index + 1];
		for(int w =0; w<index+1;w++){
			tempWord[w] = query[w];
		}
		tempWord[index] = 0;
		andWords[0] = tempWord;
		numAnds++;
	}
	if(numAnds > 0){
		string * tempANDS = new string [numAnds];
		for(int w = 0; w < numAnds; w++){
			tempANDS[w] = andWords[w];
		}
		delete [] andWords;
		andWords = tempANDS;
	}

}
// gets a string array with the OR words
string* QueryProcessor::getOrs() {
	return orWords;
}
// gets a string array with the NOT words
string* QueryProcessor::getNots() {
	return notWords;
}
//gets a string array with the AND words
string* QueryProcessor::getAnds() {
	return andWords;
}
//prints the AND words in the query
void QueryProcessor::printAnds(){
	if(numAnds == 0)
		cout << "There are no AND words in the query." << endl;
	else{
		cout<< "The AND words in the query are: " << endl;
		for(int i = 0; i < numAnds; i++){
			cout << "# " <<  i+1 << ": " << andWords[i] << endl;
		}
	}
}
//prints the OR words in the query
void QueryProcessor::printOrs(){
	if(numOrs == 0)
		cout << "There are no OR words in the query." << endl;
	else{
		cout<< "The OR words in the query are: " << endl;
		for(int i = 0; i < numOrs; i++){
			cout << "# " <<  i+1 << ": " << orWords[i] << endl;
		}
	}
}
//gets the number of ors
int QueryProcessor::getNumOrs() {
	return numOrs;
}
//gets the number of nots
int QueryProcessor::getNumNots() {
	return numNots;
}
//gets the number of ands
int QueryProcessor::getNumAnds() {
	return numAnds;
}
//prints the words after NOT
void QueryProcessor::printNots(){
	if(numNots == 0)
		cout << "There are no NOT words in the query." << endl;
	else{
		cout<< "The NOT words in the query are: " << endl;
		for(int i = 0; i < numNots; i++){
			cout << "# " <<  i+1 << ": " << notWords[i] << endl;
		}
	}
}
//prints the query broken up into AND OR and NOT words
void QueryProcessor::printQuery(){
	printAnds();
	cout << endl;
	printOrs();
	cout << endl;
	printNots();
	cout << endl;
}
//stems the query so that it can be compared to the index words
void QueryProcessor::stemStringArray(string * s, int numInArray) {
	for(int i = 0;i < numInArray; i++){
		char * tempString = new char [s[i].length()+1];
		for(int j = 0;j < s[i].length();j++){
			tempString[j] = s[i][j];
		}
		tempString[s[i].length()] = 0;
		int newEndIndex = stem(tempString,0,s[i].length()-1);
		tempString[newEndIndex + 1] = 0;

		s[i]= tempString;
		s[i].erase(remove_if (s[i].begin(), s[i].end(), static_cast<int(*)(int)>(&ispunct)), s[i].end());

	}
}
//reads in stop words from the file
void QueryProcessor::setStopWordsFromFile(){
	ifstream ifs;
	string input;
	ifs.open("StopWords.txt");
	while(ifs.good())
	{
		getline(ifs, input);
		input.erase(remove_if (input.begin(), input.end(), static_cast<int(*)(int)>(&ispunct)), input.end());
		stopWords.push_back(input);
	}
	ifs.close();
}
//checks if the query is a stop word
bool QueryProcessor::isStopWord(string input){
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	input.erase(remove_if (input.begin(), input.end(), static_cast<int(*)(int)>(&isdigit)), input.end());
	input.erase(remove_if (input.begin(), input.end(), static_cast<int(*)(int)>(&ispunct)), input.end());
	for(unsigned int j=0; j<stopWords.size()-1; j++){
		if(input == stopWords[j]){
			input = "";
			return true;
		}
	}
	return false;
}
//default destructor
QueryProcessor::~QueryProcessor() {
	delete andWords;
	delete orWords;
	delete notWords;
}

