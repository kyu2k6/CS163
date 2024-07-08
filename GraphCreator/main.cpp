//Kevin Yu
//6-9-23
//Graph Creator

#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

node* search(node** list, char in, int index);
void addV(node** list, int index);
void removeV(node** list, int index);
void addE(node** list, int index);
void removeE(node** list, int index);
void print(node** list, int index);
void path(node** list, int index);

int main() {

	node** list = new node*[20]; // vertex list
	int index = 0; //index counter	
	bool play = true;
	char input[5];
	while (play == true) {
		cout << "Add Vertex(AV), Add Edge(AE), Remove Vertex(RV), Remove Edge(RE), Find Path(FP), Print, Quit: ";
		cin.get(input, 5);
		cin.get();
		if (strcmp(input, "AV") == 0 ) { //add vertex
			addV(list, index);
			index++;
		}
		else if (strcmp(input, "RV") == 0) { //delete vertex
      			removeV(list, index);
      			index--;
    		}
    		else if (strcmp(input, "AE") == 0) { //add edge
      			addE(list, index);
    		}
    		else if (strcmp(input, "RE") == 0) { //delete edge
			removeE(list, index);
    		}
    		else if (strcmp(input, "Print") == 0) { //print
      			print(list, index);
   		}	
    		else if (strcmp(input, "FP") == 0) { //shortest path algorithm	
      			path(list, index);
    		}
		else if (strcmp(input, "Quit") == 0 ) {
			play = false;
		}
		else {
			cout << "Invalid Input" << endl;
		}
	}
}

node* search(node** list, char in, int index) { //search for index
	int i = 0;
	while (i < index) {
		if ((list[i]) -> getName() == in) {
			return (list[i]);
		}
		else {
			i++;
		}
	}

	return NULL;
}

void addV(node** list, int index) {
	node* newNode = new node();
	newNode -> setWeight(index);
	char input;
	cout << "New Vertex: ";
	cin >> input;
	cin.get();
	newNode -> setName(input);
	list[index] = newNode;
}

void removeV(node** list, int index) {
	if (list[0] == NULL) {
		return; //no vertex 
	}

	char input;
	cout << "Delete vertex: ";
	cin >> input;
	cin.get();
	node* n = search(list, input, index);
	if (n == NULL) {
		cout << "Does not exist." << endl;
		return;
	}
	int tmp = n -> getWeight();
	n -> ~node();
	//reset all edge list for each node
	for (int i = 0; i < index; i++) {
		node* current = list[i];
		for (int edge = tmp; edge < index; edge++) {
			if (edge == index - 1) {
				current -> setEdge(edge, 0);
			}
			else {
				int next = edge + 1;
				current -> setEdge(edge, current -> getEdge(next));
			}
		}
		list[i] = current;
	}
	list[tmp] = NULL;
	while (tmp < index) {
		if (tmp == index - 1) {
			list[tmp] = NULL;
			break;
		}
		list[tmp] = list[tmp+1];
		(list[tmp]) -> setWeight(tmp);
		tmp++;
	}
}

void addE(node** list, int index) {
	if (list[0] == NULL || list[1] == NULL) {
		cout << "Need 2. " << endl;
		return;
		//only one node
	}
	char input, inputs;
	cout << "Vertex 1: ";
	cin >> input;
	cin.get();
	cout << "Vertex 2: ";
	cin >> inputs;
	cin.get();
	node* n1 = search(list, input, index);
	node* n2 = search(list, inputs, index);
	if (n1 == NULL || n2 == NULL) {
		cout << "Doesn't Exist. " << endl;
		return;
		//cant find
	}
	int eVal;
	cout << "Edge Value: ";
	cin >> eVal;
	cin.get();
	n1 -> setEdge(n2 -> getWeight(), eVal);
	n2 -> setEdge(n1 -> getWeight(), eVal);
}

void removeE(node** list, int index) {
	if(list[0] == NULL || list[1] == NULL) {
		cout << "Need 2. " << endl;
		return;
	}
	char input, inputs;
	cout << "Vertex 1: ";
	cin >> input;
	cin.get();
	cout << "Vertex 2: ";
	cin >> inputs;
	cin.get();
	node* n1 = search(list, input, index);
	node* n2 = search(list, inputs, index);
	if (n1 == NULL || n2 == NULL) {
		cout << "Doesn't Exist. " << endl;
		return;
		//cant find
	}
	n1 -> setEdge(n2 -> getWeight(), 0);
	n2 -> setEdge(n1 -> getWeight(), 0);
}

void print(node** list, int index) {
	char display[21][21];
	//create empty matrix
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			display[i][j] = ' ';
		}
	}

	int edgeD[20][20];
	int count = 0;
	//adjancey matrix
	while(count < index) {
		display[0][count+1] = (list[count]) -> getName();
		display[count+1][0] = (list[count]) -> getName();
		count++;
	}
	//edge display list
	for (int i = 0; i < index; i++ ) {
		node* n = list[i];
		for (int j = 0; j < index; j++) {
			node* nn = list[j];
			if (n -> getEdge(nn -> getWeight()) != 0) {
				edgeD[i][j] = 'T';
			}
			else {
				edgeD[i][j] = 'F';
			}
		}
	}
	//fill display list
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < index; j++) {
			display[i+1][j+1] = edgeD[i][j];
		}
	}
	//display adjancecy matrix
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (display[i][j] == 'T' && i != 0 && j != 0) {
				cout << display[i][j] << '\t';
			}
			else if (display[i][j] == 'F' && i != 0 && j != 0) {
				cout << display[i][j] << '\t';
			}
			else {
				cout << display[i][j] << '\t';
			}
		}
		if (display[i+1][0] == ' ') {
			break;
		}	
	}	
}

void path(node** list, int index) {

}
