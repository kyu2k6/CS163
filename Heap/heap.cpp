//Kevin Yu
//3-4-2023
//Make heap tree

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void createArray(char* in, int* array, int& count);
void del(int* heap, int size);
void print(int* heap, int size);
int maxHeap(int* tmp);
void Heap(int* array, int* heap, int size);

int main() {
	
	bool play = true;
	char input[20];
	char readinput[10000];
	char fileName[20];
	int array[100];

	for (int i = 0; i < 100; i++) {
		array[i] = 0;
	}

	int count = 0;

	while (play == true) {
		
		for (int i =  0; i < 100; i++) {
			array[i] = 0;
		}
		count = 0;

		cout << "Manual, File, Quit: ";
		cin.get(input, 20);
		cin.get();	
		if (strcmp(input, "Manual") == 0) {
			cout << "Enter Numbers: " << endl;
			char in[10000];
			cin.get(in, 10000);
			cin.get();
			createArray(in, array, count);
			cout << "Input: ";
			for (int i = 0; i < 100; i++) {
				if (array[i] == 0) break;
				cout << array[i] << " ";
			}
			cout << endl;

			//makes the tree
			int heap[101];
           		for (int z = 0; z < 101; z++) {
                		heap[z] = 0;
            		}
            		//get size of array
            		int size = 0;
            		for (int i = 0; i < 100; i++) {
                		if (array[i] != 0) {
                    			size++;
                		}
                	else break;
            		}
            		Heap(array, heap, size); 
            		cout << "Heap: " << endl;
            		for (int i = 1; i < 101; i++) {
                		if (heap[i] == 0) break;
                		cout << heap[i] << " ";
            		}
            		cout << endl;
            		print(heap, size); 
            		del(heap, size); 
        	}

		else if (strcmp(input, "File") == 0) {
			cout << "File Name: ";
                	cin.get(fileName, 20);
                	cin.get();

			//These file lines with help from Nathan Zou
                	streampos size;
                	ifstream file(fileName, ios::in | ios::binary | ios::ate);
		       	if (file.is_open()) {
                    		size = file.tellg();
                    		file.seekg(0, ios::beg);
                    		file.read(readinput, size);
                    		file.close();

                    		createArray(readinput, array, count);
                    		cout << "Input: ";
                   		for (int i = 0; i < 100; i++) {
                        		if (array[i] == 0) break;
                        		cout << array[i] << " ";
                    		}
				cout << endl; 
			}

			//makes the tree
			int fheap[101];
           		for (int z = 0; z < 101; z++) {
                		fheap[z] = 0;
            		}
            		//get size of array
            		int fsize = 0;
            		for (int i = 0; i < 100; i++) {
                		if (array[i] != 0) {
                    			fsize++;
                		}
                	else break;
            		}
            		Heap(array, fheap, fsize); 
            		cout << "Heap: " << endl;
            		for (int i = 1; i < 101; i++) {
                		if (fheap[i] == 0) break;
                		cout << fheap[i] << " ";
            		}
            		cout << endl;
            		print(fheap, fsize); 
            		del(fheap, fsize); 

		}
		else if (strcmp(input, "Quit") == 0) {
			play = false;
		}
		else {
			cout << "Invalid Input" << endl;
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
				cout << array[count];
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

void Heap(int* array, int* heap, int size) { 
    int current = 1;
    //set index at 1 to big node
    heap[1] = array[maxHeap(array)]; 
    array[maxHeap(array)] = 0;
    while (current <= size) {
        if (heap[2 * current] == 0) { //If the right child is empty fill in the right child with the next max int
            heap[2 * current] = array[maxHeap(array)];
            array[maxHeap(array)] = 0;
            //fill in the left child with the one after previous
            heap[2 * current + 1] = array[maxHeap(array)];
            array[maxHeap(array)] = 0;
        }
        else { //If right child is filled, fill in the left child with the next max int
            heap[2 * current + 1] = array[maxHeap(array)];
            array[maxHeap(array)] = 0;
        }
        current++;
    }
}

int maxHeap(int* array) {
    int i = 0;
    for (int x = 0; x < 100; x++) {
        if (array[x] >= array[i]) {
            i = x;
        }
    }
    return i;
}

void del(int* heap, int size) { 
    for (int i = 1; i <= size; i++) {
        cout << heap[i] << " ";
        heap[i] = 0;
    }
    cout << endl;
}

void print(int* heap, int size) { 
    for (int i = 1; i <= size / 2; i++) {
        if (heap[i] != 0) {
            cout << endl << heap[i];
        }
        if (heap[i * 2] != 0) {
            cout << " --- R: " << heap[i * 2] << endl;
        }
        if (heap[i * 2 + 1] != 0) {
            cout << " |" << endl;
            cout << "  --- L: " << heap[i * 2 + 1] << endl;
        }
    }
    cout << endl;
}
