#include <iostream>
#include <cmath>

using namespace std;

// class node
// {
// private:
// 	int _time;
// 	int _height;
// 	double _value;
// 	node * _up;
// 	node * _down;
// public:
// 	node(){};
// 	node(int time,
// 		 int height);
// 	node(int time,
// 		 int height,
// 		 double value);

// 	int time();
// 	int height();
// 	double value();
// };

// int node::time() { return _time; }
// int node::height() { return _height; }
// double node::value() { return _option_value; }

// node::node(int time,
// 		   int height) {

// 	_time = time;
// 	_height = height;
// }

// node::node(int time,
// 		   int height,
// 		   double value) {

// 	_time = time;
// 	_height = height;
// 	_value = value;
// }

// class tree
// {
// private:
// 	node _up;
// 	node _down;
// 	node _initial;
// public:
// 	tree(){};
// 	tree(node up_node,
// 		 node down_node);

// 	node up();
// 	node down();
// 	void set_up_node(node up_node);
// 	void set_down_node(node down_node);
// };

// tree::tree(node up_node,
// 		   node down_node) {

// 	_up = up_node;
// 	_down = down_node;
// }

// struct node
// {
// 	int value;
// 	node *up;
// 	node *down;
// };

// class tree
// {
// public:
// 	tree();
// 	~tree();

// 	void insert(int value);
// 	node *search(int value);
// 	void destroy_tree();

// private:
// 	void destroy_tree(node *leaf);
// 	void insert(int value, node *leaf);
// 	node *search(int value, node *leaf);

// 	node *root;
// };

// tree::tree(){
// 	root = NULL;
// }

// tree::~tree() {
// 	destroy_tree();
// }

// void tree::destroy_tree(node * leaf) {
// 	if (leaf != NULL){
// 		destroy_tree(leaf->down);
// 		destroy_tree(leaf->up);
// 		delete leaf;
// 	}
// }

// void tree::insert(int value, node *leaf) {
// 	if (value < leaf->value){
// 		if (leaf->down != NULL){
// 			insert(value, leaf->down);
// 		}
// 		else {
// 			leaf->down = new node;
// 			leaf->down->value = value;
// 			leaf->down->down = NULL;
// 			leaf->down->up = NULL;
// 		}
// 	}
// 	else if (value >= leaf->value){
// 		if (leaf->up != NULL){
// 			insert(value, leaf->up);
// 		}
// 		else {
// 			leaf->up = new node;
// 			leaf->up->value = value;
// 			leaf->up->down = NULL;
// 			leaf->up->up = NULL;
// 		}
// 	}
// }

// node *tree::search(int value, node *leaf) {
// 	if (leaf != NULL) {
// 		if (value == leaf->value) {
// 			return leaf;
// 		}
// 		if (value < leaf->value) {
// 			return search(value, leaf->down);
// 		}
// 		else {
// 			return search(value, leaf->up);
// 		}
// 	}
// 	else return NULL;
// }

// void tree::insert(int value) {
// 	if (root != NULL) {
// 		insert(value, root);
// 	}
// 	else {
// 		root = new node;
// 		root->value = value;
// 		root->down = NULL;
// 		root->up = NULL;
// 	}
// }

// node *tree::search(int value) {
// 	return search(value, root);
// }

// void tree::destroy_tree() {
// 	destroy_tree(root);
// }


struct node
{
	double value;
	int time;
	int height;
	node * up;
	node * down;
};

class Tree
{
private:
	node ** _treeArray;


public:
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


// class SecurityTree : public tree
// {

// };



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