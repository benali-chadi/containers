#include <iostream>
#include "Tree.hpp"

int main()
{
	typedef ft::node<int, int> node;
	ft::RBT_Tree<int, int> rbt;

	rbt.insert(node(2, 3));
	rbt.insert(node(3, 4));
	rbt.insert(node(5, 4));
	rbt.insert(node(1, 4));
	rbt.insert(node(6, 4));
	rbt.insert(node(4, 4));
	rbt.insert(node(7, 4));
	rbt.insert(node(8, 3));
	rbt.insert(node(10, 3));
	
	// rbt.erase(5);
	// rbt.erase(7);
	// rbt.erase(8);
	rbt.erase(2);
	rbt.erase(4);

	rbt.traverse();
	std::cout << "\n" << rbt.find(5)->right->key << std::endl;
	return 0;
}