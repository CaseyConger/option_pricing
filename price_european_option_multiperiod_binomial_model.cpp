#include <iostream>
#include <cmath>

using namespace std;


// Node struct used for storing the "leafs" in these trees
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
	// ~Tree();


	double value(int time, int height);
	void set(int time, int height, double value);

	node ** nodeArray();

	void print();

};

node ** Tree::nodeArray(){
	return _treeArray;
}

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

// Tree::~Tree() {
// 	delete _treeArray;
// }

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

class OptionPriceTree;

// Security Tree
class SecurityTree : public Tree {
friend class OptionPriceTree;
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



class OptionTree : public Tree {
protected:
	double _strike;
	int _expiration;
	string _type;

};





class OptionPriceTree : public Tree {
private:
	double _strike;
	int _expiration;
	double _riskFreeRate;
	double _upProb;
	double _downProb;
	string _type;
	SecurityTree _securityTree();

public:
	OptionPriceTree(string optionType,
			   double strike,
			   int expiration,
			   double riskFreeRate,
			   SecurityTree securityTree);

};

OptionPriceTree::OptionPriceTree(string optionType,
					   double strike,
					   int expiration,
					   double riskFreeRate,
					   SecurityTree securityTree)
				: Tree(expiration) {
	_strike = strike;
	_expiration = expiration;
	_riskFreeRate = riskFreeRate;
	_type = optionType;
	double up = securityTree._up;
	double down = securityTree._down;

	_upProb = (_riskFreeRate - down)/(up - down);
	_downProb = 1.0 - _upProb;
	

	for (int j = 0; j <= expiration; j++) {
		double tmp = securityTree.nodeArray()[expiration][j].value - _strike;
		_treeArray[expiration][j].value = tmp > 0 ? tmp : 0;
	}

	if (optionType == "call") {
		for (int i = _numTimeSteps - 1; i >=0 ; --i)
		{
			for (int j = 0; j <= i; ++j)
			{
				
				_treeArray[i][j].value = _upProb * _treeArray[i+1][j+1].value;
				_treeArray[i][j].value += _downProb * _treeArray[i+1][j].value;
				_treeArray[i][j].value *= 1.0/_riskFreeRate;
			}
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


	SecurityTree first_tree(1.06529, 100., 1);
	SecurityTree second_tree(3.0, 200.0, 15);
	OptionPriceTree opt_tree("call", 100.0, 1, 1.01, first_tree);
	first_tree.print();
	opt_tree.print();

	cout << opt_tree.value(0,0) << endl;




	return 0;
}