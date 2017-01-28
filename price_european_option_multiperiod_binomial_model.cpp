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

node ** Tree::nodeArray()
{
	return _treeArray;
}

Tree::Tree(int numTimeSteps)
{
	_numTimeSteps = numTimeSteps;
	_treeArray = new node*[numTimeSteps + 1];
	_treeArray[0] = new node[1];

	for (int i = 1; i <= _numTimeSteps; ++i)
	{
		_treeArray[i] = new node[i + 2];
	}

	for (int i = 0; i < _numTimeSteps + 1; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
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

double Tree::value(int time, int height)
{
	return _treeArray[time][height].value;
}

void Tree::set(int time, int height, double value)
{	
	_treeArray[time][height].value = value;
	_treeArray[time][height].time = time;
	_treeArray[time][height].height = height;
}

void Tree::print()
{
	for (int i = 0; i < _numTimeSteps + 1; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			cout << "[" << i << "][" << j << "] = ";
			cout << _treeArray[i][j].value << " ";
		}
		cout << endl;
	}
}



class OptionTree;

// Security Tree
class SecurityTree
: public Tree
{
friend class OptionTree;

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
: Tree(numTimeSteps)
{
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


// enum that stores the different option types available
enum OptionType
{
	call,
	put
};

// Class that will store the pay off functions for different option types
class Payoff
{
private:
	double _strike;
	OptionType _optionType;

public:
	Payoff(OptionType optionType,
		   double strike);
	double operator()(double spot) const;
};

Payoff::Payoff(OptionType optionType,
			   double strike)
{
	_optionType = optionType;
	_strike = strike;
}

double Payoff::operator ()(double spot) const
{
	switch (_optionType)
	{
	case call :
		return max(spot - _strike, 0.0);
	case put :
		return max(_strike - spot, 0.0);
	default:
		throw("Option type undefined.");
	}
}


class OptionTree
:
	public Tree
{
private:
	double _strike;
	int _expiration;
	double _riskFreeRate;
	double _upProb;
	double _downProb;
	OptionType _optionType;
	Payoff * _payoff();
	SecurityTree _underlyingTree();
	// Tree * _priceTree;

	// Tree * makePriceTree();

public:
	OptionTree(OptionType optionType,
			   Payoff payoff,
			   int expiration,
			   double riskFreeRate,
			   SecurityTree underlyingTree);

};

OptionTree::OptionTree(OptionType optionType,
					   Payoff payoff,
					   int expiration,
					   double riskFreeRate,
					   SecurityTree underlyingTree)
:
	Tree(expiration)
{
	_numTimeSteps = expiration;
	_riskFreeRate = riskFreeRate;
	_optionType = optionType;
	


	double up = underlyingTree._up;
	double down = underlyingTree._down;

	_upProb = (_riskFreeRate - down)/(up - down);
	_downProb = 1.0 - _upProb;
	
	for (int j = 0; j <= _numTimeSteps; j++)
	{
		double tmp = underlyingTree.nodeArray()[_numTimeSteps][j].value;
		_treeArray[_numTimeSteps][j].value = payoff(tmp);
	}

	switch (_optionType)
	{
	case call :
		for (int i = _numTimeSteps - 1; i >=0 ; --i)
		{
			for (int j = 0; j <= i; ++j)
			{
				_treeArray[i][j].value = _upProb * _treeArray[i+1][j+1].value;
				_treeArray[i][j].value += _downProb * _treeArray[i+1][j].value;
				_treeArray[i][j].value *= 1.0/_riskFreeRate;
			}
		}
	case put :
		break;
	}	
}




int main(int argc, char* argv[])
{
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
	Payoff payoff(call, 105.0);
	cout << payoff(200.) << endl;

	SecurityTree first_tree(1.06529, 100., 1);
	SecurityTree second_tree(3.0, 200.0, 15);
	OptionTree opt_tree(call, payoff, 1, 1.01, first_tree);
	first_tree.print();
	opt_tree.print();

	cout << opt_tree.value(0,0) << endl;




	return 0;
}