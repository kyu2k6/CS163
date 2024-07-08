#include <iostream>
#include "node.h"

using namespace std;

node::node() {
	name = '\0';
	int x = 0;
	while (x < 20) {
		edges[x] = 0;
		x++;
	}
}

node::~node() {
	name = '\0';
	weight = 0;
	int y = 0;	
	while (y < 20) {
		edges[y] = 0;
		y++;
	}
}

char node::getName() {
	return name;
}

int node::getWeight() {
	return weight;
}

int node::getEdge(int index) {
	return edges[index];
}

void node::setName(char newName) {
	name = newName;
}

void node::setWeight(int newWeight) {
	weight = newWeight;
}

void node::setEdge(int index, int data) {
	edges[index] = data;
}
