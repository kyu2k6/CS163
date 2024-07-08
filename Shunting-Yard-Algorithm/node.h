#ifndef nodeh
#define nodeh

class Node {
	public:
		Node(); //constructor
		~Node(); //destructor

		char getValue();
		Node* getNext();
		Node* getRight();
		Node* getLeft();

		void setValue(char value);
		void setNext(Node* next);
		void setRight(Node* newRight);
		void setLeft(Node* newLeft);
	
		Node* next;
		char value;
		Node* left;
		Node* right;
};
#endif
