#include "FibHeap.h"
//#include "Node.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
//Constructor to initialize fibheap
FibHeap::FibHeap() {
	this->max = nullptr;
	this->totalNodes = 0;
}
//insert function to insert node into root list
void FibHeap::insert(Node* node) {
	if (this->max == nullptr) {
		this->max = node;
		node->rightSibling = node;
		node->leftSibling = node;
	}
	else {
		node->rightSibling = this->max->rightSibling;
		node->leftSibling = this->max;
		this->max->rightSibling = node;
		node->rightSibling->leftSibling = node;
		if (node->data > this->max->data) {
			this->max = node;
		}
	}
	this->totalNodes++;

}
//Increase the count of the existing hashtag by "value"
void FibHeap::increaseCount(Node* node, int value) {
	node->data = node->data + value;
	Node* parent = node->parent;
	if (parent != nullptr && node->data > node->parent->data) {
		cut(this, node, node->parent);
		cascadeCut(this, parent);

	}
	else {
		if (node->data > this->max->data) {
			this->max = node;
		}
	}
}
//cut the node from the child list and insert into root list
void FibHeap::cut(FibHeap* fHeap, Node* node, Node* parent) {
	//if node is the only child, make the child pointer of parent as null
	//else make the child pointer of parent to point to right sibling of current node
	if (node->rightSibling == node) {
		parent->child = nullptr;
	}
	else {
		parent->child = node->rightSibling;
		node->rightSibling->leftSibling = node->leftSibling;
		node->leftSibling->rightSibling = node->rightSibling;
	}
	//insert the node to root list
	node->parent = nullptr;
	node->childCut = false;
	node->rightSibling = fHeap->max->rightSibling;
	node->leftSibling = fHeap->max;
	fHeap->max->rightSibling = node;
	node->rightSibling->leftSibling = node;
	fHeap->totalNodes++;
}
//cascade cut recurses its way up in the tree until it finds a node 
//with “childCut” value as false or till it reaches the root.
void FibHeap::cascadeCut(FibHeap* fHeap, Node* parent) {
	
	Node* gParent = parent->parent;
	//check if parent of current parent node is root or if it has childCut value false
	if (gParent != nullptr) {
		if (parent->childCut == false) {
			parent->childCut = true;
		}
		else {
			cut(fHeap, parent, gParent);
			//recursively call cascade cut until it finds a node 
			//with “childCut” value as false or till it reaches the root.
			cascadeCut(fHeap, gParent);
		}
	}
}
//removes max node and returns the max node.
//internally calls pairwise combine to merge equal degree trees
Node* FibHeap::removeMax() {
	

		Node* temp = this->max;
		Node* nextMax = temp->rightSibling;
		if (temp != nullptr) {
			
			while (temp->child != nullptr) {
				
				Node* tempChild = temp->child;
				//check if max node has only 1 child
				if (tempChild->rightSibling == tempChild) {
					//insert child into root list
					tempChild->parent = nullptr;
					tempChild->rightSibling = this->max->rightSibling;
					tempChild->leftSibling = this->max;
					this->max->rightSibling = tempChild;
					this->totalNodes++;
					tempChild->rightSibling->leftSibling = tempChild;
					temp->child = nullptr;
				}
				else {
					//change the child pointer of parent to right sibling of current child 
					temp->child = tempChild->rightSibling;
					temp->child->leftSibling = tempChild->leftSibling;
					temp->child->leftSibling->rightSibling = temp->child;
					//insert child into root list
					tempChild->parent = nullptr;
					tempChild->rightSibling = this->max->rightSibling;
					tempChild->leftSibling = this->max;
					this->max->rightSibling = tempChild;
					this->totalNodes++;
					tempChild->rightSibling->leftSibling = tempChild;
				}
			}
			this->totalNodes--;
			//reset new max
			if (this->max->rightSibling == this->max) {
				this->max = nullptr;
			}
			else {
				this->max->rightSibling->leftSibling = this->max->leftSibling;
				this->max->leftSibling->rightSibling = this->max->rightSibling;
				this->max = this->max->rightSibling;
				pairWiseCombine(this);
			}
				
		}
		return temp;
	
	
}
//Combines equal degree trees
void FibHeap::pairWiseCombine(FibHeap* fHeap) {
	int rootNodes=0;
	//degree table to keep track of the degrees of the trees
	vector<Node*> degree(100, nullptr);
	int n = fHeap->totalNodes;
	Node* temp0 = fHeap->max;
	//traverse root list to find equal degree trees and combine them
	for (int i = 0; i < n; i++) {
		Node* next = temp0->rightSibling;
		int deg = temp0->Degree;
		while (degree[deg] != nullptr) {
			Node* temp1 = degree[deg];
			//maintain such that temp0->data is always greater than temp1->data, swap if necessary
			if (temp1->data > temp0->data) {
				Node* t = temp1;
				temp1 = temp0;
				temp0 = t;
			}
			//call combine to combine trees temp0 and temp1
			this->combine(temp1, temp0);
			this->totalNodes--;
			degree[deg] = nullptr;
			deg++;
		}
		degree[deg] = temp0;
		
		temp0 = next;
	}
	//reset max to null ptr
	fHeap->max = nullptr;
	//restructure fib heap with updated max node
	for (int i = 0; i < degree.size(); i++) {
		
		if (degree[i] != nullptr) {
			if (fHeap->max == nullptr) {
				
				fHeap->max = degree[i];
				fHeap->max->rightSibling = fHeap->max;
				fHeap->max->leftSibling = fHeap->max;
			}
			else {
				degree[i]->rightSibling = this->max->rightSibling;
				degree[i]->leftSibling = this->max;
				this->max->rightSibling = degree[i];
				degree[i]->rightSibling->leftSibling = degree[i];
				if (degree[i]->data >= fHeap->max->data) {
					fHeap->max = degree[i];
				}
			}
		}
	}

}
//combine two trees t0 and t1
void FibHeap::combine(Node* t1, Node* t0) {
	//remove t1 from root list
	t1->rightSibling->leftSibling = t1->leftSibling;
	t1->leftSibling->rightSibling = t1->rightSibling;
	//if t0 has other child trees, add t1 to child list
	if (t0->child != nullptr) {
		t1->leftSibling = t0->child;
		t1->rightSibling = t0->child->rightSibling;
		t1->leftSibling->rightSibling = t1;
		t1->rightSibling->leftSibling = t1;
		t1->parent = t0;
		t0->Degree++;
		t1->childCut = false;
	}
	//else make t1 the child of t0
	else {
		t0->child = t1;
		t1->parent = t0;
		t1->rightSibling = t1;
		t1->leftSibling = t1;
		t1->childCut = false;
		t0->Degree++;
	}
}
