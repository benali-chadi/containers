#include <iostream>
#include "Tree.hpp"

int main()
{
	typedef ft::node<char, int> node;
	ft::Tree<char, int> rbt;

	rbt.insert(node('2', 3));
	rbt.insert(node('3', 4));
	rbt.insert(node('5', 4));
	rbt.insert(node('1', 4));
	rbt.insert(node('6', 4));
	rbt.insert(node('0', 4));

	rbt.traverse();
	return 0;
}