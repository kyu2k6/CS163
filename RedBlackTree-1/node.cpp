#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

Node::Node() {

	color = 1;
	parent = NULL;
	data;
	prev = NULL;
	next = NULL;
	
}

Node::~Node() {
	prev = NULL;
	next = NULL;
	parent = NULL;
}

int Node::getColor() {
	return color;
}
Node* Node::getParent() {
	return parent;
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

void Node::setColor(int newColor) {
	color = newColor;
}
void Node::setParent(Node* newParent) {
	parent = newParent;
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
