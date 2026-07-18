#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode* cur, int& count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode* cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)) {

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode* cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode* cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode* cur, BTNode* newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)) {
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode* pre, BTNode* cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)) {
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode* pre, BTNode* cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode* cur) {
	BTNode* is, * isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

bool BST::printLevelNodes() {
	if (root == NULL)
		return false;

	Queue q;
	q.enqueue(root);

	int level = 1;

	while (!q.empty()) {
		int size = q.size();

		cout << "Level " << level << " nodes: ";

		for (int i = 0; i < size; i++) {
			BTNode* temp;
			q.dequeue(temp);

			cout << temp->item.id << " ";

			if (temp->left != NULL)
				q.enqueue(temp->left);

			if (temp->right != NULL)
				q.enqueue(temp->right);
		}

		cout << endl;
		level++;
	}

	return true;
}

void BST::printPathHelper(BTNode* node, int path[], int pathLen) {
	if (node == NULL)
		return;

	path[pathLen] = node->item.id;
	pathLen++;

	if (node->left == NULL && node->right == NULL) {
		for (int i = 0; i < pathLen; i++) {
			cout << path[i] << " ";
		}
		cout << endl;
		return;
	}

	printPathHelper(node->left, path, pathLen);
	printPathHelper(node->right, path, pathLen);
}


bool BST::printPath() {
	if (root == NULL)
		return false;

	int path[100];
	int pathLen = 0;

	cout << "Below are all the external paths for the tree: \n\n";

	printPathHelper(root, path, pathLen);

	return true;
}


void recursiveDisplay(BTNode* cur, int order, ostream& out) {
	if (cur == NULL) return;

	if (order == 1) { // Ascending: Left -> Root -> Right
		recursiveDisplay(cur->left, order, out);
		cur->item.print(out);
		recursiveDisplay(cur->right, order, out);
	}
	else { // Descending: Right -> Root -> Left
		recursiveDisplay(cur->right, order, out);
		cur->item.print(out);
		recursiveDisplay(cur->left, order, out);
	}
}

bool BST::display(int order, int source) {
	if (empty()) return false; //the tree is empty

	if (source == 1)
		recursiveDisplay(root, order, cout);

	else if (source == 2) {
		ofstream outFile;
		outFile.open("student-info.txt");
		if (!outFile) return false;

		recursiveDisplay(root, order, outFile);

		outFile.close();
		cout << "\nStudent info is displayed in student-info.txt successfully!" << endl;
	}

	return true;
}

bool BST::deepestNodes() {
	if (empty()) return false; //the tree is empty

	Queue q;
	q.enqueue(root);

	int deepestIDs[100]; //define an array to store deepest node(s)
	int count = 0; //count: number of nodes

	while (!q.empty()) {
		int size = q.size(); //size of queue
		count = 0; //reset the array index

		//process all the nodes
		for (int i = 0; i < size; i++) {
			BTNode* cur;
			q.dequeue(cur);

			//store student IDs in the current node
			deepestIDs[count++] = cur->item.id;

			//insert children to be processed in the next level
			if (cur->left != NULL) q.enqueue(cur->left);
			if (cur->right != NULL) q.enqueue(cur->right);
		}
	}

	cout << "Deepest node(s): ";
	for (int i = 0; i < count; i++) {
		cout << deepestIDs[i] << " ";
	}
	cout << endl;

	return true;
}

// 1.Find a node containing the given item (Student) in the BST
BTNode* BST::findNode(BTNode* cur, type item) {
	if (cur == nullptr) return nullptr;

	// Check if IDs are equal
	if (cur->item.compare2(item))
		return cur;

	// Compare IDs to decide left or right
	// compare1 returns true if cur->item.id > item.id
	if (cur->item.compare1(item))
		return findNode(cur->left, item);
	else
		return findNode(cur->right, item);
}

// 2. Recursively deep copy the subtree rooted at src
BTNode* BST::cloneSubtreeRecursive(BTNode* src) {
	if (src == nullptr) return nullptr;

	// Create a new node and copy student data
	BTNode* newNode = new BTNode(src->item);

	// Recursively copy left and right subtrees
	newNode->left = cloneSubtreeRecursive(src->left);
	newNode->right = cloneSubtreeRecursive(src->right);

	return newNode;
}

//3.  Recursively count the number of nodes in the subtree rooted at cur
int BST::countNodesRecursive(BTNode* cur) {
	if (cur == nullptr) return 0;
	return 1 + countNodesRecursive(cur->left) + countNodesRecursive(cur->right);
}

// 4. Main function to clone a subtree
bool BST::CloneSubtree(BST t1, type item) {
	// Condition 1: current tree (this) must be empty
	if (!this->empty()) return false;

	// Condition 2: source tree t1 must not be empty
	if (t1.empty()) return false;

	// Find the target node in t1
	BTNode* srcNode = findNode(t1.root, item);
	if (srcNode == nullptr) return false;

	// Deep copy the subtree rooted at srcNode
	this->root = cloneSubtreeRecursive(srcNode);

	// Update the node count
	this->count = countNodesRecursive(this->root);

	return true;
}


