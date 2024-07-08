#ifndef Node_h
#define Node_h

class Node {
	public:
		Node();
		~Node();

		Node* getNext();
		Node* getPrev();
		int getData();

		void setNext(Node*);
		void setPrev(Node*);
		void setData(int);
	private:
		int data;
		Node* next;
		Node* prev;
};
#endif
