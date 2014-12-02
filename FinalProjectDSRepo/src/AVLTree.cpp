/* Tyler Jackson
 * Date: Nov 12, 2013
 *
 * 		AVLTree.cpp
 *
 *		This is the implimentation for my AVL tree object.  Handles balancing and insertion
 *		and searching.
 */

#include "AVLTree.h"
#include "math.h"
using namespace std;

//basic constructor initializes root to null
AVLTree::AVLTree() {
	root=NULL;
}

//returns a word object based on the string word
Word AVLTree::getWord(string wordName){
	wordNode * temp = new wordNode();
	temp = getNode(root,wordName);
	return temp->word;
}

//checks if a word exists
bool AVLTree::wordExists(string wordName){
	bool b = nodeExists(root, wordName);
	return b;
}

//check if a node exists
bool AVLTree::nodeExists(wordNode * node,string wordName){
	if(node != NULL){
		if(node->word.getWord() == wordName)
			return true;
		return (nodeExists(node->left,wordName) || nodeExists(node->right,wordName));
	}
	return false;
}

//gets node -- only called if node exists
wordNode* AVLTree::getNode(wordNode * node,string wordName){
	if(node == NULL || node->word.getWord() == wordName)
		return node;
	else if (wordName < node->word.getWord() )
		return getNode(node->left,wordName);
	else
		return getNode(node->right,wordName);

}

//destructor clears tree by removing every node in it
AVLTree::~AVLTree() {
	emptyTree(root);
}

//insert a node taking a word as parameter
//this allows us to prevent anyone from using my nodes
void AVLTree::insertWord(Word& word){
	wordNode * temp = new wordNode ();
	temp->word = word;
	insertNode(temp);
}

//insert new node and then call balance
//to make sure it maintains AVL property
void AVLTree::insertNode(wordNode* temp) {

	//if nothing in tree set root = to new node
	if(root == NULL){
		root=temp;
		return;
	}

	wordNode * iter=new wordNode();
	iter = root;
	wordNode * placeHolder = new wordNode();
	wordNode * unbalancedNode = new wordNode();
	placeHolder = root;

	//-iterate down tree by name values till iter = null
	//-set parent to placeholder each time before iterating down
	//-this way when iter finally is null, we can add it to the correct
	//side of the leaf
	while(iter != NULL){
		if(temp->word < iter->word ){
			placeHolder = iter;
			iter = iter->left;
		}else{
			placeHolder=iter;
			iter = iter->right;
		}
	}
	//add node to correct side
	temp->parent=placeHolder;
	if(temp->word < placeHolder->word){
		placeHolder->left = temp;
	}else{
		placeHolder->right = temp;
		temp->parent = placeHolder;
	}

	//call setBalances to determine the balance of each node and return true if any
	//are <-1 or >1
	bool unbalanced = setBalances(temp);

	//iterate through if unbalanced and find unbalanced node
	if(unbalanced){
		unbalancedNode=temp->parent;
		while(!isUnbalancedNode(unbalancedNode))
			unbalancedNode = unbalancedNode->parent;
	}

	//	if nodes are unbalanced, balance nodes by rotation using balance function
	if(unbalanced){
		balance(unbalancedNode,temp);
		updateBalances(root);
	}

}

//balance tree based on which case it is LL. RR. LR. RL.
void AVLTree::balance(wordNode * rootUnbalanced,wordNode * leaf) {
	string child;
	string subtree;
	//define which subtree of which child we are inserting into
	// (for our cases)

	if( leaf->word < rootUnbalanced->word ){
		child="left";
		if( leaf->word < rootUnbalanced->left->word ){
			subtree = "leftsubtree";
		}else
			subtree = "rightsubtree";
	}else{
		child="right";
		if( leaf->word < rootUnbalanced->right->word ){
			subtree = "leftsubtree";
		}else
			subtree = "rightsubtree";
	}
	//case 1
	//	insert into Left subtree of left child
	if(child == "left" && subtree == "leftsubtree"){
		LLRotation(rootUnbalanced,leaf);

	//case 2
	//	insert into Right subtree of right child
	}else if(child == "right" && subtree == "rightsubtree"){
		RRRotation(rootUnbalanced,leaf);
	//case 3
	//	insert into Left subtree of right child
	}else if(child == "right" && subtree == "leftsubtree")
		LRRotation(rootUnbalanced,leaf);
	//case 4
	//	insert into Right subtree of left child
	else
		RLRotation(rootUnbalanced,leaf);

}

