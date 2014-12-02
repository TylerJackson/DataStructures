/*AVLTester.cpp
 *
 * by Tyler Jackson
 * 11/12/13
 *
 * This is just a main routine to test the AVLTree object
 *-To see a more in depth description refer to the console upon running, or scroll down
 */
#include "AVLTree.h"
#include <iostream>

using namespace std;


int main(){


	//There's twelve different cases for testing the insertion rotations
	//3 for inserting into left sub tree of the left child of alpha
	//3 for inserting into right sub tree of the right child of alpha
	//3 for inserting into right sub tree of the left child of alpha
	//3 for inserting into left sub tree of the right child of alpha
	cout<<"---                 AVL TREE TESTER              ---"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"    This tester class tests my AVL Class.  It tests the ability to insert words"<<endl;
	cout<<"to a tree.  In order to maintain its AVL balance it rotates the tree if necessary"<<endl;
	cout<<"upon insertion.  It then prints out the order of the nodes using an inorder"<<endl;
	cout<<"traversal method.  It also states each nodes height, and its balance.  Therefore"<<endl;
	cout<<"you can not only verify that all the balances are in between -1 and 1, but also"<<endl;
	cout<<"visualize the tree a little using the heights."<<endl;
	cout<<endl;
	cout<<endl;

//start of test
	Word worda;
	Word wordb;
	Word wordc;
	Word wordd;
	Word worde;
	Word wordf;
	Word wordg;
	Word wordh;
	Word wordi;
	Word wordj;
	worda.setWord("A");
	wordb.setWord("B");
	wordc.setWord("C");
	wordd.setWord("D");
	worde.setWord("E");
	wordf.setWord("F");
	wordg.setWord("G");
	wordh.setWord("H");
	wordi.setWord("I");
	wordj.setWord("J");

	//LL Insertion
	//create tree and insert words for test one A,B,C
	AVLTree * tree=new AVLTree();
	tree->insertWord(worda);
	tree->insertWord(wordb);
	tree->insertWord(wordc);

	cout<<"--------TEST 1---------"<<endl;
	cout<<endl;
	tree->print();
	cout<<endl;
	cout<<endl;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//start of  next test


	Word worda1;
	Word wordb1;
	Word wordc1;
	Word wordd1;
	Word worde1;
	Word wordf1;
	Word wordg1;
	Word wordh1;
	Word wordi1;
	Word wordj1;
	worda1.setWord("A");
	wordb1.setWord("B");
	wordc1.setWord("C");
	wordd1.setWord("D");
	worde1.setWord("E");
	wordf1.setWord("F");
	wordg1.setWord("G");
	wordh1.setWord("H");
	wordi1.setWord("I");
	wordj1.setWord("J");

	//create tree and insert words for test two B,A,F,E,G,H
	AVLTree * tree1=new AVLTree();
	tree1->insertWord(wordb1);
	tree1->insertWord(worda1);
	tree1->insertWord(wordf1);
	tree1->insertWord(worde1);
	tree1->insertWord(wordg1);
	tree1->insertWord(wordh1);

	cout<<"--------TEST 2---------"<<endl;
	cout<<endl;
	tree1->print();
	cout<<endl;
	cout<<endl;

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
	//start of  next test

	Word worda2;
	Word wordb2;
	Word wordc2;
	Word wordd2;
	Word worde2;
	Word wordf2;
	Word wordg2;
	Word wordh2;
	Word wordi2;
	Word wordj2;
	worda2.setWord("A");
	wordb2.setWord("B");
	wordc2.setWord("C");
	wordd2.setWord("D");
	worde2.setWord("E");
	wordf2.setWord("F");
	wordg2.setWord("G");
	wordh2.setWord("H");
	wordi2.setWord("I");
	wordj2.setWord("J");
	//create tree and insert words for test three B,A,F,E,H,G
	AVLTree * tree2=new AVLTree();
	tree2->insertWord(wordb2);
	tree2->insertWord(worda2);
	tree2->insertWord(wordf2);
	tree2->insertWord(worde2);
	tree2->insertWord(wordh2);
	tree2->insertWord(wordg2);

	cout<<"--------TEST 3---------"<<endl;
	cout<<endl;
	tree2->print();
	cout<<endl;
	cout<<endl;

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
	//start of  next test

	Word worda3;
	Word wordb3;
	Word wordc3;
	Word wordd3;
	Word worde3;
	Word wordf3;
	Word wordg3;
	Word wordh3;
	Word wordi3;
	Word wordj3;
	worda3.setWord("A");
	wordb3.setWord("B");
	wordc3.setWord("C");
	wordd3.setWord("D");
	worde3.setWord("E");
	wordf3.setWord("F");
	wordg3.setWord("G");
	wordh3.setWord("H");
	wordi3.setWord("I");
	wordj3.setWord("J");

	//RR Insertion
	//create tree and insert words for test four C,B,A
	AVLTree * tree3=new AVLTree();
	tree3->insertWord(wordc3);
	tree3->insertWord(wordb3);
	tree3->insertWord(worda3);

	cout<<"--------TEST 4---------"<<endl;
	cout<<endl;
	tree3->print();
	cout<<endl;
	cout<<endl;

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
	//start of  next test

	Word worda4;
	Word wordb4;
	Word wordc4;
	Word wordd4;
	Word worde4;
	Word wordf4;
	Word wordg4;
	Word wordh4;
	Word wordi4;
	Word wordj4;
	worda4.setWord("A");
	wordb4.setWord("B");
	wordc4.setWord("C");
	wordd4.setWord("D");
	worde4.setWord("E");
	wordf4.setWord("F");
	wordg4.setWord("G");
	wordh4.setWord("H");
	wordi4.setWord("I");
	wordj4.setWord("J");

	//create tree and insert words for test five G,H,E,F,B,A
	AVLTree * tree4=new AVLTree();
	tree4->insertWord(wordg4);
	tree4->insertWord(wordh4);
	tree4->insertWord(worde4);
	tree4->insertWord(wordf4);
	tree4->insertWord(wordb4);
	tree4->insertWord(worda4);

	cout<<"--------TEST 5---------"<<endl;
	cout<<endl;
	tree4->print();
	cout<<endl;
	cout<<endl;
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//start of  next test
	Word worda5;
	Word wordb5;
	Word wordc5;
	Word wordd5;
	Word worde5;
	Word wordf5;
	Word wordg5;
	Word wordh5;
	Word wordi5;
	Word wordj5;
	worda5.setWord("A");
	wordb5.setWord("B");
	wordc5.setWord("C");
	wordd5.setWord("D");
	worde5.setWord("E");
	wordf5.setWord("F");
	wordg5.setWord("G");
	wordh5.setWord("H");
	wordi5.setWord("I");
	wordj5.setWord("J");

	//create tree and insert words for test six G,H,E,F,B,C
	AVLTree * tree5=new AVLTree();
	tree5->insertWord(wordg5);
	tree5->insertWord(wordh5);
	tree5->insertWord(worde5);
	tree5->insertWord(wordf5);
	tree5->insertWord(wordb5);
	tree5->insertWord(wordc5);

	cout<<"--------TEST 6---------"<<endl;
	cout<<endl;
	tree5->print();
	cout<<endl;
	cout<<endl;
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//start of  next test
	Word worda6;
	Word wordb6;
	Word wordc6;
	Word wordd6;
	Word worde6;
	Word wordf6;
	Word wordg6;
	Word wordh6;
	Word wordi6;
	Word wordj6;
	worda6.setWord("A");
	wordb6.setWord("B");
	wordc6.setWord("C");
	wordd6.setWord("D");
	worde6.setWord("E");
	wordf6.setWord("F");
	wordg6.setWord("G");
	wordh6.setWord("H");
	wordi6.setWord("I");
	wordj6.setWord("J");

	//RL Insertion
	//create tree and insert words for test seven D,B,C
	AVLTree * tree6=new AVLTree();
	tree6->insertWord(wordd6);
	tree6->insertWord(wordb6);
	tree6->insertWord(wordc6);

	cout<<"--------TEST 7---------"<<endl;
	cout<<endl;
	tree6->print();
	cout<<endl;
	cout<<endl;

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
	//start of  next test
	Word worda7;
	Word wordb7;
	Word wordc7;
	Word wordd7;
	Word worde7;
	Word wordf7;
	Word wordg7;
	Word wordh7;
	Word wordi7;
	Word wordj7;
	worda7.setWord("A");
	wordb7.setWord("B");
	wordc7.setWord("C");
	wordd7.setWord("D");
	worde7.setWord("E");
	wordf7.setWord("F");
	wordg7.setWord("G");
	wordh7.setWord("H");
	wordi7.setWord("I");
	wordj7.setWord("J");

	//create tree and insert words for test eight H,I,D,F,B,E
	AVLTree * tree7=new AVLTree();
	tree7->insertWord(wordh7);
	tree7->insertWord(wordi7);
	tree7->insertWord(wordd7);
	tree7->insertWord(wordf7);
	tree7->insertWord(wordb7);
	tree7->insertWord(worde7);

	cout<<"--------TEST 8---------"<<endl;
	cout<<endl;
	tree7->print();
	cout<<endl;
	cout<<endl;

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
	//start of  next test
	Word worda8;
	Word wordb8;
	Word wordc8;
	Word wordd8;
	Word worde8;
	Word wordf8;
	Word wordg8;
	Word wordh8;
	Word wordi8;
	Word wordj8;
	worda8.setWord("A");
	wordb8.setWord("B");
	wordc8.setWord("C");
	wordd8.setWord("D");
	worde8.setWord("E");
	wordf8.setWord("F");
	wordg8.setWord("G");
	wordh8.setWord("H");
	wordi8.setWord("I");
	wordj8.setWord("J");

	//create tree and insert words for test nine H,I,D,B,F,G
	AVLTree * tree8=new AVLTree();
	tree8->insertWord(wordh8);
	tree8->insertWord(wordi8);
	tree8->insertWord(wordd8);
	tree8->insertWord(wordb8);
	tree8->insertWord(wordf8);
	tree8->insertWord(wordg8);

	cout<<"--------TEST 9---------"<<endl;
	cout<<endl;
	tree8->print();
	cout<<endl;
	cout<<endl;

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
	//start of  next test
	Word worda9;
	Word wordb9;
	Word wordc9;
	Word wordd9;
	Word worde9;
	Word wordf9;
	Word wordg9;
	Word wordh9;
	Word wordi9;
	Word wordj9;
	worda9.setWord("A");
	wordb9.setWord("B");
	wordc9.setWord("C");
	wordd9.setWord("D");
	worde9.setWord("E");
	wordf9.setWord("F");
	wordg9.setWord("G");
	wordh9.setWord("H");
	wordi9.setWord("I");
	wordj9.setWord("J");

	//LR Insertion
	//create tree and insert words for test ten A,C,B
	AVLTree * tree9=new AVLTree();
	tree9->insertWord(worda9);
	tree9->insertWord(wordc9);
	tree9->insertWord(wordb9);

	cout<<"--------TEST 10---------"<<endl;
	cout<<endl;
	tree9->print();
	cout<<endl;
	cout<<endl;
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
	//start of  next test
	Word worda10;
	Word wordb10;
	Word wordc10;
	Word wordd10;
	Word worde10;
	Word wordf10;
	Word wordg10;
	Word wordh10;
	Word wordi10;
	Word wordj10;
	worda10.setWord("A");
	wordb10.setWord("B");
	wordc10.setWord("C");
	wordd10.setWord("D");
	worde10.setWord("E");
	wordf10.setWord("F");
	wordg10.setWord("G");
	wordh10.setWord("H");
	wordi10.setWord("I");
	wordj10.setWord("J");


	//create tree and insert words for test eleven B,A,G,E,H,F
	AVLTree * tree10=new AVLTree();
	tree10->insertWord(wordb10);
	tree10->insertWord(worda10);
	tree10->insertWord(wordg10);
	tree10->insertWord(worde10);
	tree10->insertWord(wordh10);
	tree10->insertWord(wordf10);

	cout<<"--------TEST 11---------"<<endl;
	cout<<endl;
	tree10->print();
	cout<<endl;
	cout<<endl;

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
	//start of  next test
	Word worda11;
	Word wordb11;
	Word wordc11;
	Word wordd11;
	Word worde11;
	Word wordf11;
	Word wordg11;
	Word wordh11;
	Word wordi11;
	Word wordj11;
	worda11.setWord("A");
	wordb11.setWord("B");
	wordc11.setWord("C");
	wordd11.setWord("D");
	worde11.setWord("E");
	wordf11.setWord("F");
	wordg11.setWord("G");
	wordh11.setWord("H");
	wordi11.setWord("I");
	wordj11.setWord("J");

	//create tree and insert words for test twelve B,A,G,E,H,D
	AVLTree * tree11=new AVLTree();
	tree11->insertWord(wordb11);
	tree11->insertWord(worda11);
	tree11->insertWord(wordg11);
	tree11->insertWord(worde11);
	tree11->insertWord(wordh11);
	tree11->insertWord(wordd11);

	cout<<"--------TEST 12---------"<<endl;
	cout<<endl;
	tree11->print();
	cout<<endl;
	cout<<endl;

	cout << "Test some of the Word Functions from AVL Tree" << endl;

	Word apple("apple");
	Word banana("banana");
	Word cherry("cherry");
	Word orange("orange");
	Word pear("pear");
	Word peach("peach");
	AVLTree * wordTester = new AVLTree();
	wordTester->insertWord(peach);
	wordTester->insertWord(banana);
	wordTester->insertWord(cherry);
	wordTester->insertWord(apple);
	wordTester->insertWord(orange);
	wordTester->insertWord(pear);

	if(wordTester->wordExists("orange")){
		cout << "it works" << endl;
		Word temp;
		temp = wordTester->getWord("orange");
		cout << "The word is: " << temp.getWord() << endl;
	}
	if(wordTester->wordExists("banana")){
		Word temp;
		temp = wordTester->getWord("banana");
		cout << "The word is: " << temp.getWord() << endl;
		cout << "it works" << endl;
	}
	if(wordTester->wordExists("suck"))
		cout << "it doesn't work" << endl;
	if(wordTester->wordExists("pear"))
		cout << "The word is: " << wordTester->getWord("pear").getWord() << endl;
	return 0;

}






