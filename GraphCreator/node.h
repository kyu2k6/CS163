#ifndef node_h
#define node_h

using namespace std;

class node {
	public:
  		node();
  		~node();
  		char getName();
  		int getWeight();
  		int getEdge(int);
  		void setName(char);
  		void setWeight(int);
  		void setEdge(int, int);
	private:
  		char name;
  		int weight;
  		int edges[20];
		//no more than 20 vertices a panel
};
#endif
