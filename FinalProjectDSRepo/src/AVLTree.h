/*	Tyler Jackson
 *  Nov 12, 2013
 *
 * 			AVLTree.h
 *
 * Description:  This is the function declarations/private data for my AVLTree object.
 * 				It also contains the structure for my word node object.  Notice the
 * 				nodes is not accessed by the user
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>
#include <map>
#include <string>
#include "Word.h"
using namespace std;

//word node object-- added a parent node to ease with traversal
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
	//default constructor
	AVLTree();
	//desctructor
	virtual ~AVLTree();
	//insert a word into the tree
	void insertWord(Word& word);
	//get a word from the tree
	Word getWord(string wordName);
	//check if a word already exists in the tree
	bool wordExists(string wordName);
	//print the tree--shows balance factors and heights of each node
	void print();

private:
	//print the tree recursively --called in print()
	void print(wordNode * node);
	//inserts a node--called in insertWord()
	void insertNode(wordNode * temp);
	//update the balances after balancing
	void updateBalances(wordNode * temp);
	//set the balances after adding a node
	bool setBalances(wordNode * temp);
	//balance the tree if its unbalanced
	void balance(wordNode * temp,wordNode * temp1);
	//empty the tree
	void emptyTree(wordNode * node);
	//inserting into right sub tree of right child
	void RRRotation(wordNode * rootUnbalanced,wordNode * leaf);
	//inserting into left subtree of left child
	void LLRotation(wordNode * rootUnbalanced,wordNode * leaf);
	//inserting into left subtree of right child
	void LRRotation(wordNode * rootUnbalanced,wordNode * leaf);
	//inserting into right subtree of left child
	void RLRotation(wordNode * rootUnbalanced,wordNode * leaf);
	//single rotation right
	void singleRotRight(wordNode * node);
	//single rotation left
	void singleRotLeft(wordNode * node);
	//check if the current node is unbalanced
	bool isUnbalancedNode(wordNode* temp);
	//check if a node exists--called in wordExists
	bool nodeExists(wordNode * node,string wordName);
	//get a node based on string recursively --called in get word
	wordNode* getNode(wordNode * node,string wordName);

	//root of tree
	wordNode * root;

};

#endif /* AVLTREE_H_ */
