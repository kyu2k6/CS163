#include "node.h"
#include <iostream>

Node::Node() {
	
	left = NULL;
	right = NULL;
	next = NULL;
	value = NULL;

}

Node::~Node() {

}

void Node::setValue(char newvalue) {
	value = newvalue;
}

void Node::setNext(Node* newNext) {
	next = newNext;
}

Node* Node::getNext() {
	return next;
}

char Node::getValue() {
	return value;
}
void Node::setRight(Node* newRight) {
  	right = newRight;
}

void Node::setLeft(Node* newLeft) {
  	left = newLeft;
}

Node* Node::getRight() {
  	return right;
}

Node* Node::getLeft() {
  	return left;
}
