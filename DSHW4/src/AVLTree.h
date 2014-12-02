/*
 * AVLTree.h
 *
 * Created on: Nov 12, 2013
 * Author: tgjackson
 *
 * Description:  This is the function declarations/private data for my AVLTree object.
 * 				It also contains the structure for my word node object
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>
#include <map>
#include <string>
#include "Word.h"
using namespace std;

struct wordNode{
	int height;
	int balanceFactor;
	wordNode * left;
	wordNode * right;
	wordNode * parent;
	Word word;
	wordNode (){
		height=0;
		parent=NULL;
		right=NULL;
		left=NULL;
		balanceFactor = 0;
	}

};

class AVLTree {
public:
	AVLTree();
	virtual ~AVLTree();
	void insertWord(Word * word);
	void insertWord(Word& word);
	Word getWord(string wordName);
	bool wordExists(string wordName);

	void print();
	wordNode * root;
private:
	void print(wordNode * node);
	void insertNode(wordNode * temp);
	void updateBalances(wordNode * temp);
	bool setBalances(wordNode * temp);
	void balance(wordNode * temp,wordNode * temp1);
	void emptyTree(wordNode * node);
	void RRRotation(wordNode * rootUnbalanced,wordNode * leaf);
	void LLRotation(wordNode * rootUnbalanced,wordNode * leaf);
	void LRRotation(wordNode * rootUnbalanced,wordNode * leaf);
	void RLRotation(wordNode * rootUnbalanced,wordNode * leaf);
	void singleRotRight(wordNode * node);
	void doubleRotRight(wordNode * node);
	void singleRotLeft(wordNode * node);
	void doubleRotLeft(wordNode * node);
	bool isUnbalancedNode(wordNode* temp);
	bool nodeExists(wordNode * node,string wordName);
	wordNode* getNode(wordNode * node,string wordName);




};

#endif /* AVLTREE_H_ */
