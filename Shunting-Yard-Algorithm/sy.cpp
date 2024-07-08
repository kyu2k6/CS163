//Kevin Yu
//3-19-22
//Postifx Infix, Prefix
//With assitance from Nathan Zou on the binary tree expression area

#include <iostream>
#include "node.h"
#include <cstring>

using namespace std;

int order(char input);
void enqueue(Node*& headQ, char newvalue);
void print(Node* head);
void stack(Node*& headS, char newvalue, Node*& headQ);
void pop(Node*& headS, Node*& headQ);
void pushTree(Node*& tree, Node*& temp);
void popTree(Node*& tree);
void disInfix(Node* InF);
void disPrefix(Node* PreF);
void disPostfix(Node* PosF);

int main() {

	//Print Postfix

	Node* headS = NULL;
	Node* headQ = NULL;
	
	char input[100];

	cout << "Please input your expression with spaces: ";

	cin.get(input, 100);
	cin.get(); 
	
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] != ' ') {
			if (order(input[i]) == 0) {
				enqueue(headQ, input[i]);
			}		
			else {
				stack(headS, input[i], headQ);
				
			}
		}
	}
	
	//everything left in stack
	while (headS != NULL) {
		pop(headS, headQ);
	}
	
	print(headQ); //print postfix
	

//----------------------------------------------------------------
	
	//Print the Infix Postfix and Prefix

	cout << "Infix, Prefix, or Postfix? ";
	char input2[10];
	cin.get(input2, 10);
	cin.get();

	Node* tree = NULL; //Tree Head or Top
	
	while (headQ != NULL) {
		Node* temp = new Node();
		temp -> setValue(headQ->getValue());
		pushTree(tree, temp);
		headQ = headQ->getNext();
	}
	if (strcmp(input2, "Infix") == 0) { //infix notation
                disInfix(tree);
        }
        else if (strcmp(input2, "Prefix") == 0) { //prefix notation
                disPrefix(tree);
        }
        else if (strcmp(input2, "Postfix") == 0) { //postfix notation
                disPostfix(tree);
        }
        else {
                cout << "Not an option" << endl;
        }


}
void pop(Node*& headS, Node*& headQ) {
	enqueue(headQ, headS->value);
	Node* temp = headS;
	headS = headS -> next;
	delete temp;
}

void enqueue(Node*& headQ, char newvalue) {
	Node* n = new Node();
	n->setValue(newvalue);
	n->setNext(NULL);
	if(headQ == NULL) {
		headQ = n;
}
	else {
		Node* temp = headQ;
		while(temp -> next != NULL) {
			temp = temp -> next;
		}
		temp -> next = n;
	}
}

void stack(Node*& headS, char newvalue, Node*& headQ) {
	if (headS == NULL) {
		Node* n = new Node();
		n -> setValue(newvalue);
		n -> setNext(NULL);
		headS = n;
	}
	else {	//if no has paranthesis
		if (order(newvalue) != 4) {
			if ((order(newvalue) <= order(headS->value)) && (order(headS -> value) != 4)) {
				pop(headS, headQ);
				stack(headS, newvalue, headQ);
			}
			else {
				//only if incoming is bigger than current top value
				Node* n = new Node();
				n->setValue(newvalue);
				n->setNext(headS);
				headS = n;
			}
		}//if has 
		else {
			if (newvalue == ')') {
				while (headS->value != '(') {
					pop(headS, headQ);
				}
				Node* temp = headS;
				headS = headS -> next;
				delete temp;
			}	
		}
	}
}

void print(Node*head){
	Node* temp = head;
	if (temp != NULL) {
		cout << "Postfix: ";
		while(temp != NULL) {
			cout << temp -> value << " ";
			temp = temp -> next;
		}
		cout << endl;
	}
	else {
		cout << "nuthin";
	}
}

//Idea from Nathan Zou to use number scale
int order(char input) {
    if (input == '^') {
        return 3; //Highest
    }
    else if (input == '*' || input == '/') {
        return 2; //Second highest
    }
    else if (input == '+' || input == '-') {
        return 1; //Second lowest
    }
    else if (input == '(' || input == ')') {
        return 4; //Can be anything, as long as it is differentiated from the rest
    }
    else {
        return 0; //Lowest, which are the numbers
    }
}

void pushTree(Node*& tree, Node*& temp) {  
	
	if (tree == NULL) { 
        	temp->setNext(tree);
       	 	tree = temp;
    	}
	else {
        	if (order(temp->getValue()) == 0) { //Checking for numbers
            		temp->setNext(tree);
            		tree = temp;
        	}
        	else { //If token is operator
            		Node* right = tree;
            		popTree(tree);
            		right->setNext(NULL);
           		Node* left = tree;
            		popTree(tree);
           		left->setNext(NULL);
            		temp->setNext(tree);
            		tree = temp;
            		tree->setLeft(left);
           		tree->setRight(right);
        	}		
    	}
}

void popTree(Node*& tree) { 
    if (tree == NULL) {
        cout << "Nuthin" << endl;
    }
    else {
        Node* temp = tree;
        tree = tree->getNext();
        temp->setNext(NULL);
    }
}

void disInfix(Node* InF) { //Display Infix Function
    if (InF != NULL) {
        if (order(InF->getValue()) != 0) {
            cout << "( ";
        }
        disInfix(InF->getLeft());
        cout << InF->getValue() << " ";
        disInfix(InF->getRight());
        if (order(InF->getValue()) != 0) {
            cout << ") ";
        }
    }
}

void disPrefix(Node* PreF) { //Display Prefix Function
    if (PreF != NULL) {
        cout << PreF->getValue() << " ";
        disPrefix(PreF->getLeft());
        disPrefix(PreF->getRight());
    }
}

void disPostfix(Node* PosF) { //Display Postfix Function
    if (PosF != NULL) {
        disPostfix(PosF->getLeft());
        disPostfix(PosF->getRight());
        cout << PosF->getValue() << " ";
    }
}

