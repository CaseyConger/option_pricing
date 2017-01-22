#include <iostream>
#include <cmath>

using namespace std;

class node
{
private:
	int _time;
	int _height;
	double _underlying;
	double _option_value;
public:
	node(){};
	node(int time,
		 int height);
	node(int time,
		 int height,
		 double underlying,
		 double option_value);

	int time();
	int height();
	double underlying();
	double option_value();
};

int node::time() { return _time; }
int node::height() { return _height; }
double node::underlying() { return _underlying; }
double node::option_value() { return _option_value; }

node::node(int time,
		   int height) {

	_time = time;
	_height = height;
}

node::node(int time,
		   int height,
		   double underlying,
		   double option_value) {

	_time = time;
	_height = height;
	_underlying = underlying;
	_option_value = option_value;
}



class tree
{
private:
	node _up;
	node _down;
	node _initial;
public:
	tree(){};
	tree(node up_node,
		 node down_node);

	node up();
	node down();
	void set_up_node(node up_node);
	void set_down_node(node down_node);
};

tree::tree(node up_node,
		   node down_node) {

	_up = up_node;
	_down = down_node;
}

int main(int argc, char* argv[]) {
	cout << "---------------------------------------------------------------";
	cout << "--------" << endl;
	cout << "---------------------------------------------------------------";
	cout << "--------" << endl;
	cout << "--Program used for pricing European Options in the multinomial";
	cout << " model--" << endl;
	cout << "---------------------------------------------------------------";
	cout << "--------" << endl;
	cout << "---------------------------------------------------------------";
	cout << "--------" << endl;

	node node_1(2,2);
	node node_2(3,4);
	node node_3;

	node_3 = node_1;

	cout << node_3.time() << endl;

	return 0;
}