//removes every node from "node" down
//used mainly for destructor
void AVLTree::emptyTree(wordNode* node) {
	if(node->left != NULL)
		emptyTree(node->left);
	if(node->right != NULL)
		emptyTree(node->right);
	delete node;
}

//case RR - right subtree of right child
//single rotation
void AVLTree::RRRotation(wordNode* rootUnbalanced, wordNode* leaf) {
	singleRotLeft(rootUnbalanced);
}

//inserting into Left sub tree of left child of alpha
//will be a single rotation
void AVLTree::LLRotation(wordNode* rootUnbalanced, wordNode* leaf) {
	singleRotRight(rootUnbalanced);
}

//left subtree of right child
//double rotation
void AVLTree::LRRotation(wordNode* rootUnbalanced, wordNode* leaf) {
	wordNode * secondaryAlpha= new wordNode ();
	secondaryAlpha = rootUnbalanced->right;
	secondaryAlpha->parent = rootUnbalanced;
	singleRotRight(secondaryAlpha);
	singleRotLeft(rootUnbalanced);
}

//inserting into right subtree of left child
//will be a double rotation
void AVLTree::RLRotation(wordNode* rootUnbalanced, wordNode* leaf) {
	wordNode * secondaryAlpha= new wordNode ();
	secondaryAlpha = rootUnbalanced->left;
	secondaryAlpha->parent = rootUnbalanced;
	singleRotLeft(secondaryAlpha);
	singleRotRight(rootUnbalanced);
}

