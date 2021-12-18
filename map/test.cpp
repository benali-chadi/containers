#include <iostream>
#include "RBT_Tree.hpp"
#include "../utils/pair.hpp"
#include "MapIterator.hpp"

int main()
{
	// typedef ft::node<int, int> node;
	typedef ft::RBT<int, int, std::less<int> > RBT;
	RBT rbt;

	// rbt.insert(2, 3);
	// rbt.insert(3, 4);
	// rbt.insert(5, 4);
	// rbt.insert(1, 4);
	// rbt.insert(6, 4);
	// rbt.insert(4, 4);
	// rbt.insert(7, 4);
	// rbt.insert(8, 3);
	// rbt.insert(10, 3);
	rbt.insert(ft::make_pair(2, 2));
	rbt.insert(ft::make_pair(3, 3));
	rbt.insert(ft::make_pair(5, 5));
	rbt.insert(ft::make_pair(1, 1));
	rbt.insert(ft::make_pair(6, 6));
	rbt.insert(ft::make_pair(4, 4));
	rbt.insert(ft::make_pair(7, 7));
	rbt.insert(ft::make_pair(8, 8));
	rbt.insert(ft::make_pair(10, 10));
	
	// rbt.erase(5);
	// rbt.erase(7);
	// rbt.erase(8);
	// rbt.erase(2);
	// rbt.erase(4);

	// rbt.traverse();
	// rbt.traverse();
	RBT::iterator it = rbt.begin();
	// std::cout << "begin = " << *(it) << std::endl;
	// RBT::iterator itr = rbt.end();
	// std::cout << "end = " << *itr << std::endl;

	for (; it != rbt.end(); it++)
		std::cout << *it << std::endl;

	// std::cout << "\n" << rbt.find(5)->left->key << std::endl;
	return 0;
}