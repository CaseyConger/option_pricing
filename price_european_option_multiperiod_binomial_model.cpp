#include <iostream>
#include <cmath>

using namespace std;


// Node struct
struct node
{
	double value;
	int time;
	int height;
	node * up;
	node * down;
};


// Basic tree class
class Tree
{
protected:
	node ** _treeArray;

public:
	// Constructors & Destructors
	Tree();
	Tree(int numTimeSteps);
	~Tree();


	double value(int time, int height);
	void set(int time, int height, double value);

};

Tree::Tree(int numTimeSteps) {
	_treeArray = new node*[numTimeSteps + 1];
	_treeArray[0] = new node[1];
	for (int i = 1; i <= numTimeSteps; ++i) {
		_treeArray[i] = new node[i + 2];
	}
}

Tree::~Tree() {
	delete _treeArray;
}

double Tree::value(int time, int height) {
	return _treeArray[time][height].value;
}

void Tree::set(int time, int height, double value) {
	
	_treeArray[time][height].value = value;
	_treeArray[time][height].time = time;
	_treeArray[time][height].height = height;
}






int main(int argc, char* argv[]) {
	// cout << "---------------------------------------------------------------";
	// cout << "--------" << endl;
	// cout << "---------------------------------------------------------------";
	// cout << "--------" << endl;
	// cout << "--Program used for pricing European Options in the multinomial";
	// cout << " model--" << endl;
	// cout << "---------------------------------------------------------------";
	// cout << "--------" << endl;
	// cout << "---------------------------------------------------------------";
	// cout << "--------" << endl;





	return 0;
}