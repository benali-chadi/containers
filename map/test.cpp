#include <iostream>
#include "Tree.hpp"

int main()
{
	typedef ft::node<int, int> node;
	ft::Tree<int, int> rbt;

	rbt.insert(node(2, 3));
	rbt.insert(node(3, 4));
	rbt.insert(node(5, 4));
	rbt.insert(node(1, 4));
	rbt.insert(node(6, 4));
	rbt.insert(node(4, 4));
	rbt.insert(node(7, 4));
	rbt.insert(node(8, 3));
	rbt.insert(node(10, 3));
	

	rbt.traverse();
	return 0;
}