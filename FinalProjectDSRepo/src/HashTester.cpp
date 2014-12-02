/*HashTester.cpp
 *
 * by Tyler Jackson
 * 11/12/13
 *
 * This is just a main routine to test the AVLTree object
 *-To see a more in depth description refer to the console upon running, or scroll down
 */
#include "HashTab.h"
#include <iostream>

using namespace std;


int main(){
	Word a;
	Word b;
	Word c;
	Word d;
	Word e;
	Word f;
	Word g;
	Word h;
	Word i;
	Word j;

	a.setWord("a");
	b.setWord("b");
	c.setWord("c");
	d.setWord("d");
	e.setWord("e");
	f.setWord("f");
	g.setWord("g");
	h.setWord("h");
	i.setWord("i");
	j.setWord("j");
	HashTab tab1;
	tab1.insert(a);
	tab1.insert(b);
	tab1.insert(d);
	tab1.insert(e);
	tab1.insert(g);
	tab1.insert(c);
	tab1.insert(h);
	tab1.insert(i);
	tab1.insert(f);
	tab1.insert(j);

	cout<<endl;
	cout<<endl;
	tab1.print();



	cout << "Test some of the Word Functions from Hash Table" << endl;

	Word apple("apple");
	Word banana("banana");
	Word cherry("cherry");
	Word orange("orange");
	Word pear("pear");
	Word peach("peach");
	HashTab * wordTester = new HashTab();
	wordTester->insert(peach);
	wordTester->insert(banana);
	wordTester->insert(cherry);
	wordTester->insert(apple);
	wordTester->insert(orange);
	wordTester->insert(pear);

	if(wordTester->wordExists("orange")){
		cout << "it works" << endl;
		Word temp;
		temp = wordTester->getWord("orange");
		cout << "It should say orange" << endl;
		cout << "The word is: " << temp.getWord() << endl;
	}
	if(wordTester->wordExists("banana")){
		Word temp;
		temp = wordTester->getWord("banana");
		cout << "It should say banana" << endl;
		cout << "The word is: " << temp.getWord() << endl;
		cout << "it works" << endl;
	}
	if(wordTester->wordExists("suck"))
		cout << "it doesn't work" << endl;
	if(wordTester->wordExists("pear"))
		cout << "It should say pear" << endl;
		cout << "The word is: " << wordTester->getWord("pear").getWord() << endl;
	return 0;

}
