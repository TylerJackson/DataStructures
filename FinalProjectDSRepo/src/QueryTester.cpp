/*Tyler Jackson
 * Date: 11/24/13
 *
 * QueryTester.cpp
 *
 *		This class just tests our query processor.  It allows us to put in any type
 *	of combo of ANDS and OR and NOT with each word being separated by a space.  It then
 *	prints the parsed results to the console for review and allows repeat.
 */

#include "QueryProcessor.h"
#include <iostream>

using namespace std;

int main(){
	QueryProcessor testQuery;
	bool b = true;
	cout << "This is our query tester.  To test a query enter any combination of AND, OR, and NOT." << endl;
	cout << "There is three things you need to know when testing: " << endl;
	cout << "1.)  Remember to keep these 3 key words all capitalized." << endl;
	cout << "2.)  Keep every word you want to search separated by a space"  << endl;
	cout <<	"3.)  To stop testing type 'DONE'" << endl;

	cout << endl;
	while(b){
		cout << " What is your query: " << endl;
		string tempQuery;
		getline(cin,tempQuery);
		if(tempQuery == "DONE"){
			cout << "Exiting Query Test.." << endl;
			b = false;
		}
		else{
			testQuery.setQuery(tempQuery);
			testQuery.printQuery();
		}
	}
	cout << endl;
	cout << "Now we'll test our 'getter' methods" << endl;
	cout << endl;
	string * tempAnds = testQuery.getAnds();
	string * tempOrs = testQuery.getOrs();
	string * tempNots = testQuery.getNots();
	int numAndWords = testQuery.getNumAnds();
	int numOrWords = testQuery.getNumOrs();
	int numNotWords = testQuery.getNumNots();

	if(numAndWords == 0){
		cout << "There were no AND words." << endl;
		cout << endl;
	}else{
		cout << "The AND words in our query are: " << endl;
		for(int i = 0; i < numAndWords; i++){
			cout << "# " << i+1 << ": " << tempAnds[i] << endl;
		}
		cout << endl;
	}
	if(numOrWords == 0){
		cout << "There were no OR words." << endl;
		cout << endl;
	}else{
		cout << "The OR words in our query are: " << endl;
		for(int i = 0; i < numOrWords; i++){
			cout << "# " << i+1 << ": " << tempOrs[i] << endl;
		}
		cout << endl;
	}
	if(numNotWords == 0){
		cout << "There were no NOT words." << endl;
		cout << endl;
	}else{
		cout << "The NOT words in our query are: " << endl;
		for(int i = 0; i < numNotWords; i++){
			cout << "# " << i+1 << ": " << tempNots[i] << endl;
		}
		cout << endl;
	}


	return 0;
}
