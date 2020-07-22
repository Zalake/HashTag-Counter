#include "Node.h"
//constructor for Node class
Node::Node(int data,std::string hashTag) {
	this->data = data;
	this->child = nullptr;
	this->parent = nullptr;
	this->Degree = 0;
	this->childCut = false;
	this->rightSibling = nullptr;
	this->leftSibling = nullptr;
	this->hashTag = hashTag;
}
int Node::getData() {
	return this->data;
}
//default constructor
Node::Node() {

}