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
	int _numTimeSteps;

public:
	// Constructors & Destructors
	Tree();
	Tree(int numTimeSteps);
	~Tree();


	double value(int time, int height);
	void set(int time, int height, double value);

	void print();

};

Tree::Tree(int numTimeSteps) {
	_numTimeSteps = numTimeSteps;
	_treeArray = new node*[numTimeSteps + 1];
	_treeArray[0] = new node[1];
	for (int i = 1; i <= _numTimeSteps; ++i) {
		_treeArray[i] = new node[i + 2];
	}

	for (int i = 0; i < _numTimeSteps + 1; ++i) {
		for (int j = 0; j <= i; ++j){
			_treeArray[i][j].time = i;
			_treeArray[i][j].height = j;
			_treeArray[i][j].down = &_treeArray[i + 1][j];
			_treeArray[i][j].up = &_treeArray[i + 1][j + 1];
		}
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

void Tree::print() {
	for (int i = 0; i < _numTimeSteps + 1; ++i) {
		for (int j = 0; j <= i; ++j) {
			cout << "[" << i << "][" << j << "] = ";
			cout << _treeArray[i][j].value << endl;
		}
	}
}


// Security Tree
class SecurityTree : public Tree {
private:
	double _up;
	double _down;
	double _S_0;
public:
	SecurityTree(double upFactor,
				 double S_0,
				 int numTimeSteps);

};

SecurityTree::SecurityTree(double upFactor,
						   double S_0,
						   int numTimeSteps)
				: Tree(numTimeSteps) {
	_up = upFactor;
	_down = 1.0/_up;
	_S_0 = S_0;

	for (int i = 0; i < _numTimeSteps + 1; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			_treeArray[i][j].value = _S_0 * pow(_up, j) * pow(_down, i - j);
		}
	}
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


	SecurityTree first_tree(2.0, 100., 15);
	first_tree.print();


	return 0;
}