//single rotation right
void AVLTree::singleRotRight(wordNode* alpha) {

	wordNode * alphaParent = new wordNode();
	//if alpha is not root set its parent to alpha parent
	if(alpha->parent != NULL)
		alphaParent=alpha->parent;

	wordNode * tempRoot = new wordNode();
	//first set tempRoot to alpha
	tempRoot = alpha;

	wordNode * tempChild = new wordNode();
	//set tempChild to the left child of alpha
	tempChild = alpha->left;

	wordNode * tempChildRightBaby = new wordNode();
	//if temp child right isn't null, must move it to left child of tempRoot
	if(tempChild->right != NULL){
		tempChildRightBaby=tempChild->right;
		tempRoot->left = tempChildRightBaby;
		tempChildRightBaby->parent = tempRoot;
	}else
		//if the right child of tempChild is NULL, the left child of the orig.
		//alpha should be null
		tempRoot->left = NULL;

	//change the parent of the left child to the parent of alpha
	//moving the left child to the top
	tempChild->parent = alpha->parent;
	//move original root to the right child of new root
	tempChild->right = alpha;

	//set the child of the parent of the original alpha to new alpha if not NULL
	if(alpha->parent != NULL){
		//if new alpha is less than parent set it to left child
		if(tempChild->word < alphaParent->word)
			alphaParent->left = tempChild;
		//else set it to right child
		else
			alphaParent->right = tempChild;
	}


	//change tempRoots parent to new alpha
	tempRoot->parent = tempChild;

	if(tempChild->parent == NULL)
		root = tempChild;
}
//single rotation left
void AVLTree::singleRotLeft(wordNode* alpha) {

	wordNode * alphaParent = new wordNode();
	//if alpha is not root set its parent to alpha parent
	if(alpha->parent != NULL){
		alphaParent=alpha->parent;
	}
	wordNode * tempRoot = new wordNode();
	//first set tempRoot to alpha
	tempRoot = alpha;

	wordNode * tempChild = new wordNode();
	//set tempChild to the left child of alpha
	tempChild = alpha->right;

	wordNode * tempChildLeftBaby = new wordNode();
	//if temp child right isn't null, must move it to left child of tempRoot
	if(tempChild->left != NULL){
		tempChildLeftBaby=tempChild->left;
		tempRoot->right = tempChildLeftBaby;
		tempChildLeftBaby->parent = tempRoot;
	}else
		//if the right child of tempChild is NULL, the left child of the orig.
		//alpha should be null
		tempRoot->right = NULL;

	//change the parent of the left child to the parent of alpha
	//moving the left child to the top
	tempChild->parent = alpha->parent;
	//move original root to the right child of new root
	tempChild->left = alpha;

	//set the child of the parent of the original alpha to new alpha if not NULL
	if(alpha->parent != NULL){
		//if new alpha is less than parent set it to left child
		if(tempChild->word < alphaParent->word)
			alphaParent->left = tempChild;
		//else set it to right child
		else
			alphaParent->right = tempChild;
	}


	//change tempRoots parent to new alpha
	tempRoot->parent = tempChild;

	if(tempChild->parent == NULL){
		root = tempChild;
	}
}
//print tree
void AVLTree::print() {
	print(root);
}
//prints the AVL Tree in order
void AVLTree::print(wordNode * node) {
	if(node != NULL){
		print(node->left);
		cout << "name: " << node->word.getWord() << endl;
		cout << "             height: " << node->height << endl;
		cout << "     balance factor: " << node->balanceFactor <<endl;
		node->word.printDocsIDs();
		cout<<endl;
		print(node->right);
	}
}
//update balances after a rotation
void AVLTree::updateBalances(wordNode * node){
	if(node != NULL){
		updateBalances(node->left);
		updateBalances(node->right);
		if(node->left == NULL && node->right == NULL){
			//leaf nodes are always height one,balance factor 0
			node->height = 1;
			node->balanceFactor = 0;
		}else if(node->left == NULL && node->right != NULL){
			//set heights
			node->height = node->right->height + 1;

			//set balance factor
			node->balanceFactor = node->right->height;
		}else if(node->left != NULL && node->right == NULL){
			//set heights
			node->height = node->left->height + 1;

			//set balance factor
			node->balanceFactor = -1*node->left->height;
		}else if(node->left !=NULL && node->right != NULL){
			//set heights
			if(node->left->height > node->right->height)
				node->height = node->left->height + 1;
			else
				node->height = node->right->height + 1;

			//set balance factor
			node->balanceFactor = -1*node->left->height + node->right->height;
		}
	}
}
//set balances after a node is added
bool AVLTree::setBalances(wordNode * node){
	bool b=false;
	wordNode * iter=new wordNode ();
	iter=node;
	while(iter!=NULL){
		if(iter->left ==NULL && iter->right == NULL){
			//leaf nodes are always height one,balance factor 0
			iter->height = 1;
			iter->balanceFactor = 0;
		}else if(iter->left == NULL && iter->right != NULL){
			//set heights
			iter->height = iter->right->height + 1;

			//set balance factor
			iter->balanceFactor = iter->right->height;
		}else if(iter->left != NULL && iter->right == NULL){
			//set heights
			iter->height = iter->left->height + 1;

			//set balance factor
			iter->balanceFactor = -1*iter->left->height;
		}else if(iter->left !=NULL && iter->right != NULL){
			//set heights
			if(iter->left->height > iter->right->height)
				iter->height = iter->left->height + 1;
			else
				iter->height = iter->right->height + 1;

			//set balance factor
			iter->balanceFactor = -1*iter->left->height + iter->right->height;
		}
		if(fabs(iter->balanceFactor) > 1)
			b = true;
		iter=iter->parent;
	}
	return b;
}

//this returns the first unbalanced node coming up from the leaf
//assumes there is an unbalanced node
bool AVLTree::isUnbalancedNode(wordNode* temp){
	if(fabs(temp->balanceFactor) > 1)
		return true;
	else
		return false;
}

