#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

Node::Node() {

	int data;
	prev = NULL;
	next = NULL;
	
}

Node::~Node() {
	prev = NULL;
	next = NULL;
}

Node* Node::getNext() {
	return next;
}

Node* Node::getPrev() {
	return prev;
}

int Node::getData() {
	return data;
}

void Node::setNext(Node* newNext) {
	next = newNext;
}
void Node::setPrev(Node* newPrev) {
	prev = newPrev;
}
void Node::setData(int newData) {
	data = newData;
}
