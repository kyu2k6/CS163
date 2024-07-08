//Kevin Yu
//4-6-23
//Binary Search Tree with add print search and delete

#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

//trunk function from nathan zou to help print the tree

struct Trunk { //Used for printing
    Trunk *previous;
    char* str;

    Trunk(Trunk* previous, char* str) {
        this->previous = previous;
        this->str = str;
    }
};

void showTrunks(Trunk* p) { //Uesd for printing
    if (p == NULL) 
        return;

    showTrunks(p->previous);

    cout << p->str;
}

void createArray(char* in, int* array, int& count);
void add(Node*& head, Node*& current, Node*& prev, int data);
void print(Node* head, Trunk *previous, bool prev);
void search(Node* current, int &data);
Node* del(Node* &head, int data);

int main() {

	char option[10];
	char filename[20];
	char input[10000];
	bool play = true;
	int count = 0;
	int array[100];
	int modesize = 0;
	
	//see if need to create tree 
	bool tree = false;

	while (play == true) {

		//help from nathan zou with memset
		memset(input, 0, 10000);
		memset(array ,0, 100);
		
		

		modesize = 0;
		count = 0;
		cout << "File or Console? ";
		cin.get(option, 10);
		cin.get();
		//console input
		if (strcmp(option, "Console") == 0) {
			tree = true;
			cout << "Enter input with spaces: ";
			char in[10000];	
			cin.get(in, 100);
			cin.get();
			createArray(in, array, count);
			for (int i = 0; i < 100; i++) {
				if (array[i] != 0) {
					modesize++;
				}
			}
		}
		//file input
		else if (strcmp(option, "File") == 0) {
			tree = true;
			cout << "File name: ";
			cin.get(filename, 20);
			cin.get();
			streampos size;
			ifstream file(filename, ios::in | ios::binary | ios::ate);
			if (file.is_open()) {
				size = file.tellg();
				file.seekg(0, ios::beg);
				file.read(input, size);
                    		file.close();
				createArray(input, array, count);
				for (int i = 0; i < 100; i++) {
					if(array[i] != 0) {
						cout << array[i] << " ";
						modesize++;
					}
				}
			}
		}
		//wrong input
		else {
			cout << "Wrong Input Type" << endl;
		}

		//are we creating tree?
		if (tree == true) {
		
			Node* head = NULL;
			Node* current = NULL;
			Node* previous = NULL;
			for (int i = 0; i < modesize; i++) {
				if(array[i] != 0) {
					current = head;
					add(head, current, previous, array[i]);
				}
			}
			print(head, NULL, false);
			bool part2 = true;
			char options2[10];
			int searchInput;
			while (part2 = true) {
				cout << "Search, Add, Delete, or Quit: ";
				cin.get(options2, 10);
				cin.get();
				if (strcmp(options2, "Search") == 0) {
					cout << "What num? ";
					cin >> searchInput;
					cin.get();
					search(head, searchInput);
				}	
				else if (strcmp(options2, "Add") == 0) {
					int value;
					cout << "Add Value: ";
					cin >> value;
					cin.get();
					Node* current = NULL;
					Node* previous = NULL;
					current = head;
					add(head, current, previous, value);
					print(head, NULL, false);
					cout << endl;
				}
				else if (strcmp(options2, "Delete") == 0) {
					int delvalue;
					cout << "What value to delete? ";
					cin >> delvalue;
					cin.get();
					head = del(head, delvalue);
					print(head, NULL, false);
				}
				else {
					cout << "Not an option." << endl;
				}
			}
		}
	}
	return 0;
}

Node* del(Node* &head, int data) {
	Node* prev = head -> getPrev();
	Node* next = head -> getNext();
	if (head == NULL) {
		return head;
	}
	else if (data < head -> getData()) {
		head -> setPrev(del(prev, data));
	}
	else if (data > head -> getData()) {
		head -> setNext(del(next, data));
	}
	else {
		if (head -> getNext() == NULL && head -> getPrev() == NULL) {
			head -> ~Node();
			head = NULL;
			return head;
		}
		else if (head -> getPrev() == NULL) {
			Node* temp = head;
			head = head -> getNext();
			temp -> ~Node();
			return head;
		}
		else if (head -> getNext() == NULL) {
			Node* temp = head;
			head = head -> getPrev();
			temp -> ~Node();
			return head;
		}
		else {
			Node* temp = head -> getNext();
			while (temp -> getPrev() != NULL) {
				temp = temp -> getPrev();
			}
			head -> setData(temp -> getData());
			Node* h = head -> getNext();
			head -> setNext(del(h, temp->getData()));
		}
	}
	return head;
}

void search(Node* current, int& data) { 
	while (current -> getData() != data && current != NULL) {
		if(current != NULL) {
			if(current -> getData() > data) {
				current = current -> getPrev();
			}
			else {
				current = current -> getNext();
			}
		}
		if (current == NULL) {
			break;
		}
	}
	if (current != NULL) {
		if(current -> getData() == data) {
			cout << "In the Tree." << endl;
		}
	}
	else {
		cout << "Not in the Tree." << endl;
	}
}


void print(Node* head, Trunk *previous, bool prev) {
	
	if (head == NULL) {
		return;
	}

	char* prevStr = (char*)("    ");
	Trunk *trunk = new Trunk(previous, prevStr);
	print(head -> getPrev(), trunk, true);

	if (!previous) {
		trunk -> str = (char*)("---");
	}
	else if (prev) {
		trunk -> str = (char*)(".---");
		prevStr = (char*)("   |");
	}
	else {
		trunk -> str = (char*)("'---");
		previous -> str = prevStr;
	}
	showTrunks(trunk);
	cout << " " << head->getData() << endl;

	if (previous) {
		previous -> str = prevStr;
	}
	trunk->str = (char*)("   |");
	print(head -> getNext(), trunk, false);
}


void add(Node*& head, Node*& current, Node*& previous, int data) {
	//first
	if (head == NULL) {
		head = new Node();
		head -> setData(data);
		return;
	}
	else {
		//if smaller
		if (data < current -> getData()) {
			previous = current;
			current = current -> getPrev();
			//if nothing here just insert it in tree
			if (current == NULL) {
				current = new Node();
				current -> setData(data);
				previous -> setPrev(current);
				return;
			}
			else {
				//repeat
				add(head, current, previous, data);
			}
		}
		//if bigger
		else {
			previous = current;
			current = current -> getNext();
			if (current == NULL) {
				current = new Node();
				current -> setData(data);
				previous -> setNext(current);
				return;
			}
			else {
				add(head, current, previous, data);
			}
		}
	}
}



void createArray(char* in, int* array, int& count) {
	int x = 0; // counter of char before add
	for (int i = 0;i < strlen(in); i++) {
		if (in[i] == ' ') {
			//if one digit so far, add it
			if(x == 1) {
				int temp = 0;
				temp = in[i-1] - '0';
				array[count] = temp;
				count++;
				x = 0;
			}	
			else {
			//if more than 1 digit, add everything till where was space
				int temp = 0;
				for (int j = 0; j < x; j++) {
					temp = 10 * temp + (in[i- x + j] - '0');
				}
				array[count] = temp;
				count++;
				x = 0;
			}
		}
		//If no space
		else {
			int temp = 0;
			// add digit counter
			x++;
			//add everything at the end
			if (i == strlen(in) - 1) {
				for (int j = 0; j < x; j++) {
					temp = 10 * temp + (in[i + j + 1 - x] - '0');
				}
				array[count] = temp;
				count++;
			}
		}
	}
}

