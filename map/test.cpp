#include <iostream>
#include "RBT_Tree.hpp"
#include "../utils/pair.hpp"
#include "MapIterator.hpp"
#include <cstdio>
#include <map>

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
	// rbt.insert(ft::make_pair(4, 4));
	// rbt.insert(ft::make_pair(7, 7));
	// rbt.insert(ft::make_pair(8, 8));
	// rbt.insert(ft::make_pair(10, 10));

	// std::cout << rbt.here(rbt.giveIt(), 10) << std::endl;	
	// rbt.erase(5);
	// rbt.erase(7);
	// rbt.erase(8);
	// rbt.erase(2);
	// rbt.erase(4);

	// rbt.traverse();
	// rbt.traverse();
	RBT::iterator it = rbt.begin();
	// // std::cout << "begin = " << *(it) << std::endl;
	RBT::iterator itr = rbt.end();
	// --itr;
	// 	std::cout << "end = " << *itr << std::endl;

	// itr--;
	for (; it != itr; it++)
		std::cout << *it << std::endl;
	// // for (; it != rbt.end(); it++)
	// itr--;
	// 	std::cout << *itr << std::endl;

	// std::map<int, int> m;

	// m.insert(std::pair<int, int>(2, 3));
	// m.insert(std::pair<int, int>(1, 4));
	// m.insert(std::pair<int, int>(5, 6));

	// // std::map<int,int>::iterator it = m.begin();
	// std::map<int,int>::iterator itr = m.end(); 

	// std::cout << itr->first << std::endl;
	// for (; it != itr; it++)
	// 	std::cout << it->first << std::endl;
	
	// std::pair<int, int> pr = *it;
	// std::cout << pr.first << std::endl;
	// printf("%d\n", pr.second);


	// std::cout << "\n" << rbt.find(5)->left->key << std::endl;
	return 0;
}