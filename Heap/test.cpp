#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void PARSE(char* in, int* modify, int& count);
void DELETE(int* heap, int size);
void PRINT(int* heap, int size);
int maxHeap(int* array);
void HEAP(int* modify, int* heap, int size);

int main() {
    bool running = true;
    char command[10];
    char input[10000];
    char fileName[30];
    int modify[100];
    for (int i = 0; i < 100; i++) {
        modify[i] = 0; //Clear array
    }
    int count = 0; //Number of chars

    cout << "Welcome to Heap" << endl;
    while (running == true) {
        for (int i = 0; i < 100; i++) {
            modify[i] = 0; //Clear int array
        }
        count = 0;
        cout << endl << "Options: RUN and QUIT" << endl;
        cin.get(command, 10);
        cin.clear();
        cin.ignore(10000, '\n');
        if (strcmp(command, "RUN") == 0 || strcmp(command, "Run") == 0) { //Run command
            cout << "File input or Manual input? ";
            cin.get(command, 10);
            cin.clear();
            cin.ignore(10000, '\n');
            if (strcmp(command, "FILE") == 0 || strcmp(command, "File") == 0) { //File command, for file input use 
                cout << "What is the file name? (Include the .txt) ";
                cin.get(fileName, 30);
                cin.clear();
                cin.ignore(100000, '\n');
                streampos size;
                ifstream file(fileName, ios::in | ios::binary | ios::ate);
                if (file.is_open()) {
                    size = file.tellg();
                    file.seekg(0, ios::beg);
                    file.read(input, size);
                    file.close();
                    PARSE(input, modify, count);
                    cout << "Input: ";
                    for (int i = 0; i < 100; i++) {
                        if (modify[i] == 0) break;
                        cout << modify[i] << " ";
                    }
                    cout << endl;
                }
            }
	   }
	   
            else if (strcmp(command, "MANUAL") == 0 || strcmp(command, "Manual") == 0) { //Manual command, for user manual input
											 //[<65;26;18M                cout << "Enter each number followed by a space:" << endl;
                char in[100000];
                cin.get(in, 100000);               
		cin.clear();
                cin.ignore(1000000, '\n');
                //Parse input by spaces[<65;28;20M                PARSE(in, modify, count);  //Parse input to modify array[<65;28;20M                cout << "Input: ";
                for (int i = 0; i < 100; i++) {
                    if (modify[i] == 0) break;
                    	cout << modify[i] << " ";
                	
			}
	    	}	
                cout << endl;
	}
}

void PARSE(char* in, int* modify, int& count) { //Parse function, takes in manual input
    int x = 0; //keeps track of number of chars before space
    for (int i = 0; i < strlen(in); i++) {
        if (in[i] == ' ') {
            if (x == 1) {
                int temp = 0;
                temp = in[i - 1] - '0';
                modify[count] = temp;
                count++;
                x = 0;
            }
            else {
                int temp = 0;
                for (int a = 0; a < x; a++) {
                    temp = 10 * temp + (in[i - x + a] - '0');
                }
                modify[count] = temp;
                count++;
                x = 0;
            }
        }
        else {
            int temp = 0;
            x++;
            if (i == strlen(in) - 1) { //last possible pair of chars
                for (int a = 0; a < x; a++) {
                    temp = 10 * temp + (in[i + a + 1 - x] - '0');
                }
                modify[count] = temp;
                count++;
            }
        }
    }
}
