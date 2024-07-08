    #include <iostream>
    #include <cstring>
    #include <fstream>
    #include "node.h"
    
    using namespace std;
    
    /*
     *
     * To Do: Sort command with the conditions
     * File Input
     *
     *
     */
    
    
    
    //RED IS 1 !!!!! BLACK IS 0
    
    //same function from binary search tree
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
    void print(Node* head, Trunk *previous, bool prev);
    void file(Node*& head);
    void add(Node*& head, Node*& current, Node*& previous, int data);
    void sort(Node*& head, Node*& current);
    void search(Node* current, int &data);
    Node* del(Node* &head, int data);

    int main() {
    
    	bool play2 = true;
    	char input2[10];
    	Node* head = NULL;
    
    	while (play2 == true) {
    
    		cout << "Console, Read, Print, Search, Delete, or Quit: ";
    		cin.get(input2, 10);
    		cin.get();
    
    		if (strcmp(input2, "Console") == 0) {
    			int data;
    			cout << "What Value: ";
    			cin >> data;
    			cin.get();
    			Node* current = head;
    			Node* previous = NULL;
    			add(head, current, previous, data);
    			if (current != head) {
    				sort(head, current);
    			}
    		}
    		else if (strcmp(input2, "Read") == 0) {
    			file(head);
    		}
    		else if(strcmp(input2, "Print") == 0) {
    			print(head, NULL, false);
    		}
    		else if(strcmp(input2, "Search") == 0) {
    		    int tmp;
    		    cout << "What Number? ";
    		    cin >> tmp;
    		    cin.get();
    		    search(head, tmp);
    		}
    		else if(strcmp(input2, "Delete") == 0) {
    		    int delvalue;
				cout << "What value to delete? ";
				cin >> delvalue;
				cin.get();
				head = del(head, delvalue);
				print(head, NULL, false);
    		}
    		else if (strcmp(input2, "Quit") == 0) {
    			play2 = false;
    		}
    		else {
    			cout << "Invalid Input" << endl;
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
    
    void sort(Node*& head, Node*& current) {
    	Node* parent = NULL;
    	Node* gparent = NULL;
    	//while not head, and the current is red with a black parent
    	while ((current != head) && (current->getColor() != 0) && ((current->getParent())->getColor() == 1)) {
    		parent = current -> getParent();
            	gparent = parent -> getParent();
    		//when the parent is on the left node of the grandparent
            	if (parent == gparent -> getPrev()) {
                		Node* uncle = gparent->getNext();
    			//case 3 where uncle is red and parent is red
                		if (uncle != NULL && uncle->getColor() != 0) {
                    		gparent->setColor(1); 
                    		parent->setColor(0); 
                    		uncle->setColor(0); 
    				current = gparent; //recursively calls on grandparent
               		}
                		else {
    				//case 4 in which uncle is black
    				if (current == parent->getNext()) {
                        			Node* right = parent -> getNext();
    					parent -> setNext(right -> getPrev());
    					if (parent -> getNext() != NULL) {
    						(parent -> getNext()) -> setParent(current);
    					}
    					right -> setParent(parent -> getParent());
    					//if its head
    					if (parent -> getParent() == NULL) {
    						head = right;
    					}
    					else if (parent == (parent -> getParent()) -> getPrev()){
    						(parent -> getParent()) -> setPrev(right);
    					}
    					else {
    						(parent -> getParent()) -> setNext(right);
    					}
    					right -> setPrev(parent);
    					parent -> setParent(right);
                        			current = parent;
                        			parent = current->getParent();
    				}
    				//Case 5 //same as right but left
    				Node* left = gparent -> getPrev();
        				gparent->setPrev(left -> getNext());
        				if (gparent->getPrev() != NULL) {
            				(gparent->getPrev())->setParent(gparent);
        				}
        				left->setParent(gparent -> getParent());
       				//if its head
        				if (gparent->getParent() == NULL) {
            				head = left;
        				}
        				else if (gparent == (gparent -> getParent()) -> getPrev()) {
            				(gparent -> getParent())->setPrev(left);
        				}
        				else {
            				(gparent -> getParent()) -> setNext(left);
        				}
        				left -> setNext(gparent);
        				gparent -> setParent(left);
    				
    				//switch colors between gparent and parent
    				int color = parent -> getColor();
    				parent -> setColor(gparent -> getColor());
    				gparent -> setColor(color);
    				current = parent;
    
                   		}
    		}
    		//when the parent is on the right node of the grandparent same thing as previosu but swapped around
    		else {
    			Node* uncle = gparent->getPrev();
    			//case 3 where uncle is red and parent is red
                		if (uncle != NULL && uncle->getColor() != 0) {
                    		gparent->setColor(1); 
                    		parent->setColor(0); 
                    		uncle->setColor(0); 
    				current = gparent; //recursively calls on grandparent
               		}
                		else {
    				//i didnt rename right and left i just copy and pasted from the first case but they should be opposite left and right
    				//case 4 in which uncle is black
    				if (current == parent->getPrev()) {
                        			Node* left = parent -> getPrev();
    					parent -> setPrev(left -> getNext());
    					if (parent -> getPrev() != NULL) {
    						(parent -> getPrev()) -> setParent(parent);
    					}
    					left -> setParent(parent -> getParent());
    					//if its head
    
    					if (parent -> getParent() == NULL) {
    						head = left;
    					}
    					else if (parent == (parent -> getParent()) -> getPrev()){
    						(parent -> getParent()) -> setPrev(left);
    					}
    					else {
    						(parent -> getParent()) -> setNext(left);
    					}
    					left -> setNext(parent);
    					parent -> setParent(left);
                        			current = parent;
                        			parent = current->getParent();
    				}
    				//Case 5 //same as right but left
    				Node* left = gparent -> getNext();
        				gparent->setNext(left -> getPrev());
        				if (gparent->getNext() != NULL) {
            				(gparent->getNext())->setParent(current);
        				}
        				left->setParent(gparent -> getParent());
       				//if its head
        				if (gparent->getParent() == NULL) {
            				head = left;
        				}
        				else if (gparent == (gparent -> getParent()) -> getPrev()) {
            				(gparent -> getParent())->setPrev(left);
        				}
        				else {
            				(gparent -> getParent()) -> setNext(left);
        				}
        				left -> setPrev(gparent);
        				gparent -> setParent(left);
    				
    				//switch colors between gparent and parent
    				int color = parent -> getColor();
    				parent -> setColor(gparent -> getColor());
    				gparent -> setColor(color);
    				current = parent;
    				print(head, NULL, false);
                   		}
    
    		}
    	}
    	head -> setColor(0); //always set root to black
    }
    
    void add(Node*& head, Node*& current, Node*& previous, int data) {
    		//firts person is always black
    		if (head == NULL) {
    			head = new Node();
    			current = head;
    			head -> setData(data);
    			head -> setColor(0);
    		}
    		else {
    		//always comes in as red
    			//if incoming is less than current node
    			if (data < (current -> getData())) {
    				previous = current;
    				current = current -> getPrev();
    				//if there is nothing below insert the node
    				if (current == NULL) {
    					current = new Node();
    					current -> setData(data);
    					previous -> setPrev(current);
    					current -> setParent(previous);
    					sort(head, current);
    					return;
    				}
    				else {
    					add(head, current, previous, data);
    				}
    			}
    			//if incoming is greater than the current node
    			else {
    				previous = current;
    				current = current -> getNext();
    				if (current == NULL) {
    					current = new Node();
    					current -> setData(data);
    					previous -> setNext(current);
    					current -> setParent(previous);
    					sort(head, current);
    					return;
    				}
    				else {
    					add(head, current, previous, data);
    				}
    			}	
    		}
    
    }
    
    
    //from bst last unit
    void file(Node*& head) {	
    	char input[10000];
        	char fname[20];
        	int modify[100];
        	int sizes = 0;
        	int count = 0;
        	memset(input, 0, 10000);
        	memset(fname, 0, 100);
        	memset(modify, 0, 100);
        	cout << endl << "Name? ";
        	cin.get(fname, 20);
        	cin.get();
        	streampos size;
        	ifstream file(fname, ios::in | ios::binary | ios::ate);
        	if (file.is_open()) {
            	size = file.tellg();
            	file.seekg(0, ios::beg);
            	file.read(input, size);
            	file.close();
            	createArray(input, modify, count); 
            	for (int i = 0; i < 100; i++) {
                		if (modify[i] != 0) {
                    		sizes++;
                		}
            	}
            	Node* current = NULL;
            	Node* previous = NULL;
            	for (int i = 0; i < sizes; i++) {
                		if (modify[i] == 0) {
    				break;
    			}
                		current = head;
                		add(head, current, previous, modify[i]);
            	}
        	}
    }
    
    //same print function as the BST
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
    	if (head -> getColor() == 0) { //b
    		cout << head -> getData() << "B" << endl;
    	}
    	else { //r
    		cout << head -> getData() << "R" << endl;
    	}
    	if (previous) {
    		previous -> str = prevStr;
    	}
    	trunk->str = (char*)("   |");
    	print(head -> getNext(), trunk, false);
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
    
    //from bst last unit
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
