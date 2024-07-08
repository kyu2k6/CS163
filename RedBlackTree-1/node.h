#ifndef Node_h
#define Node_h

class Node {
	public:
		Node();
		~Node();

		Node* getNext();
		Node* getPrev();
		int getData();
		Node* getParent();
		int getColor();

		void setColor(int);
		void setParent(Node*);
		void setNext(Node*);
		void setPrev(Node*);
		void setData(int);
	private:
		int color;
		Node* parent;
		int data;
		Node* next;
		Node* prev;
};
#endif
