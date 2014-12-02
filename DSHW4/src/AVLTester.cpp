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
void inline printByLevel(wordNode * node, int level, int count);

void inline printBoth(wordNode * a, wordNode * b);
int main(){



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

	AVLTree * tree =new AVLTree();
	tree->insertWord(worda);
	tree->insertWord(worde);
	tree->insertWord(wordg);
	tree->insertWord(wordd);

	AVLTree * tree1 =new AVLTree();
	tree1->insertWord(wordc);
	tree1->insertWord(wordb);
	tree1->insertWord(wordf);
	tree1->insertWord(wordj);


	printByLevel(tree->root,2,0);
	cout << "-------------------" << endl;
	printBoth(tree->root,tree1->root);
	return 0;
}

void printByLevel(wordNode * node, int level, int count){
	if(node != NULL){
		printByLevel(node->left,level,count+1);
		if(level == count)
			cout << node->word.getWord() << endl;
		printByLevel(node->right,level,count+1);
	}
}
void printBoth(wordNode * alpha, wordNode * beta){
	if(alpha!= NULL && beta!=NULL){
			printBoth(alpha->left,beta->left);
			if(alpha->word < beta->word){
				cout << alpha->word.getWord() << endl;
				cout << beta->word.getWord() << endl;
			}else{
				cout << beta->word.getWord() << endl;
				cout << alpha->word.getWord() << endl;
			}
			printBoth(alpha->right,beta->right);
	}else if(alpha == NULL && beta!= NULL){
		printBoth(alpha,beta->left);
	}else if(alpha != NULL && beta == NULL){
		printBoth(alpha->left,beta);
}
}

